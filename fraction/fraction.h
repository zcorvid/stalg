#ifndef __ST_ALG_FRACTION_H__
#define __ST_ALG_FRACTION_H__

// stalg fraction
// 27.12.2016

#include "../math/stalgmath.h"

namespace stalg
{
    template<class T>
    class fraction
    {
    private:
        T numerator_;
        T denominator_;

    private:
        void reduce()
        {
            T factor = gcd(numerator_, denominator_);
            numerator_ /= factor;
            denominator_ /= factor;
        }

        void normalize()
        {
            if (denominator_ == 0)
            {
                denominator_ = unit_element<T>();
            }
            else if (denominator_ < 0)
            {
                numerator_ = -numerator_;
                denominator_ = -denominator_;
            }
            reduce();
        }

    public:
        // fraction() {}

        fraction(const T& numerator = 0, const T& denominator = unit_element<T>()) : numerator_(numerator), denominator_(denominator)
        {
            normalize();
        }

        fraction(const fraction<T>& other) : numerator_(other.numerator_), denominator_(other.denominator_) {}

        void SetNumerator(const T& numerator)
        {
            numerator_ = numerator;
            normalize();
        }

        void SetDenominator(const T& denominator)
        {
            denominator_ = denominator;
            normalize();
        }

        const T Numerator() const
        {
            return numerator_;
        }

        const T Denominator() const
        {
            return denominator_;
        }

        const fraction<T> operator - () const
        {
            return fraction<T>(-numerator_, denominator_);
        }

        const fraction<T>& operator = (const fraction<T>& other)
        {
            numerator_ = other.numerator_;
            denominator_ = other.denominator_;
            return *this;
        }

        const fraction<T>& operator = (const T& number)
        {
            numerator_ = number;
            denominator_ = unit_element<T>();
            return *this;
        }

        friend
        bool operator == (const fraction<T>& lhs, const fraction<T>& rhs)
        {
            return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
        }

        friend
        bool operator != (const fraction<T>& lhs, const fraction<T>& rhs)
        {
            return !(lhs == rhs);
        }

        friend
        const fraction<T> operator + (const fraction<T>& lhs, const fraction<T>& rhs)
        {
            // T common_denominator = gcd(denominator_, other.denominator_);
            T common_denominator = lhs.Denominator() * rhs.Denominator();
            T factor_first = rhs.Denominator();
            T factor_second = lhs.Denominator();
            T numerator_new = lhs.Numerator() * factor_first + rhs.Numerator() * factor_second;
            T denominator_new = common_denominator;
            return fraction<T>(numerator_new, denominator_new);
        }

        friend
        const fraction<T> operator - (const fraction<T>& lhs, const fraction<T>& rhs)
        {
            return lhs + (-rhs);
        }

        friend
        const fraction<T> operator * (const fraction<T>& lhs, const fraction<T>& rhs)
        {
            return fraction<T>(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
        }

        friend
        const fraction<T> operator / (const fraction<T>& lhs, const fraction<T>& rhs)
        {
            return fraction<T>(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
        }
    };
}

#endif // __ST_ALG_FRACTION_H__
