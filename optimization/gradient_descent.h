#ifndef __ST_ALG_GRADIENT_DESCENT_H__
#define __ST_ALG_GRADIENT_DESCENT_H__

/* stalg Differential Evolution optimizer
 * last change: 04.05.2018
 *
 * Оптимизатор функции нескольких переменных при помощи алгоритма дифференциальной эволюции (разновидность генетического алгоритма).
 *
 * Недочёты: (1) Работает только для ArgumentType = double, так как для других неясно, как генерировать случайное значение.
 *           (2) Хорошо бы сделать кэширование значений функции.
 *
 */

#include <vector>
#include <random>
#include <stdexcept>

#include <ctime>

#include "basic_optimizer.h"
#include "../stalgiostream.h"
#include "../stalgcommon.h"

namespace stalg
{
    template<class ReturnType, class ArgumentType>
    class Optimizer_GradientDescent : public basic_optimizer<ReturnType, ArgumentType>
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

    private:
        // Рабочие данные метода
        FullArgumentType current_point_;

    private:
        // Вспомогательные объекты и функции
        std::mt19937 generator_;
        const double GetRandomReal(const double min_number, const double max_number)
        {
            return std::uniform_real_distribution<>(min_number, max_number)(generator_);
        }
        const int GetRandomInteger(const int min_number, const int max_number)
        {
            return std::uniform_int_distribution<>(min_number, max_number)(generator_);
        }
        const bool GetRandomBool(const double probability)
        {
            return std::bernoulli_distribution(probability)(generator_);
        }

    private:
        Optimizer_GradientDescent() {}

    public:
        explicit Optimizer_GradientDescent(    const unsigned int dimension
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
            if (make_default_parameters)
            {
                SetMaxSteps();
                SetFParameter();
                SetMutationProbability();
                SetSizeOfPopulation();
            }
        }

        void SetMaxSteps(const unsigned int max_steps = 50)
        {
            max_steps_ = max_steps;
        }

        void SetFParameter(const double F_parameter = 0.8)
        {
            F_parameter_ = F_parameter;
        }

        void SetMutationProbability(const double mutation_probability = 0.5)
        {
            mutation_probability_ = mutation_probability;
        }

        void SetSizeOfPopulation(const double size_of_population = 30)
        {
            size_of_population_ = size_of_population;
        }

        void Init(const int seed_number = time(0))
        {
            generator_.seed(seed_number);

            population_.resize(size_of_population_, FullArgumentType(Dimension()));
            new_population_.resize(size_of_population_, FullArgumentType(Dimension()));
        }

        void GenerateInitialPopulation()
        {
            for (unsigned int pop_index = 0; pop_index < size_of_population_; ++pop_index)
            {
                for (unsigned int i = 0; i < Dimension(); ++i)
                {
                    // Тут только для double ! Для остальных надо думать, как сделать.
                    population_[pop_index][i] = GetRandomReal(LowerBound(i), UpperBound(i));
                }
            }
        }

        void MakeStep() override
        {
            for (unsigned int i = 0; i < size_of_population_; ++i)
            {
                int v1 = GetRandomInteger(0, size_of_population_ - 2);
                int v2 = GetRandomInteger(0, size_of_population_ - 3);
                int v3 = GetRandomInteger(0, size_of_population_ - 4);
                Barbuse<int>(i, v1, v2, v3);
                CheckBarbusing<int>(i, v1, v2, v3);
                for (unsigned int j = 0; j < Dimension(); ++j)
                {
                    bool bern_try = GetRandomBool(mutation_probability_);
                    if (bern_try)
                    {
                        new_population_[i][j] = population_[v1][j] + F_parameter_ * (population_[v2][j] - population_[v3][j]);
                        if (     new_population_[i][j] < LowerBound(j) + stalg::COMPARISON_THRESHOLD
                              || new_population_[i][j] > UpperBound(j) - stalg::COMPARISON_THRESHOLD){
                            new_population_[i][j] = population_[i][j];
                        }
                    } else {
                        new_population_[i][j] = population_[i][j];
                    }
                }
                if (CostFunction(new_population_[i]) > CostFunction(population_[i]))
                {
                    new_population_[i] = population_[i];
                }
            }
            population_.swap(new_population_);
        }

        virtual bool StopCondition() const override
        {
            return current_iteration_number_ >= max_steps_;
        }

        void GetMinimum() override
        {
            int index_of_minimum = 0;
            ReturnType min_value = CostFunction(population_[index_of_minimum]);
            for (unsigned int i = 0; i < size_of_population_; ++i)
            {
                ReturnType new_value = CostFunction(population_[i]);
                if (new_value < min_value)
                {
                    index_of_minimum = i;
                    min_value = new_value;
                }
            }
            optimal_point_ = population_[index_of_minimum];
            optimal_value_ = min_value;
        }

        virtual void InitialPreparation() override
        {
            GenerateInitialPopulation();
        }

        void SayHello() const
        {
            std::cout << "optimal point = " << optimal_point_ << std::endl;
            std::cout << "min value     = " << optimal_value_ << std::endl;
        }

        void Report() const
        {
            std::cout << " *** Optimizer_DifferentialEvolution : Report        ***" << std::endl;
            //
            std::cout << "#R : dimension             = " << Dimension() << std::endl;
            std::cout << "#R : lower bound           = " << LowerBound() << std::endl;
            std::cout << "#R : upper bound           = " << UpperBound() << std::endl;
            std::cout << "#R : max steps             = " << max_steps_ << std::endl;
            std::cout << "#R : F-parameter           = " << F_parameter_ << std::endl;
            std::cout << "#R : mutation probability  = " << mutation_probability_ << std::endl;
            std::cout << "#R : size of population    = " << size_of_population_ << std::endl;
            std::cout << "#R : population            = " << population_ << std::endl;
            std::cout << "#R : new population        = " << new_population_ << std::endl;
            std::cout << " *** Optimizer_DifferentialEvolution : End of report ***" << std::endl;
        }
    };
}

#endif // __ST_ALG_GRADIENT_DESCENT_H__

