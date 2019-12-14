#ifndef __ST_ALG_SVALKA_H__
#define __ST_ALG_SVALKA_H__

/* stalg svalka
 * last change: 11.01.2017
 *
 * Здесь собраны функции, которые нужно разнести по соответствующим модулям,
 * либо вообще переделать в классы.
 * Некоторые функции не написаны, написано лишь, что они должны делать.
 *
 */

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "stalgcommon.h"

namespace stalg
{
    // Оценка прогресса выполнения чего-либо. Использует статический счётчик. Внимание, потоконебезопасная функция !
    void EstimateProgress(const double vol_made, const double vol_all, const double check_step = 20.)
    {
        static double last_progress = 0.;
        double progress = 100. * vol_made / vol_all;
        if (progress - last_progress > check_step + stalg::COMPARISON_THRESHOLD) {
            last_progress = progress;
            std::cout << "The progress reached : " << (int)last_progress << "%" << std::endl;
        }
    }

    // Парсит число на цифры по заданному основанию.
    template<class NumberType>
    std::vector<int> ParseNumber(const NumberType& number, const int base = 10)
    {
        std::vector<int> mas;
        NumberType base_degree = 1;
        for (int i = 0; number >= base_degree; ++i) {
            mas.push_back((number / base_degree) % base);
            base_degree *= base;
        }
        return mas;
    }

    // Класс выдаватель чисел Фибоначчи, ленивые вычисления.

    // Получить любой делитель числа. Вернёт 1 для простых чисел, для составных вернёт нетривиальный делитель.
    template<class T>
    T GetDivisor(const T& number)
    {
        T border = sqrt(number);
        T answer = 1;
        for (T i = border; i > 1; --i) {
            if (number % i == 0) {
                answer = i;
                break;
            }
        }
        return answer;
    }

    // Получить любой простой делитель числа. Для простого числа вернёт его само.
    template<class T>
    T GetPrimeDivisor(const T& number)
    {
        T p = number;
        T border = sqrt(number);
        for (T i = 2; i <= border; ++i) {
            if (number % i == 0) {
                p = i;
                break;
            }
        }
        return p;
    }

    // Получить максимальный простой делитель числа.
    template<class T>
    T MaxPrimeDivisor(const T& number)
    {
        const T divisor = GetDivisor(number);
        T answer;
        if (divisor == 1) {
            answer = number;
        } else {
            answer = std::max(MaxPrimeDivisor(divisor), MaxPrimeDivisor(number / divisor));
        }
        return answer;
    }

    // Делит число на заданное простое максимальное число раз. В итоге полученное число не будет делиться на заданное простое.
    // Возвращает максимальную степень d, такую, что число делится на эту степень простого числа.
    template<class T>
    T ReducePrime(T& number, const T p)
    {
        T d = 0;
        while (number % p == 0) {
            ++d;
            number /= p;
        }
        return d;
    }

    // Является ли число палиндромом в base-ричной системе счисления. Работает только для 6-значных чисел.
    template<class T>
    bool IsPalindrome(T number, const T base)
    {
        T mas[6];
        mas[0] = number % base;
        number /= base;
        mas[1] = number % base;
        number /= base;
        mas[2] = number % base;
        number /= base;
        mas[3] = number % base;
        number /= base;
        mas[4] = number % base;
        number /= base;
        mas[5] = number % base;
        number /= base;
        return mas[0] == mas[5] && mas[1] == mas[4] && mas[2] == mas[3];
    }

    // Состоит ли массив из одинаковых элементов.
    template<class T>
    bool AllEquals(const std::vector<T>& mas)
    {
        for (int i = 1; i < mas.size(); ++i) {
            if (mas[i - 1] != mas[i]) {
                return false;
            }
        }
        return true;
    }

    // Сумма чисел от 1 до n.
    template<class T>
    T SumFirst(const T n)
    {
        return n * (n + 1) / 2;
    }

