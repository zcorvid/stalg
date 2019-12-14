#ifndef __STALG_QUATERNION_H__
#define __STALG_QUATERNION_H__

namespace stalg
{
template<typename T>
class quaternion
{
private:
    T a, b, c, d;

public:
    quaternion(const T &ac = 0, const T &bc = 0, const T &cc = 0, const T &dc = 0) : a(ac), b(bc), c(cc), d(dc)
    {
        //
    }
    quaternion(const quaternion<T> &q) : a(q.a), b(q.b), c(q.c), d(q.d)
    {
        //
    }
    friend
    const quaternion<T> operator + (const quaternion<T> &lhs, const quaternion<T> &rhs)
    {
        return quaternion<T>(lhs.a + rhs.a, lhs.b + rhs.b, lhs.c + rhs.c, lhs.d + rhs.d);
    }
    friend
    const quaternion<T> operator - (const quaternion<T> &lhs, const quaternion<T> &rhs)
    {
        return lhs + (-rhs);
    }
    friend
    const quaternion<T> operator * (const quaternion<T> &lhs, const quaternion<T> &rhs)
    {
        //
    }
    friend
    const quaternion<T> operator / (const quaternion<T> &lhs, const quaternion<T> &rhs)
    {
        //
    }
};
}

#endif // __STALG_QUATERNION_H__
