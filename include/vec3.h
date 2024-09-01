#ifndef VEC3_H
#define VEC3_H

#include <concepts>

template <typename T>
concept VectorElement = std::is_arithmetic_v<T> &&
                        std::is_default_constructible_v<T> &&
                        requires(T a, T b) {
                            { a + b } -> std::convertible_to<T>;
                            { a - b } -> std::convertible_to<T>;
                            { a* b } -> std::convertible_to<T>;
                            { a / b } -> std::convertible_to<T>;
                            { -a } -> std::convertible_to<T>;
                        };

template <VectorElement T>
class vec3
{
public:
    vec3() : data({ T(), T(), T() }) {}
    vec3(T x, T y, T z) : data({ x, y, z }) {}
    ~vec3()                                   = default;
    vec3(const vec3<T>& other)                = default;
    vec3<T>& operator=(const vec3<T>& other)  = default;
    vec3(vec3<T>&& other)                     = default;
    vec3<T>& operator=(vec3<T>&& other)       = default;

    T x() const { return data[0]; }
    T y() const { return data[1]; }
    T z() const { return data[2]; }

    T r() const { return data[0]; }
    T g() const { return data[1]; }
    T b() const { return data[2]; }

    T operator[](uint32_t i) const { return data[i]; }
    T& operator[](uint32_t i) { return data[i]; }

    vec3 operator-() const { return vec3(-data[0], -data[1], -data[2]); }

    vec3& operator+(const vec3& other) {
        data[0] += other.data[0];
        data[1] += other.data[1];
        data[2] += other.data[2];
        return *this;
    }

    vec3& operator*(const vec3& other) {
        data[0] *= other.data[0];
        data[1] *= other.data[1];
        data[2] *= other.data[2];
        return *this;
    }

    vec3& operator/(const T& divisor) {
        data[0] /= divisor;
        data[1] /= divisor;
        data[2] /= divisor;
        return *this;
    }

private:
    std::array<T, 3> data;
};

template <VectorElement T>
inline std::ostream& operator<<(std::ostream& out, const vec3<T>& v) {
    return out << v.x() << " " << v.y() << " " << v.z();
}

template <VectorElement T>
inline vec3<T> operator+(const vec3<T>& u, const vec3<T>& v) {
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

template <VectorElement T>
inline vec3<T> operator-(const vec3<T>& u, const vec3<T>& v) {
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

template <VectorElement T>
inline vec3<T> operator*(const vec3<T>& u, const vec3<T>& v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

template <VectorElement T>
inline vec3<T> operator*(const vec3<T>& u, T scalar) {
    return vec3(scalar * u[0], scalar * u[1], scalar * u[2]);
}

template <VectorElement T>
inline vec3<T> operator*(T scalar, const vec3<T>& u) {
    return scalar * u;
}

template <VectorElement T>
inline vec3<T> operator/(const vec3<T>& u, const T& scalar) {
    return vec3(u[0] / scalar, u[1] / scalar, u[2] / scalar);
}

template <VectorElement T>
inline double dot(const vec3<T>& u, const vec3<T>& v) {
    return u[0] * v[0]
        + u[1] * v[1]
        + u[2] * v[2];
}

template <VectorElement T>
inline vec3<T> cross(const vec3<T>& u, const vec3<T>& v) {
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

template <VectorElement T>
inline vec3<T> unit_vector(const vec3<T>& v) {
    return v / v.length();
}

#endif