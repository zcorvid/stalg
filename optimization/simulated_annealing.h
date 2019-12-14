#ifndef __ST_ALG_SIMULATED_ANNEALING_H__
#define __ST_ALG_SIMULATED_ANNEALING_H__

#include <vector>
#include <random>
#include <stdexcept>

#include <ctime>
#include <cmath>

#include "basic_optimizer.h"
#include "../stalgiostream.h"
#include "../stalgcommon.h"

namespace stalg
{
    template<class ReturnType, class ArgumentType>
    class Optimizer_SimulatedAnnealing : public basic_optimizer<ReturnType, ArgumentType>
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
        static constexpr double basic_epsilon = 1.;
        FullArgumentType start_point_;
        double start_temperature_;

    private:
        // Рабочие данные метода
        FullArgumentType best_old_point_;
        ReturnType best_old_value_;
        FullArgumentType current_point_;
        ReturnType current_value_;
        double current_temperature_;

    private:
        // Вспомогательные объекты и функции
        std::mt19937 generator_;
        double GetRandomReal(const double min_number, const double max_number)
        {
            return std::uniform_real_distribution<>(min_number, max_number)(generator_);
        }
        double GetRandomInteger(const int min_number, const int max_number)
        {
            return std::uniform_int_distribution<>(min_number, max_number)(generator_);
        }
        double GetRandomBool(const double probability)
        {
            return std::bernoulli_distribution(probability)(generator_);
        }
        FullArgumentType RandomVector(const FullArgumentType& lower_bound, const FullArgumentType& upper_bound)
        {
            FullArgumentType return_vector;
            size_t vector_size = lower_bound.size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                return_vector.push_back(GetRandomReal(lower_bound[i], upper_bound[i]));
            }
            return return_vector;
        }
        FullArgumentType RandomVector(const FullArgumentType& lower_bound, const FullArgumentType& upper_bound, const FullArgumentType& center, const double k)
        {
            FullArgumentType return_vector;
            size_t vector_size = lower_bound.size();
            for (size_t i = 0; i < vector_size; ++i)
            {
                return_vector.push_back(GetRandomReal(std::max(lower_bound[i], center[i] - basic_epsilon * k), std::min(upper_bound[i], center[i] + basic_epsilon * k)));
            }
            return return_vector;
        }

    public:
        explicit Optimizer_SimulatedAnnealing(    const unsigned int dimension
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
                Init();
                SetStartPoint();
                SetStartTemperature();
            }
        }

        void SetStartPoint()
        {
            start_point_ = RandomVector(LowerBound(), UpperBound());
        }

        void SetStartPoint(const FullArgumentType& start_point)
        {
            start_point_ = start_point;
        }

        void SetStartTemperature(const double start_temperature = 30.)
        {
            start_temperature_ = start_temperature;
        }

        void Init(const int seed_number = time(0))
        {
            generator_.seed(seed_number);
        }

        virtual FullArgumentType GenerateNextPoint()
        {
            // Новая пробная точка зависит от предыдущей и от температуры.
            // return RandomVector(LowerBound(), UpperBound(), current_point_, pow(current_temperature_ / start_temperature_, 1));
            return RandomVector(LowerBound(), UpperBound());
        }

        virtual bool TestPassed(const FullArgumentType& next_point, const ReturnType& next_value)
        {
            return next_value < current_value_ - stalg::COMPARISON_THRESHOLD || GetRandomBool(exp(-stalg::abs(next_value - current_value_) / current_temperature_));
        }

        virtual void DecreaseTemperature()
        {
            current_temperature_ = current_temperature_ * 0.9999;
        }

        void MakeStep() override
        {
            FullArgumentType next_point = GenerateNextPoint();
            ReturnType next_value = CostFunction(next_point);
            if (TestPassed(next_point, next_value)) {
                if (current_value_ < next_value - stalg::COMPARISON_THRESHOLD) {
                    best_old_point_ = current_point_;
                    best_old_value_ = current_value_;
                }
                current_point_.swap(next_point);
                std::swap(current_value_, next_value);
            }
            DecreaseTemperature();
        }

        bool StopCondition() const override
        {
            return stalg::abs(current_temperature_) < stalg::COMPARISON_THRESHOLD || current_temperature_ < 0.;
        }

        void GetMinimum() override
        {
            if (current_value_ < best_old_value_ - stalg::COMPARISON_THRESHOLD) {
                optimal_point_ = current_point_;
                optimal_value_ = current_value_;
            } else {
                optimal_point_ = best_old_point_;
                optimal_value_ = best_old_value_;
            }
        }

        void InitialPreparation() override
        {
            current_point_ = start_point_;
            current_value_ = CostFunction(current_point_);
            current_temperature_ = start_temperature_;
        }

        void SayHello()
        {
            std::cout << "optimal point = " << optimal_point_ << std::endl;
            std::cout << "min value     = " << optimal_value_ << std::endl;
        }

        void Report()
        {
            std::cout << " *** Optimizer_DifferentialEvolution : Report        ***" << std::endl;
            //
            std::cout << "#R : dimension             = " << Dimension() << std::endl;
            std::cout << "#R : lower bound           = " << LowerBound() << std::endl;
            std::cout << "#R : upper bound           = " << UpperBound() << std::endl;
            std::cout << " *** Optimizer_DifferentialEvolution : End of report ***" << std::endl;
        }
    };
}

#endif // __ST_ALG_SIMULATED_ANNEALING_H__
