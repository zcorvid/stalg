#ifndef __ST_ALG_NNMATCHER_EXTERNAL_H__
#define __ST_ALG_NNMATCHER_EXTERNAL_H__

/* stalg Nearest Neighbour matcher external
 * last change: 16.11.2016
 *
 * Матчер по методу ближайшего соседа. Работает с внешними данными. При необходимости может
 * сохранить данные внутри класса, но это увеличит время работы классификатора на время,
 * необходимое для копирование данных.
 *
 * L = (<время работы функции distance_>)
 * M = количество объектов
 * N = количество образцов
 * Порядок алгоритма: O(M * N * L)
 * Время работы: (1) CalculateNNIndexes         : M * N * 2 * L
 *               (2) CalculateCorrespondence    : M * L
 *               (3) CalculateSamplesStatistics : M * L
 *               (4) CalculateDiscrepance       : N
 *               (S) Общее время                : L * (2 * M * N + M + N) + N
 *               (T) Точная асимптотика         : 2 * L * M * N
 * Самое узкое место - функция расчёта индексов ближайших соседей CalculateNNIndexes(), она будет
 * главным объектом оптимизации.
 *
 * Возможные оптимизации: 1) Если кэшировать таблицу дистанций, то мы прибавим в памяти M * N,
 *                           во времени L * M * N (на расчёт таблицы), но зато множитель L
 *                           пропадёт, суммарное время будет:
 *                              L * M * N + ((M * N + M + N) + N) = L * M * N + M * N + M + 2 * N
 *                           , выигрыш:
 *                              (L - 1) * (M * N + M + N)
 *                           , хотя порядок алгоритма это не уменьшит.
 *                        2) Если пространство объектов одномерно, то можно получить порядок M * N * log(N),
 *                           использовав сортировку образцов, и затем бинарный поиск объектов в отсортированном
 *                           массиве образцов. В этом случае КЭШ расстояний считать не следует.
 *
 * Нужно сделать:         1) move-операции в конструкторах.
 *
 * По состоянию на 16.11.2016 модуль недостаточно протестирован. Использовать с осторожностью.
 */

#include <iostream>
#include <vector>
#include <functional>

#include "../stalgcommon.h"
#include "../stalgiostream.h"
#include "../math/weight.h"
#include "../math/metric.h"

namespace stalg
{
    template<class TPoint>
    class NNMatcherExternal
    {
    private:
        std::function<double(const TPoint&, const TPoint&)> distance_;
        std::function<double(const double)> weight_function_;

        // Данные для работы
        unsigned int n_objects_;
        unsigned int n_samples_;
        const TPoint* objects_;
        const TPoint* samples_;
        double ClassifyingSuccessThreshold_;

        // Данные для отчёта
        bool data_saved;
        std::vector<TPoint> NNObjects_;
        std::vector<TPoint> NNSamples_;

        bool initialized_;
        bool all_classifyed_;

        // Результаты классификации
        std::vector<int> NearestNeighbourIndex_;
        std::vector<bool> classifyed_;
        std::vector<double> DispersionOnSample_;
        std::vector<int> NumberOfMatchedObjects_;
        double discrepancy_;

    private:
        void Init(    const std::vector<TPoint>& objects
                    , const std::vector<TPoint>& samples
                    , const double classifying_threshold
                    , const bool save_data
                  )
        {
            ResetInitialization();

            n_objects_ = objects.size();
            n_samples_ = samples.size();
            objects_ = objects.data();
            samples_ = samples.data();

            ClassifyingSuccessThreshold_ = classifying_threshold;

            if (save_data)
            {
                NNObjects_ = objects;
                NNSamples_ = samples;
            }
            data_saved = save_data;

            NearestNeighbourIndex_.clear();
            classifyed_.clear();
            DispersionOnSample_.clear();
            NumberOfMatchedObjects_.clear();

            NearestNeighbourIndex_.resize(n_objects_, 0);
            classifyed_.resize(n_objects_, false);
            DispersionOnSample_.resize(n_samples_, 0.);
            NumberOfMatchedObjects_.resize(n_samples_, 0);

            discrepancy_ = 0.;

            initialized_ = true;
        }

