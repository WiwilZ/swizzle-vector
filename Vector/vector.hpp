#pragma once


#include "definition.hpp"
#include "swizzle.hpp"
#include <array>


namespace math {
    template <arithmetic T, size_t I0, size_t I1>
    Vector(detail::Swizzle<2, T, I0, I1>) -> Vector<2, T>;


    template <arithmetic T>
    struct Vector<2, T> {
        constexpr Vector() noexcept : data{0, 0} {}
        template <arithmetic U>
        constexpr explicit Vector(U e) noexcept : data{static_cast<T>(e), static_cast<T>(e)} {}
        template <arithmetic U0, arithmetic U1>
        constexpr Vector(U0 e0, U1 e1) noexcept : data{static_cast<T>(e0), static_cast<T>(e1)} {}
        template <size_t D, arithmetic U>
        constexpr Vector(const Vector<D, U>& v) noexcept : data{static_cast<T>(v.x), static_cast<T>(v.y)} {}
        template <arithmetic U, size_t I0, size_t I1>
        constexpr Vector(const detail::Swizzle<2, U, I0, I1>& v) noexcept : data{static_cast<T>(v[0]), static_cast<T>(v[1])} {}


        template <class Self>
        constexpr auto&& operator[](this Self&& self, size_t index) noexcept {
            return std::forward<Self>(self).data[index];
        }


        template <arithmetic U>
        constexpr Vector& operator=(U rhs) noexcept {
            T t = static_cast<T>(rhs);
            data[0] = t;
            data[1] = t;
            return *this;
        }
        template <size_t D, arithmetic U>
        constexpr Vector& operator=(const Vector<D, U>& rhs) noexcept {
            data[0] = rhs.data[0];
            data[1] = rhs.data[1];
            return *this;
        }


        union {
            T data[2];
            struct { T x, y; };
            struct { T u, v; };



            detail::SwizzleContainer<2, T, 0, 0> xx, uu;
            detail::SwizzleContainer<2, T, 0, 1> xy, uv;
            detail::SwizzleContainer<2, T, 1, 0> yx, vu;
            detail::SwizzleContainer<2, T, 1, 1> yy, vv;
            detail::SwizzleContainer<2, T, 0, 0, 0> xxx, uuu;
            detail::SwizzleContainer<2, T, 0, 0, 1> xxy, uuv;
            detail::SwizzleContainer<2, T, 0, 1, 0> xyx, uvu;
            detail::SwizzleContainer<2, T, 0, 1, 1> xyy, uvv;
            detail::SwizzleContainer<2, T, 1, 0, 0> yxx, vuu;
            detail::SwizzleContainer<2, T, 1, 0, 1> yxy, vuv;
            detail::SwizzleContainer<2, T, 1, 1, 0> yyx, vvu;
            detail::SwizzleContainer<2, T, 1, 1, 1> yyy, vvv;
            detail::SwizzleContainer<2, T, 0, 0, 0, 0> xxxx, uuuu;
            detail::SwizzleContainer<2, T, 0, 0, 0, 1> xxxy, uuuv;
            detail::SwizzleContainer<2, T, 0, 0, 1, 0> xxyx, uuvu;
            detail::SwizzleContainer<2, T, 0, 0, 1, 1> xxyy, uuvv;
            detail::SwizzleContainer<2, T, 0, 1, 0, 0> xyxx, uvuu;
            detail::SwizzleContainer<2, T, 0, 1, 0, 1> xyxy, uvuv;
            detail::SwizzleContainer<2, T, 0, 1, 1, 0> xyyx, uvvu;
            detail::SwizzleContainer<2, T, 0, 1, 1, 1> xyyy, uvvv;
            detail::SwizzleContainer<2, T, 1, 0, 0, 0> yxxx, vuuu;
            detail::SwizzleContainer<2, T, 1, 0, 0, 1> yxxy, vuuv;
            detail::SwizzleContainer<2, T, 1, 0, 1, 0> yxyx, vuvu;
            detail::SwizzleContainer<2, T, 1, 0, 1, 1> yxyy, vuvv;
            detail::SwizzleContainer<2, T, 1, 1, 0, 0> yyxx, vvuu;
            detail::SwizzleContainer<2, T, 1, 1, 0, 1> yyxy, vvuv;
            detail::SwizzleContainer<2, T, 1, 1, 1, 0> yyyx, vvvu;
            detail::SwizzleContainer<2, T, 1, 1, 1, 1> yyyy, vvvv;
        };
    };
}