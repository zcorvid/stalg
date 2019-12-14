#ifndef __ST_ALG_NNMATCHER_H__
#define __ST_ALG_NNMATCHER_H__

/* stalg Nearest Neighbour matcher
 * last change: 13.10.2016
 *
 * Матчер по методу ближайшего соседа.
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
 * Сообщение от 16.11.2016. Модуль устарел, и больше не поддерживается. Будет заменён на NNMatcherExternal, а затем удалён.
 */

#include <iostream>
#include <vector>
#include <functional>
#include <utility>

#include "../stalgcommon.h"
#include "../stalgiostream.h"
#include "../math/weight_function.h"

namespace stalg
{
    template<class TPoint>
    class NNMatcher
    {
    private:
        bool initialized_;
        bool all_classifyed_;
        std::function<double(const TPoint&, const TPoint&)> distance_;
        std::function<double(const double)> weight_function_;
        std::vector<TPoint> NNObjects_;
        std::vector<TPoint> NNSamples_;
        std::vector<int> NearestNeighbourIndex_;
        double ClassifyingSuccessThreshold_;
        std::vector<bool> classifyed_;
        std::vector<double> DispersionOnSample_;
        std::vector<int> NumberOfMatchedObjects_;
        double discrepancy_;

    private:
        // Вычисление индексов ближайших соседей.
        void CalculateNNIndexes()
        {
            for (int i = 0; i < NNObjects_.size(); ++i)
            {
                int index_of_minimum = 0;
                for (int j = 0; j < NNSamples_.size(); ++j)
                {
                    if (distance_(NNObjects_[i], NNSamples_[j]) < distance_(NNObjects_[i], NNSamples_[index_of_minimum]) - plls::COMPARISON_THRESHOLD)
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
            for (int i = 0; i < NNObjects_.size(); ++i)
            {
                if (distance_(NNObjects_[i], NNSamples_[NearestNeighbourIndex_[i]]) < ClassifyingSuccessThreshold_)
                {
                    classifyed_[i] = true;
                }
            }
        }

        // Расчёт статистики по образцам
        void CalculateSamplesStatistics()
        {
            for (int i = 0; i < NNObjects_.size(); ++i)
            {
                if (classifyed_[i])
                {
                    DispersionOnSample_[NearestNeighbourIndex_[i]] += weight_function_(distance_(NNObjects_[i], NNSamples_[NearestNeighbourIndex_[i]]));
                    ++NumberOfMatchedObjects_[NearestNeighbourIndex_[i]];
                }
            }
        }

        // Вычисление невязки
        void CalculateDiscrepance()
        {
            for (int j = 0; j < NNSamples_.size(); ++j)
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
            std::cout << "            " << "Objects                   = " << NNObjects_ << std::endl;
            std::cout << "            " << "Samples                   = " << NNSamples_ << std::endl;
            std::cout << "            " << "NNIndexes                 = " << NearestNeighbourIndex_ << std::endl;
            std::cout << "            " << "Classification flags      = " << classifyed_ << std::endl;
            std::cout << "            " << "Dispersion on samples     = " << DispersionOnSample_ << std::endl;
            std::cout << "            " << "Number of matched objects = " << NumberOfMatchedObjects_ << std::endl;
            std::cout << "            " << "Discrepancy               = " << discrepancy_ << std::endl;
        }

    public:
        // NNMatcher(const std::function<double(const TPoint&, const TPoint&)>&& distance) : distance_(std::move(distance))
        NNMatcher(    const std::function<double(const TPoint&, const TPoint&)>& distance
                    , const std::function<double(const double)>& weight_function = stalg::weight::identity_weight<double>
                  ) : distance_(distance)
                    , weight_function_(weight_function)
        {
            ResetInitialization();
        }

        void ResetInitialization()
        {
            all_classifyed_ = false;
            initialized_ = false;
        }

        void AddObjects(const TPoint& object)
        {
            ResetInitialization();
            NNObjects_.push_back(object);
        }

        void AddObjects(const std::vector<TPoint>& objects)
        {
            for (int i = 0; i < objects.size(); ++i)
            {
                AddObjects(objects[i]);
            }
        }

        void SetObjects(const std::vector<TPoint>& objects)
        {
            NNObjects_.clear();
            AddObjects(objects);
        }

        void AddSamples(const TPoint& sample)
        {
            ResetInitialization();
            NNSamples_.push_back(sample);
        }

        void AddSamples(const std::vector<TPoint>& samples)
        {
            for (int i = 0; i < samples.size(); ++i)
            {
                AddSamples(samples[i]);
            }
        }

        void SetSamples(const std::vector<TPoint>& samples)
        {
            NNSamples_.clear();
            AddSamples(samples);
        }

        void SetClassifyingSuccessThreshold(const double threshold)
        {
            ResetInitialization();
            ClassifyingSuccessThreshold_ = threshold;
        }

        void Init()
        {
            ResetInitialization();

            NearestNeighbourIndex_.clear();
            classifyed_.clear();
            DispersionOnSample_.clear();
            NumberOfMatchedObjects_.clear();

            NearestNeighbourIndex_.resize(NNObjects_.size(), 0);
            classifyed_.resize(NNObjects_.size(), false);
            DispersionOnSample_.resize(NNSamples_.size(), 0.);
            NumberOfMatchedObjects_.resize(NNSamples_.size(), 0);

            discrepancy_ = 0;

            // all_classifyed_ = false;
            initialized_ = true;
        }

        void Classify()
        {
            if (!initialized_)
            {
                Init();
            }
            CalculateNNIndexes();
            CalculateCorrespondence();
            CalculateSamplesStatistics();
            CalculateDiscrepance();
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

#endif // __ST_ALG_NNMATCHER_H__