        // Вычисление индексов ближайших соседей.
        void CalculateNNIndexes()
        {
            for (unsigned int i = 0; i < n_objects_; ++i)
            {
                int index_of_minimum = 0;
                for (unsigned int j = 0; j < n_samples_; ++j)
                {
                    if (distance_(objects_[i], samples_[j]) < distance_(objects_[i], samples_[index_of_minimum]) - stalg::COMPARISON_THRESHOLD)
                    {
                        index_of_minimum = j;
                    }
                }
                NearestNeighbourIndex_[i] = index_of_minimum;
            }
        }

        // Принятие решений о сопоставлении.
        void CalculateCorrespondence()
        {
            for (unsigned int i = 0; i < n_objects_; ++i)
            {
                if (distance_(objects_[i], samples_[NearestNeighbourIndex_[i]]) < ClassifyingSuccessThreshold_)
                {
                    classifyed_[i] = true;
                }
            }
        }

        // Расчёт статистики по образцам
        void CalculateSamplesStatistics()
        {
            for (unsigned int i = 0; i < n_objects_; ++i)
            {
                if (classifyed_[i])
                {
                    DispersionOnSample_[NearestNeighbourIndex_[i]] += weight_function_(distance_(objects_[i], samples_[NearestNeighbourIndex_[i]]));
                    ++NumberOfMatchedObjects_[NearestNeighbourIndex_[i]];
                }
            }
        }

        // Вычисление невязки
        void CalculateDiscrepancy()
        {
            for (unsigned int j = 0; j < n_samples_; ++j)
            {
                if (NumberOfMatchedObjects_[j] > 0)
                {
                    DispersionOnSample_[j] /= NumberOfMatchedObjects_[j];
                }
                discrepancy_ += DispersionOnSample_[j];
            }
        }

        void ReportRaw() const
        {
            std::cout << "#NNMatcher: " << "*** Report ***" << std::endl;
            if (data_saved)
            {
                std::cout << "            " << "Objects                       = " << NNObjects_ << std::endl;
                std::cout << "            " << "Samples                       = " << NNSamples_ << std::endl;
            }
            std::cout << "            " << "Classifying success threshold = " << ClassifyingSuccessThreshold_ << std::endl;
            std::cout << "            " << "NNIndexes                     = " << NearestNeighbourIndex_ << std::endl;
            std::cout << "            " << "Classification flags          = " << classifyed_ << std::endl;
            std::cout << "            " << "Dispersion on samples         = " << DispersionOnSample_ << std::endl;
            std::cout << "            " << "Number of matched objects     = " << NumberOfMatchedObjects_ << std::endl;
            std::cout << "            " << "Discrepancy                   = " << discrepancy_ << std::endl;
        }

    public:
        // NNMatcher(const std::function<double(const TPoint&, const TPoint&)>&& distance) : distance_(std::move(distance))
        NNMatcherExternal(    const std::function<double(const TPoint&, const TPoint&)>& distance = stalg::metric::standard_distance<TPoint>
                            , const std::function<double(const double)>& weight_function = stalg::weight::standard_weight<double>
                          ) : distance_(distance)
                            , weight_function_(weight_function)
        {
            ResetInitialization();
        }

        void ResetInitialization()
        {
            data_saved = false;
            all_classifyed_ = false;
            initialized_ = false;
        }

        void Classify(    const std::vector<TPoint>& Objects
                        , const std::vector<TPoint>& Samples
                        , const double classifying_threshold
                        , const bool save_data = false
                      )
        {
            Init(Objects, Samples, classifying_threshold, save_data);

            CalculateNNIndexes();
            CalculateCorrespondence();
            CalculateSamplesStatistics();
            CalculateDiscrepancy();

            all_classifyed_ = true;
        }

        void Report() const
        {
            if (!initialized_)
            {
                std::cout << "#NNMatcher: " << "Классификатор не инициализирован." << std::endl;
            } else if (!all_classifyed_)
            {
                std::cout << "#NNMatcher: " << "Классификация не произведена." << std::endl;
            } else {
                ReportRaw();
            }
        }

        double Discrepancy() const
        {
            return discrepancy_;
        }
    };
}

#endif // __ST_ALG_NNMATCHER_EXTERNAL_H__
