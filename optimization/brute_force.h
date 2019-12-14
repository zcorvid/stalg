#ifndef __ST_ALG_BRUTE_FORCE_H__
#define __ST_ALG_BRUTE_FORCE_H__

/* stalg Brute Force optimizer
 * last change: 5.06.2017
 *
 * Оптимизатор функции нескольких переменных алгоритмом перебора по сетке (брутфорс, метод грубой силы).
 *
 * Пока сделан с интерфейсом итеративного оптимизатора. В действительности никаких итерация не будет,
 * функция MakeStep ничего не делает, а StopCondition всегда возвращает true (итераций не будет).
 *
 */

#include <stdexcept>
#include <vector>

#include "basic_optimizer.h"
#include "../stalgcommon.h"

namespace stalg
{
    template<class ReturnType, class ArgumentType>
    class Optimizer_BruteForce : public basic_optimizer<ReturnType, ArgumentType>
    {
    public:
        // Алиасы для методов базового шаблона
        using typename basic_optimizer<ReturnType, ArgumentType>::FullArgumentType;
        using typename basic_optimizer<ReturnType, ArgumentType>::CostFunctionType;

        using basic_optimizer<ReturnType, ArgumentType>::Dimension;
        using basic_optimizer<ReturnType, ArgumentType>::CostFunction;
        using basic_optimizer<ReturnType, ArgumentType>::LowerBound;
        using basic_optimizer<ReturnType, ArgumentType>::UpperBound;

        using basic_optimizer<ReturnType, ArgumentType>::current_iteration_number_;
        using basic_optimizer<ReturnType, ArgumentType>::optimal_point_;
        using basic_optimizer<ReturnType, ArgumentType>::optimal_value_;

    private:
        // Параметры метода
        std::vector<ArgumentType> accuracy_;              // Вектор погрешностей. Будет уточнён в МЕНЬШУЮ сторону в процессе работы оптимизатора.
        ArgumentType border_epsilon_;

    private:
        // Рабочие данные метода
        std::vector<ArgumentType> test_vector_;

    private:
        // Вспомогательные объекты и функции
        // Уточнить вектор погрешностей (погрешность не возрастёт), делает так, чтобы в диапазоне укладовалось целое число точек сетки.
        // От краёв отступаем на border_epsilon_
        void AdjustAccuracy()
        {
            for (unsigned int i = 0; i < Dimension(); ++i)
            {
                int steps = (UpperBound(i) - LowerBound(i) - 2 * border_epsilon_) / accuracy_[i] + 1.;
                accuracy_[i] = (UpperBound(i) - LowerBound(i)) / steps;
            }
        }

    private:
        Optimizer_BruteForce();

    public:
        explicit Optimizer_BruteForce(    const unsigned int dimension
                                        , const CostFunctionType& cost_function
                                        , const FullArgumentType& lower_bound
                                        , const FullArgumentType& upper_bound
                                        , const bool make_default_parameters = true
                                      ) : basic_optimizer<ReturnType, ArgumentType>(    dimension
                                                                                      , cost_function
                                                                                      , lower_bound
                                                                                      , upper_bound
                                                                                    )
        {
            if (make_default_parameters) {
                SetBorderEpsilon();
            }
        }

        void SetAccuracy(const std::vector<ArgumentType>& accuracy)
        {
            accuracy_ = accuracy;
        }

        void SetBorderEpsilon(const ArgumentType border_epsilon = stalg::COMPARISON_THRESHOLD)
        {
            border_epsilon_ = border_epsilon;
        }

        bool StopCondition() const
        {
            return true;
        }

        void MakeStep()
        {
            //
        }

        // Вся оптимизация в этой функции
        void GetMinimum()
        {
            AdjustAccuracy();
            // Пока работает лишь для размерности 3 !!!
            if (Dimension() != 3)
            {
                throw std::runtime_error("Inaccessible dimension !");
            }
            test_vector_[0] = LowerBound(0) + border_epsilon_;
            test_vector_[1] = LowerBound(1) + border_epsilon_;
            test_vector_[2] = LowerBound(2) + border_epsilon_;
            optimal_point_ = test_vector_;
            optimal_value_ = CostFunction(test_vector_);

            for (ArgumentType x = LowerBound(0) + border_epsilon_; x < UpperBound(0); x += accuracy_[0])
            {
                test_vector_[0] = x;
                for (ArgumentType y = LowerBound(1) + border_epsilon_; y < UpperBound(1); y += accuracy_[1])
                {
                    test_vector_[1] = y;
                    for (ArgumentType z = LowerBound(2) + border_epsilon_; z < UpperBound(2); z += accuracy_[2])
                    {
                        test_vector_[2] = z;
                        ReturnType new_value = CostFunction(test_vector_);
                        if (new_value < optimal_value_ - stalg::COMPARISON_THRESHOLD)
                        {
                            optimal_point_ = test_vector_;
                            optimal_value_ = new_value;
                        }
                    }
                }
            }
        }

        // Проверка на соответствие размера вектора погрешностей
        void InitialPreparation()
        {
            if (accuracy_.size() != Dimension())
            {
                throw std::runtime_error("Invalid accuracy vector dimension !");
            }
            test_vector_.resize(Dimension());
        }

        void SayHello() const
        {
            std::cout << "optimal point = " << optimal_point_ << std::endl;
            std::cout << "min value     = " << optimal_value_ << std::endl;
        }
    };
}

#endif // __ST_ALG_BRUTE_FORCE_H__