    // Сумма квадратов чисел от 1 до n.
    template<class T>
    T SumSquaresFirst(const T n)
    {
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    /* (Кривая) реализация решета Эратосфена. Нужно переделать на класс.
     * Все (или почти все) функции следует вызывать с явным указанием шаблонного параметра.
     * Пример использования решета:
     * int main()
     * {
     *     IntType N;
     *     IntType wanted;
     *     std::cout << "Enter N: ";
     *     std::cin >> N;
     *     std::cout << "Enter number of wanted prime: ";
     *     std::cin >> wanted;
     *     std::vector<bool> sieve;
     *     sieve.resize(N, true);
     *     sieve[0] = false;
     *     for (IntType number = 1; stalg::EratosthenesGetNext(sieve, number);) {
     *         stalg::EratosthenesSift(sieve, number);
     *     }
     *     stalg::PrintPrimes<IntType>(sieve);
     *     stalg::FindPrime<IntType>(sieve, wanted);
     *     stalg::FindSumOfPrimes<IntType>(sieve);
     * 	   return 0;
     * }
     */
    // Получить следующее число.
    template<class T>
    bool EratosthenesGetNext(const std::vector<bool>& sieve, T& number)
    {
        T index = -1;
        for (index = number; index < sieve.size() && !sieve[index]; ++index);
        if (index >= sieve.size()) {
            return false;
        } else {
            number = index + 1;
            return true;
        }
    }
    // Вычеркнуть все числа, делящиеся на заданное.
    template<class T>
    void EratosthenesSift(std::vector<bool>& sieve, T number)
    {
        for (T i = number * number - 1; i < sieve.size(); i += number) {
            sieve[i] = false;
        }
    }
    // Вывести все простые (считается, что решето уже подготовлено).
    template<class T>
    void PrintPrimes(const std::vector<bool>& sieve)
    {
        int counter = 0;
        for (T i = 0; i < sieve.size(); ++i) {
            if (sieve[i]) {
                ++counter;
                std::cout << counter << "-th prime is " << i + 1 << std::endl;
            }
        }
    }
    // Найти нужное по счёту простое число.
    template<class T>
    void FindPrime(const std::vector<bool>& sieve, const int wanted)
    {
        int counter = 0;
        for (T i = 0; i < sieve.size(); ++i) {
            if (sieve[i]) {
                ++counter;
                if (counter == wanted) {
                    std::cout << counter << "-th prime is " << i + 1 << std::endl;
                    return;
                }
            }
        }
        std::cout << "Wanted " << wanted << " prime wasn't found. Only " << counter << " primes found." << std::endl;
    }
    // Найти сумму простых в решете.
    template<class T>
    void FindSumOfPrimes(const std::vector<bool>& sieve)
    {
        T sum = 0;
        for (T i = 0; i < sieve.size(); ++i) {
            if (sieve[i]) {
                sum += (i + 1);
            }
        }
        std::cout << "Sum of primes in segment {1, ...  " << sieve.size() << "} is " << sum << std::endl;
    }
    // -----

    // Тип: разложение числа на простые множители
    typedef std::map<long long, int> Decomposition;

    // Получить разложение не простые множители
    template<class T>
    Decomposition Decompose(T number)
    {
        Decomposition dec;
        while (number > 1) {
            T p = GetPrimeDivisor(number);
            dec[p] = ReducePrime(number, p);
        }
        return dec;
    }

    // Печать разложения на экран.
    void PrintDecomposition(const Decomposition& dec)
    {
        for (auto it = dec.begin(); it != dec.end(); ++it) {
            std::cout << "#Prime " << it->first << " : " << it->second << std::endl;
        }
    }

    // sigma_0 - количество делителей числа
    template<class T>
    T SigmaZero(const T& number)
    {
        T answer = 1;
        stalg::Decomposition decomposition = stalg::Decompose(number);
        for (auto it = decomposition.begin(); it != decomposition.end(); ++it) {
            answer *= it->second + 1;
        }
        return answer;
    }

    template<class T>
    void PrintNumber(const T number)
    {
        std::cout << "#Number " << number << std::endl;
    }

    template<class T, class TValue>
    void set2dVecByRandom(T** mas, int d1, int d2, const TValue& value)
    {
        for (int i = 0; i < d1; ++i)
        {
            for (int j = 0; j < d2; ++j)
            {
                mas[i][j] = rand() % 2;
            }
        }
    }

    template<class T>
    void print2dVec(T** mas, int d1, int d2)
    {
        for (int i = 0; i < d1; ++i)
        {
            for (int j = 0; j < d2; ++j)
            {
                std::cout << (int)mas[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    template<class T>
    void print2dVecNonZero(T** mas, int d1, int d2)
    {
        for (int i = 0; i < d1; ++i)
        {
            for (int j = 0; j < d2; ++j)
            {
                if ((int)mas[i][j])
                {
                    std::cout << (int)mas[i][j] << " ";
                }
                else
                {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
    }

    template<class T>
    void set2dVecCool(T** mas, int d1, int d2)
    {
        for (int i = 0; i < d1; ++i)
        {
            for (int j = 0; j < d2; ++j)
            {
                mas[i][j] = (int)(2 * i < j);
            }
        }
    }

    template <class T>
    inline void MemCopy(T* dst, const T* src, size_t s)
    {
        memcpy(dst, src, s * sizeof(T));
    }
}

#endif // __ST_ALG_SVALKA_H__
