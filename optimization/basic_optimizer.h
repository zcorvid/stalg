#ifndef __ST_ALG_BASIC_OPTIMIZER_H__
#define __ST_ALG_BASIC_OPTIMIZER_H__

/* stalg basic_optimizer class
 * last change: 24.10.2016
 *
 * Базовый класс оптимизатора.
 *
 * Недочёты: скорее всего стоит защитить все его методы.
 *
 */

#include <vector>
#include <functional>

namespace stalg
{
    template<class ReturnType, class ArgumentType>
    class basic_optimizer
    {
    public:
        // Алиасы типов
        typedef std::vector<ArgumentType> FullArgumentType;
        typedef std::function<ReturnType(const FullArgumentType&)> CostFunctionType;
    private:
        unsigned int dimension_;
        CostFunctionType cost_function_;
        FullArgumentType lower_bound_;
        FullArgumentType upper_bound_;
    private:
        basic_optimizer();
        basic_optimizer(const basic_optimizer<ReturnType, ArgumentType>&);
    protected:
        unsigned int current_iteration_number_;
        FullArgumentType optimal_point_;
        ReturnType optimal_value_;
        explicit basic_optimizer(    const unsigned int dimension
                                   , const CostFunctionType& cost_function
                                   , const FullArgumentType& lower_bound
                                   , const FullArgumentType& upper_bound
                                 ) :
                                     dimension_(dimension)
                                   , cost_function_(cost_function)
                                   , lower_bound_(lower_bound)
                                   , upper_bound_(upper_bound)
                                {}

    public:
        unsigned int Dimension() const
        {
            return dimension_;
        }

        const ReturnType CostFunction(const FullArgumentType& argument) const
        {
            return cost_function_(argument);
        }

        const FullArgumentType LowerBound() const
        {
            return lower_bound_;
        }

        const ArgumentType LowerBound(const unsigned int index) const
        {
            return lower_bound_[index];
        }

        const FullArgumentType UpperBound() const
        {
            return upper_bound_;
        }

        const ArgumentType UpperBound(const unsigned int index) const
        {
            return upper_bound_[index];
        }

        const FullArgumentType OptimalPoint() const
        {
            return optimal_point_;
        }

        const ArgumentType OptimalPoint(const unsigned int index) const
        {
            return optimal_point_[index];
        }

        const ArgumentType OptimalValue() const
        {
            return optimal_value_;
        }

        virtual bool StopCondition() const = 0;
        virtual void MakeStep() = 0;
        virtual void GetMinimum() = 0;
        virtual void InitialPreparation() = 0;

        void Work()
        {
            InitialPreparation();
            for (current_iteration_number_ = 0; !StopCondition(); ++current_iteration_number_)
            {
                MakeStep();
            }
            GetMinimum();
        }
    };
}

#endif // __ST_ALG_BASIC_OPTIMIZER_H__
