#pragma once


#include <cmath>

#include <concepts>
#include <iostream>

#include "type_helper.h"


template <size_t N, detail::numeric T>
struct Vector;


namespace detail {
    struct Base;

    template <typename T>
    concept integral_element_constraint = std::derived_from<T, Base> && integral<typename T::element_type>;

    template <typename Other, typename Self>
    concept rhs_constraint = std::derived_from<Other, Base> && Other::dim == Self::dim || numeric<Other>;

    template <typename Other, typename Self>
    concept bitwise_rhs_constraint = integral_element_constraint<Other> && Self::dim == Other::dim || integral<Other>;

    template <typename L, typename R>
    concept binary_compatible = std::derived_from<L, Base> && rhs_constraint<R, L> || numeric<L> && std::derived_from<R, Base>;

    template <typename L, typename R>
    concept bitwise_compatible = integral_element_constraint<L> && bitwise_rhs_constraint<R, L> || integral<L> && integral_element_constraint<R>;


    struct Base {
        // unary operators
        // arithmetic operators
        [[nodiscard]] constexpr auto operator+(this const auto& self) noexcept {
            return Vector(self);
        }

        template <typename Self>
        [[nodiscard]] constexpr auto operator-(this const Self& self) noexcept {
            return self.unary_func([](auto e) -> typename Self::element_type { return -e; });
        }

        // bitwise operators
        template <typename Self>
            requires integral<typename Self::element_type>
        [[nodiscard]] constexpr auto operator~(this const Self& self) noexcept {
            return self.unary_func([](auto e) -> typename Self::element_type { return ~e; });
        }

        // logical operators
        [[nodiscard]] constexpr auto operator!(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return !e; });
        }


        // other unary functions
        template <numeric T>
        [[nodiscard]] constexpr auto cast(this const auto& self) noexcept {
            return self.unary_func([](auto e) -> T { return e; });
        }

        template <typename Self>
        [[nodiscard]] constexpr auto abs(this const Self& self) noexcept {
            return self.unary_func([](auto e) -> typename Self::element_type { return std::abs(e); });
        }

        [[nodiscard]] constexpr auto sqrt(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::sqrt(e); });
        }

        [[nodiscard]] constexpr auto cbrt(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::cbrt(e); });
        }

        [[nodiscard]] constexpr auto exp(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::exp(e); });
        }

        [[nodiscard]] constexpr auto exp2(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::exp2(e); });
        }

        [[nodiscard]] constexpr auto expm1(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::expm1(e); });
        }

        [[nodiscard]] constexpr auto log(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::log(e); });
        }

        [[nodiscard]] constexpr auto log10(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::log10(e); });
        }

        [[nodiscard]] constexpr auto log2(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::log2(e); });
        }

        [[nodiscard]] constexpr auto log1p(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::log1p(e); });
        }

        [[nodiscard]] constexpr auto sin(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::sin(e); });
        }

        [[nodiscard]] constexpr auto cos(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::cos(e); });
        }

        [[nodiscard]] constexpr auto tan(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::tan(e); });
        }

        [[nodiscard]] constexpr auto asin(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::asin(e); });
        }

        [[nodiscard]] constexpr auto acos(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::acos(e); });
        }

        [[nodiscard]] constexpr auto atan(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::atan(e); });
        }

        [[nodiscard]] constexpr auto sinh(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::sinh(e); });
        }

        [[nodiscard]] constexpr auto cosh(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::cosh(e); });
        }

        [[nodiscard]] constexpr auto tanh(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::tanh(e); });
        }

        [[nodiscard]] constexpr auto asinh(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::asinh(e); });
        }

        [[nodiscard]] constexpr auto acosh(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::acosh(e); });
        }

        [[nodiscard]] constexpr auto atanh(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::atanh(e); });
        }

        [[nodiscard]] constexpr auto erf(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::erf(e); });
        }

        [[nodiscard]] constexpr auto erfc(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::erfc(e); });
        }

        [[nodiscard]] constexpr auto tgamma(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::tgamma(e); });
        }

        [[nodiscard]] constexpr auto lgamma(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::lgamma(e); });
        }

        [[nodiscard]] constexpr auto ceil(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::ceil(e); });
        }

        [[nodiscard]] constexpr auto floor(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::floor(e); });
        }

        [[nodiscard]] constexpr auto trunc(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::trunc(e); });
        }

        [[nodiscard]] constexpr auto round(this const auto& self) noexcept {
            return self.unary_func([](auto e) { return std::round(e); });
        }


        template <typename Self>
        [[nodiscard]] constexpr bool any(this const Self& self) noexcept {
            return [&]<size_t... Is>(std::index_sequence<Is...>) {
                return (... || self[Is]);
            }(std::make_index_sequence<Self::dim>{});
        }

        template <typename Self>
        [[nodiscard]] constexpr bool all(this const Self& self) noexcept {
            return [&]<size_t... Is>(std::index_sequence<Is...>) {
                return (... && self[Is]);
            }(std::make_index_sequence<Self::dim>{});
        }

    private:
        template <typename Self>
        constexpr auto unary_func(this const Self& self, const auto& op) noexcept {
            return self.unary_func(op, std::make_index_sequence<Self::dim>{});
        }

        template <size_t... Is>
        constexpr auto unary_func(this const auto& self, const auto& op, std::index_sequence<Is...>) noexcept {
            return Vector{op(self[Is])...};
        }
    };


    struct MutableBase : Base {
        // assignment operators
        template <typename Self, std::derived_from<Base> Other>
            requires(Self::dim != Other::dim)
        auto& operator=(this Self&, const Other&) = delete;// prevent object slicing

        template <typename Self>
        constexpr auto& operator=(this Self& self, const rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l = r; });
            return self;
        }

        // arithmetic operators
        template <typename Self>
        constexpr auto& operator+=(this Self& self, const rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l += r; });
            return self;
        }

        template <typename Self>
        constexpr auto& operator-=(this Self& self, const rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l -= r; });
            return self;
        }

        template <typename Self>
        constexpr auto& operator*=(this Self& self, const rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l *= r; });
            return self;
        }

        template <typename Self>
        constexpr auto& operator/=(this Self& self, const rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l /= r; });
            return self;
        }

        template <typename Self>
        constexpr auto& operator%=(this Self& self, const rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l %= r; });
            return self;
        }

        // bitwise operators
        template <integral_element_constraint Self>
        constexpr auto& operator&=(this Self& self, const bitwise_rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l &= r; });
            return self;
        }

        template <integral_element_constraint Self>
        constexpr auto& operator|=(this Self& self, const bitwise_rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l |= r; });
            return self;
        }

        template <integral_element_constraint Self>
        constexpr auto& operator^=(this Self& self, const bitwise_rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l ^= r; });
            return self;
        }

        template <integral_element_constraint Self>
        constexpr auto& operator<<=(this Self& self, const bitwise_rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l <<= r; });
            return self;
        }

        template <integral_element_constraint Self>
        constexpr auto& operator>>=(this Self& self, const bitwise_rhs_constraint<Self> auto& other) noexcept {
            self.inplace_func(other, [](auto& l, auto r) noexcept { l >>= r; });
            return self;
        }

        // unary operators
        // increment and decrement operators
        constexpr auto& operator++(this auto& self) noexcept {
            self.inplace_func([](auto& e) noexcept { ++e; });
            return self;
        }

        constexpr auto& operator--(this auto& self) noexcept {
            self.inplace_func([](auto& e) noexcept { --e; });
            return self;
        }

        constexpr auto operator++(this auto& self, int) noexcept {
            const auto tmp = self;
            self.inplace_func([](auto& e) noexcept { ++e; });
            return tmp;
        }

        constexpr auto operator--(this auto& self, int) noexcept {
            const auto tmp = self;
            self.inplace_func([](auto& e) noexcept { --e; });
            return tmp;
        }

    private:
        template <typename Self>
        constexpr void inplace_func(this Self& self, const std::derived_from<Base> auto& v, const auto& op) noexcept {
            self.inplace_func(v, op, std::make_index_sequence<Self::dim>{});
        }

        template <typename Self, std::derived_from<Base> Other, size_t... Is>
        constexpr void inplace_func(this Self& self, const Other& v, const auto& op, std::index_sequence<Is...>) noexcept {
            using LT = typename Self::element_type;
            using RT = typename Other::element_type;
            if constexpr (std::is_same_v<LT, RT>) {
                if (self.data == v.data) {
                    RT tmp[]{v[Is]...};
                    (..., op(self[Is], tmp[Is]));
                    return;
                }
            }
            (..., op(self[Is], v[Is]));
        }

        template <typename Self>
        constexpr void inplace_func(this Self& self, numeric auto e, const auto& op) noexcept {
            self.inplace_func(e, op, std::make_index_sequence<Self::dim>{});
        }

        template <size_t... Is>
        constexpr void inplace_func(this auto& self, numeric auto e, const auto& op, std::index_sequence<Is...>) noexcept {
            (..., op(self[Is], e));
        }

        template <typename Self>
        constexpr void inplace_func(this Self& self, const auto& op) noexcept {
            self.unary_func(op, std::make_index_sequence<Self::dim>{});
        }

        template <size_t... Is>
        constexpr void inplace_func(this auto& self, const auto& op, std::index_sequence<Is...>) noexcept {
            (..., op(self[Is]));
        }
    };


    template <std::derived_from<Base> L, std::derived_from<Base> R, size_t... Is>
        requires(L::dim == R::dim)
    [[nodiscard]] constexpr auto binary_func(const L& lhs, const R& rhs, const auto& op, std::index_sequence<Is...>) noexcept {
        return Vector{op(lhs[Is], rhs[Is])...};
    }

    template <std::derived_from<Base> L, size_t... Is>
    [[nodiscard]] constexpr auto binary_func(const L& lhs, numeric auto e, const auto& op, std::index_sequence<Is...>) noexcept {
        return Vector{op(lhs[Is], e)...};
    }

    template <std::derived_from<Base> R, size_t... Is>
    [[nodiscard]] constexpr auto binary_func(numeric auto e, const R& rhs, const auto& op, std::index_sequence<Is...>) noexcept {
        return Vector{op(e, rhs[Is])...};
    }


    template <std::derived_from<Base> L>
    [[nodiscard]] constexpr auto binary_func(const L& lhs, const rhs_constraint<L> auto& rhs, const auto& op) noexcept {
        return binary_func(lhs, rhs, op, std::make_index_sequence<L::dim>{});
    }

    template <std::derived_from<Base> R>
    [[nodiscard]] constexpr auto binary_func(numeric auto e, const R& rhs, const auto& op) noexcept {
        return binary_func(e, rhs, op, std::make_index_sequence<R::dim>{});
    }


    // binary operators
    // arithmetic operators
    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator+(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l + r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator-(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l - r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator*(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l * r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator/(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l / r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator%(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l % r; });
    }

    // bitwise operators
    template <typename L, typename R>
        requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator&(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l & r; });
    }

    template <typename L, typename R>
        requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator|(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l | r; });
    }

    template <typename L, typename R>
        requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator^(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l ^ r; });
    }

    template <typename L, typename R>
        requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator<<(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l << r; });
    }

    template <typename L, typename R>
        requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator>>(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) -> common_type_t<decltype(l), decltype(r)> { return l >> r; });
    }

    // logical operators
    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator&&(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l && r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator||(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l || r; });
    }

    // comparison operators
    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator==(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l == r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator!=(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l != r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator<(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l < r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator<=(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l <= r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator>(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l > r; });
    }

    template <typename L, typename R>
        requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator>=(const L& lhs, const R& rhs) noexcept {
        return binary_func(lhs, rhs, [](auto l, auto r) { return l >= r; });
    }


    std::ostream& operator<<(std::ostream& os, const std::derived_from<Base> auto& v) {
        os << "(" << v[0];
        for (size_t i = 1; i < v.dim; i++) {
            os << ", " << v[i];
        }
        os << ")";
        return os;
    }


    template <size_t N, numeric T, size_t... Is>
    struct Swizzle : MutableBase {
        friend struct MutableBase;

        template <size_t M, numeric U, size_t... Js>
        friend struct Swizzle;

        template <size_t M, numeric U>
        friend struct VectorBase;


        static constexpr size_t dim = sizeof...(Is);
        using element_type = T;


        using MutableBase::operator=;


        constexpr auto& operator=(const Swizzle& v) noexcept {
            if (this != &v) {
                (..., (data[Is] = v.data[Is]));
            }
            return *this;
        }


        template <typename Self>
        [[nodiscard]] constexpr auto&& operator[](this Self&& self, size_t i) noexcept {
            if constexpr (std::is_same_v<std::index_sequence<Is...>, std::make_index_sequence<dim>>) {
                return std::forward<Self>(self).data[i];
            } else {
                static constexpr size_t indices[]{Is...};
                return std::forward<Self>(self).data[indices[i]];
            }
        }

    private:
        T data[N];
    };

    template <size_t N, numeric T, size_t... Is>
        requires is_duplicated_v<Is...>
    struct Swizzle<N, T, Is...> : Base {
        friend struct MutableBase;

        template <size_t M, numeric U, size_t... Js>
        friend struct Swizzle;

        template <size_t M, numeric U>
        friend struct VectorBase;


        static constexpr size_t dim = sizeof...(Is);
        using element_type = T;


        auto& operator=(auto&&) = delete;// prevent swizzles with duplicate indices from being assigned to


        [[nodiscard]] constexpr T operator[](size_t i) const noexcept {
            if constexpr (std::is_same_v<std::index_sequence<Is...>, std::make_index_sequence<dim>>) {
                return data[i];
            } else {
                static constexpr size_t indices[]{Is...};
                return data[indices[i]];
            }
        }

    private:
        T data[N];
    };


    template <size_t N, numeric T>
    struct VectorBase {
        static constexpr size_t dim = N;
        using element_type = T;


        constexpr VectorBase() noexcept : VectorBase(T{}) {}

        constexpr explicit VectorBase(T e) noexcept {
            std::fill_n(data(), N, e);
        }

        template <std::same_as<T>... Ts>
            requires(sizeof...(Ts) == N)
        constexpr VectorBase(Ts... es) noexcept {
            new (data()) T[]{es...};
        }

        constexpr explicit VectorBase(const T* const buffer) noexcept {
            std::copy_n(buffer, N, data());
        }

        constexpr VectorBase(const VectorBase& v) noexcept : VectorBase(v.data()) {}

        template <size_t M, size_t... Is>
            requires(sizeof...(Is) == N)
        constexpr VectorBase(const Swizzle<M, T, Is...>& v) noexcept : VectorBase(v.data[Is]...) {}


        template <typename Self>
        [[nodiscard]] constexpr auto&& operator[](this Self&& self, size_t i) noexcept {
            return std::forward<Self>(self).data[i];
        }

    private:
        T* data() noexcept {
            return static_cast<Vector<N, T>&>(*this).data;
        }

        const T* data() const noexcept {
            return static_cast<const Vector<N, T>&>(*this).data;
        }
    };
}// namespace detail


template <detail::numeric T>
struct Vector<2, T> : detail::VectorBase<2, T>, detail::MutableBase {
    using detail::VectorBase<2, T>::dim;
    using typename detail::VectorBase<2, T>::element_type;


    using detail::VectorBase<2, T>::VectorBase;


    constexpr auto& operator=(const Vector& v) noexcept {
        if (this != &v) {
            std::copy_n(v.data, dim, data);
        }
        return *this;
    }

    using detail::MutableBase::operator=;


    union {
        T data[2];
        struct {
            T x, y;
        };
        struct {
            T u, v;
        };
        detail::Swizzle<2, T, 0, 0> xx, uu;
        detail::Swizzle<2, T, 0, 1> xy, uv;
        detail::Swizzle<2, T, 1, 0> yx, vu;
        detail::Swizzle<2, T, 1, 1> yy, vv;
        detail::Swizzle<2, T, 0, 0, 0> xxx, uuu;
        detail::Swizzle<2, T, 0, 0, 1> xxy, uuv;
        detail::Swizzle<2, T, 0, 1, 0> xyx, uvu;
        detail::Swizzle<2, T, 0, 1, 1> xyy, uvv;
        detail::Swizzle<2, T, 1, 0, 0> yxx, vuu;
        detail::Swizzle<2, T, 1, 0, 1> yxy, vuv;
        detail::Swizzle<2, T, 1, 1, 0> yyx, vvu;
        detail::Swizzle<2, T, 1, 1, 1> yyy, vvv;
        detail::Swizzle<2, T, 0, 0, 0, 0> xxxx, uuuu;
        detail::Swizzle<2, T, 0, 0, 0, 1> xxxy, uuuv;
        detail::Swizzle<2, T, 0, 0, 1, 0> xxyx, uuvu;
        detail::Swizzle<2, T, 0, 0, 1, 1> xxyy, uuvv;
        detail::Swizzle<2, T, 0, 1, 0, 0> xyxx, uvuu;
        detail::Swizzle<2, T, 0, 1, 0, 1> xyxy, uvuv;
        detail::Swizzle<2, T, 0, 1, 1, 0> xyyx, uvvu;
        detail::Swizzle<2, T, 0, 1, 1, 1> xyyy, uvvv;
        detail::Swizzle<2, T, 1, 0, 0, 0> yxxx, vuuu;
        detail::Swizzle<2, T, 1, 0, 0, 1> yxxy, vuuv;
        detail::Swizzle<2, T, 1, 0, 1, 0> yxyx, vuvu;
        detail::Swizzle<2, T, 1, 0, 1, 1> yxyy, vuvv;
        detail::Swizzle<2, T, 1, 1, 0, 0> yyxx, vvuu;
        detail::Swizzle<2, T, 1, 1, 0, 1> yyxy, vvuv;
        detail::Swizzle<2, T, 1, 1, 1, 0> yyyx, vvvu;
        detail::Swizzle<2, T, 1, 1, 1, 1> yyyy, vvvv;
    };
};

template <detail::numeric T>
struct Vector<3, T> : detail::VectorBase<3, T>, detail::MutableBase {
    using detail::VectorBase<3, T>::dim;
    using typename detail::VectorBase<3, T>::element_type;


    using detail::VectorBase<3, T>::VectorBase;


    template <std::derived_from<detail::Base> V>
        requires(V::dim == 2 && std::is_same_v<typename V::element_type, T>)
    constexpr Vector(T e, const V& v) noexcept : data{e, v[0], v[1]} {}

    template <std::derived_from<detail::Base> V>
        requires(V::dim == 2 && std::is_same_v<typename V::element_type, T>)
    constexpr Vector(const V& v, T e) noexcept : data{v[0], v[1], e} {}


    constexpr auto& operator=(const Vector& v) noexcept {
        if (this != &v) {
            std::copy_n(v.data, dim, data);
        }
        return *this;
    }

    using detail::MutableBase::operator=;


    union {
        T data[3];
        struct {
            T x, y, z;
        };
        struct {
            T u, v, w;
        };
        struct {
            T r, g, b;
        };
        detail::Swizzle<3, T, 0, 0> xx, uu, rr;
        detail::Swizzle<3, T, 0, 1> xy, uv, rg;
        detail::Swizzle<3, T, 0, 2> xz, uw, rb;
        detail::Swizzle<3, T, 1, 0> yx, vu, gr;
        detail::Swizzle<3, T, 1, 1> yy, vv, gg;
        detail::Swizzle<3, T, 1, 2> yz, vw, gb;
        detail::Swizzle<3, T, 2, 0> zx, wu, br;
        detail::Swizzle<3, T, 2, 1> zy, wv, bg;
        detail::Swizzle<3, T, 2, 2> zz, ww, bb;
        detail::Swizzle<3, T, 0, 0, 0> xxx, uuu, rrr;
        detail::Swizzle<3, T, 0, 0, 1> xxy, uuv, rrg;
        detail::Swizzle<3, T, 0, 0, 2> xxz, uuw, rrb;
        detail::Swizzle<3, T, 0, 1, 0> xyx, uvu, rgr;
        detail::Swizzle<3, T, 0, 1, 1> xyy, uvv, rgg;
        detail::Swizzle<3, T, 0, 1, 2> xyz, uvw, rgb;
        detail::Swizzle<3, T, 0, 2, 0> xzx, uwu, rbr;
        detail::Swizzle<3, T, 0, 2, 1> xzy, uwv, rbg;
        detail::Swizzle<3, T, 0, 2, 2> xzz, uww, rbb;
        detail::Swizzle<3, T, 1, 0, 0> yxx, vuu, grr;
        detail::Swizzle<3, T, 1, 0, 1> yxy, vuv, grg;
        detail::Swizzle<3, T, 1, 0, 2> yxz, vuw, grb;
        detail::Swizzle<3, T, 1, 1, 0> yyx, vvu, ggr;
        detail::Swizzle<3, T, 1, 1, 1> yyy, vvv, ggg;
        detail::Swizzle<3, T, 1, 1, 2> yyz, vvw, ggb;
        detail::Swizzle<3, T, 1, 2, 0> yzx, vwu, gbr;
        detail::Swizzle<3, T, 1, 2, 1> yzy, vwv, gbg;
        detail::Swizzle<3, T, 1, 2, 2> yzz, vww, gbb;
        detail::Swizzle<3, T, 2, 0, 0> zxx, wuu, brr;
        detail::Swizzle<3, T, 2, 0, 1> zxy, wuv, brg;
        detail::Swizzle<3, T, 2, 0, 2> zxz, wuw, brb;
        detail::Swizzle<3, T, 2, 1, 0> zyx, wvu, bgr;
        detail::Swizzle<3, T, 2, 1, 1> zyy, wvv, bgg;
        detail::Swizzle<3, T, 2, 1, 2> zyz, wvw, bgb;
        detail::Swizzle<3, T, 2, 2, 0> zzx, wwu, bbr;
        detail::Swizzle<3, T, 2, 2, 1> zzy, wwv, bbg;
        detail::Swizzle<3, T, 2, 2, 2> zzz, www, bbb;
        detail::Swizzle<3, T, 0, 0, 0, 0> xxxx, uuuu, rrrr;
        detail::Swizzle<3, T, 0, 0, 0, 1> xxxy, uuuv, rrrg;
        detail::Swizzle<3, T, 0, 0, 0, 2> xxxz, uuuw, rrrb;
        detail::Swizzle<3, T, 0, 0, 1, 0> xxyx, uuvu, rrgr;
        detail::Swizzle<3, T, 0, 0, 1, 1> xxyy, uuvv, rrgg;
        detail::Swizzle<3, T, 0, 0, 1, 2> xxyz, uuvw, rrgb;
        detail::Swizzle<3, T, 0, 0, 2, 0> xxzx, uuwu, rrbr;
        detail::Swizzle<3, T, 0, 0, 2, 1> xxzy, uuwv, rrbg;
        detail::Swizzle<3, T, 0, 0, 2, 2> xxzz, uuww, rrbb;
        detail::Swizzle<3, T, 0, 1, 0, 0> xyxx, uvuu, rgrr;
        detail::Swizzle<3, T, 0, 1, 0, 1> xyxy, uvuv, rgrg;
        detail::Swizzle<3, T, 0, 1, 0, 2> xyxz, uvuw, rgrb;
        detail::Swizzle<3, T, 0, 1, 1, 0> xyyx, uvvu, rggr;
        detail::Swizzle<3, T, 0, 1, 1, 1> xyyy, uvvv, rggg;
        detail::Swizzle<3, T, 0, 1, 1, 2> xyyz, uvvw, rggb;
        detail::Swizzle<3, T, 0, 1, 2, 0> xyzx, uvwu, rgbr;
        detail::Swizzle<3, T, 0, 1, 2, 1> xyzy, uvwv, rgbg;
        detail::Swizzle<3, T, 0, 1, 2, 2> xyzz, uvww, rgbb;
        detail::Swizzle<3, T, 0, 2, 0, 0> xzxx, uwuu, rbrr;
        detail::Swizzle<3, T, 0, 2, 0, 1> xzxy, uwuv, rbrg;
        detail::Swizzle<3, T, 0, 2, 0, 2> xzxz, uwuw, rbrb;
        detail::Swizzle<3, T, 0, 2, 1, 0> xzyx, uwvu, rbgr;
        detail::Swizzle<3, T, 0, 2, 1, 1> xzyy, uwvv, rbgg;
        detail::Swizzle<3, T, 0, 2, 1, 2> xzyz, uwvw, rbgb;
        detail::Swizzle<3, T, 0, 2, 2, 0> xzzx, uwwu, rbbr;
        detail::Swizzle<3, T, 0, 2, 2, 1> xzzy, uwwv, rbbg;
        detail::Swizzle<3, T, 0, 2, 2, 2> xzzz, uwww, rbbb;
        detail::Swizzle<3, T, 1, 0, 0, 0> yxxx, vuuu, grrr;
        detail::Swizzle<3, T, 1, 0, 0, 1> yxxy, vuuv, grrg;
        detail::Swizzle<3, T, 1, 0, 0, 2> yxxz, vuuw, grrb;
        detail::Swizzle<3, T, 1, 0, 1, 0> yxyx, vuvu, grgr;
        detail::Swizzle<3, T, 1, 0, 1, 1> yxyy, vuvv, grgg;
        detail::Swizzle<3, T, 1, 0, 1, 2> yxyz, vuvw, grgb;
        detail::Swizzle<3, T, 1, 0, 2, 0> yxzx, vuwu, grbr;
        detail::Swizzle<3, T, 1, 0, 2, 1> yxzy, vuwv, grbg;
        detail::Swizzle<3, T, 1, 0, 2, 2> yxzz, vuww, grbb;
        detail::Swizzle<3, T, 1, 1, 0, 0> yyxx, vvuu, ggrr;
        detail::Swizzle<3, T, 1, 1, 0, 1> yyxy, vvuv, ggrg;
        detail::Swizzle<3, T, 1, 1, 0, 2> yyxz, vvuw, ggrb;
        detail::Swizzle<3, T, 1, 1, 1, 0> yyyx, vvvu, gggr;
        detail::Swizzle<3, T, 1, 1, 1, 1> yyyy, vvvv, gggg;
        detail::Swizzle<3, T, 1, 1, 1, 2> yyyz, vvvw, gggb;
        detail::Swizzle<3, T, 1, 1, 2, 0> yyzx, vvwu, ggbr;
        detail::Swizzle<3, T, 1, 1, 2, 1> yyzy, vvwv, ggbg;
        detail::Swizzle<3, T, 1, 1, 2, 2> yyzz, vvww, ggbb;
        detail::Swizzle<3, T, 1, 2, 0, 0> yzxx, vwuu, gbrr;
        detail::Swizzle<3, T, 1, 2, 0, 1> yzxy, vwuv, gbrg;
        detail::Swizzle<3, T, 1, 2, 0, 2> yzxz, vwuw, gbrb;
        detail::Swizzle<3, T, 1, 2, 1, 0> yzyx, vwvu, gbgr;
        detail::Swizzle<3, T, 1, 2, 1, 1> yzyy, vwvv, gbgg;
        detail::Swizzle<3, T, 1, 2, 1, 2> yzyz, vwvw, gbgb;
        detail::Swizzle<3, T, 1, 2, 2, 0> yzzx, vwwu, gbbr;
        detail::Swizzle<3, T, 1, 2, 2, 1> yzzy, vwwv, gbbg;
        detail::Swizzle<3, T, 1, 2, 2, 2> yzzz, vwww, gbbb;
        detail::Swizzle<3, T, 2, 0, 0, 0> zxxx, wuuu, brrr;
        detail::Swizzle<3, T, 2, 0, 0, 1> zxxy, wuuv, brrg;
        detail::Swizzle<3, T, 2, 0, 0, 2> zxxz, wuuw, brrb;
        detail::Swizzle<3, T, 2, 0, 1, 0> zxyx, wuvu, brgr;
        detail::Swizzle<3, T, 2, 0, 1, 1> zxyy, wuvv, brgg;
        detail::Swizzle<3, T, 2, 0, 1, 2> zxyz, wuvw, brgb;
        detail::Swizzle<3, T, 2, 0, 2, 0> zxzx, wuwu, brbr;
        detail::Swizzle<3, T, 2, 0, 2, 1> zxzy, wuwv, brbg;
        detail::Swizzle<3, T, 2, 0, 2, 2> zxzz, wuww, brbb;
        detail::Swizzle<3, T, 2, 1, 0, 0> zyxx, wvuu, bgrr;
        detail::Swizzle<3, T, 2, 1, 0, 1> zyxy, wvuv, bgrg;
        detail::Swizzle<3, T, 2, 1, 0, 2> zyxz, wvuw, bgrb;
        detail::Swizzle<3, T, 2, 1, 1, 0> zyyx, wvvu, bggr;
        detail::Swizzle<3, T, 2, 1, 1, 1> zyyy, wvvv, bggg;
        detail::Swizzle<3, T, 2, 1, 1, 2> zyyz, wvvw, bggb;
        detail::Swizzle<3, T, 2, 1, 2, 0> zyzx, wvwu, bgbr;
        detail::Swizzle<3, T, 2, 1, 2, 1> zyzy, wvwv, bgbg;
        detail::Swizzle<3, T, 2, 1, 2, 2> zyzz, wvww, bgbb;
        detail::Swizzle<3, T, 2, 2, 0, 0> zzxx, wwuu, bbrr;
        detail::Swizzle<3, T, 2, 2, 0, 1> zzxy, wwuv, bbrg;
        detail::Swizzle<3, T, 2, 2, 0, 2> zzxz, wwuw, bbrb;
        detail::Swizzle<3, T, 2, 2, 1, 0> zzyx, wwvu, bbgr;
        detail::Swizzle<3, T, 2, 2, 1, 1> zzyy, wwvv, bbgg;
        detail::Swizzle<3, T, 2, 2, 1, 2> zzyz, wwvw, bbgb;
        detail::Swizzle<3, T, 2, 2, 2, 0> zzzx, wwwu, bbbr;
        detail::Swizzle<3, T, 2, 2, 2, 1> zzzy, wwwv, bbbg;
        detail::Swizzle<3, T, 2, 2, 2, 2> zzzz, wwww, bbbb;
    };
};


template <detail::numeric T>
struct Vector<4, T> : detail::VectorBase<4, T>, detail::MutableBase {
    using detail::VectorBase<4, T>::dim;
    using typename detail::VectorBase<4, T>::element_type;


    using detail::VectorBase<4, T>::VectorBase;


    template <std::derived_from<detail::Base> V>
        requires(V::dim == 3 && std::is_same_v<typename V::element_type, T>)
    constexpr Vector(T e, const V& v) noexcept : data{e, v[0], v[1], v[2]} {}

    template <std::derived_from<detail::Base> V>
        requires(V::dim == 3 && std::is_same_v<typename V::element_type, T>)
    constexpr Vector(const V& v, T e) noexcept : data{v[0], v[1], v[2], e} {}


    template <std::derived_from<detail::Base> V>
        requires(V::dim == 2 && std::is_same_v<typename V::element_type, T>)
    constexpr Vector(T e0, T e1, const V& v) noexcept : Vector(e0, e1, v[0], v[1]) {}

    template <std::derived_from<detail::Base> V>
        requires(V::dim == 2 && std::is_same_v<typename V::element_type, T>)
    constexpr Vector(T e0, const V& v, T e1) noexcept : Vector(e0, v[0], v[1], e1) {}

    template <std::derived_from<detail::Base> V>
        requires(V::dim == 2 && std::is_same_v<typename V::element_type, T>)
    constexpr Vector(const V& v, T e0, T e1) noexcept : Vector(v[0], v[1], e0, e1) {}


    template <std::derived_from<detail::Base> V, std::derived_from<detail::Base> W>
        requires(V::dim == 2 && W::dim == 2 && std::is_same_v<typename V::element_type, typename W::element_type>)
    constexpr Vector(const V& v, const W& w) noexcept : data{v[0], v[1], w[0], w[1]} {}


    constexpr auto& operator=(const Vector& v) noexcept {
        if (this != &v) {
            std::copy_n(v.data, dim, data);
        }
        return *this;
    }

    using detail::MutableBase::operator=;


    union {
        T data[4];
        struct {
            T x, y, z, w;
        };
        struct {
            T r, g, b, a;
        };
        detail::Swizzle<4, T, 0, 0> xx, rr;
        detail::Swizzle<4, T, 0, 1> xy, rg;
        detail::Swizzle<4, T, 0, 2> xz, rb;
        detail::Swizzle<4, T, 0, 3> xw, ra;
        detail::Swizzle<4, T, 1, 0> yx, gr;
        detail::Swizzle<4, T, 1, 1> yy, gg;
        detail::Swizzle<4, T, 1, 2> yz, gb;
        detail::Swizzle<4, T, 1, 3> yw, ga;
        detail::Swizzle<4, T, 2, 0> zx, br;
        detail::Swizzle<4, T, 2, 1> zy, bg;
        detail::Swizzle<4, T, 2, 2> zz, bb;
        detail::Swizzle<4, T, 2, 3> zw, ba;
        detail::Swizzle<4, T, 3, 0> wx, ar;
        detail::Swizzle<4, T, 3, 1> wy, ag;
        detail::Swizzle<4, T, 3, 2> wz, ab;
        detail::Swizzle<4, T, 3, 3> ww, aa;
        detail::Swizzle<4, T, 0, 0, 0> xxx, rrr;
        detail::Swizzle<4, T, 0, 0, 1> xxy, rrg;
        detail::Swizzle<4, T, 0, 0, 2> xxz, rrb;
        detail::Swizzle<4, T, 0, 0, 3> xxw, rra;
        detail::Swizzle<4, T, 0, 1, 0> xyx, rgr;
        detail::Swizzle<4, T, 0, 1, 1> xyy, rgg;
        detail::Swizzle<4, T, 0, 1, 2> xyz, rgb;
        detail::Swizzle<4, T, 0, 1, 3> xyw, rga;
        detail::Swizzle<4, T, 0, 2, 0> xzx, rbr;
        detail::Swizzle<4, T, 0, 2, 1> xzy, rbg;
        detail::Swizzle<4, T, 0, 2, 2> xzz, rbb;
        detail::Swizzle<4, T, 0, 2, 3> xzw, rba;
        detail::Swizzle<4, T, 0, 3, 0> xwx, rar;
        detail::Swizzle<4, T, 0, 3, 1> xwy, rag;
        detail::Swizzle<4, T, 0, 3, 2> xwz, rab;
        detail::Swizzle<4, T, 0, 3, 3> xww, raa;
        detail::Swizzle<4, T, 1, 0, 0> yxx, grr;
        detail::Swizzle<4, T, 1, 0, 1> yxy, grg;
        detail::Swizzle<4, T, 1, 0, 2> yxz, grb;
        detail::Swizzle<4, T, 1, 0, 3> yxw, gra;
        detail::Swizzle<4, T, 1, 1, 0> yyx, ggr;
        detail::Swizzle<4, T, 1, 1, 1> yyy, ggg;
        detail::Swizzle<4, T, 1, 1, 2> yyz, ggb;
        detail::Swizzle<4, T, 1, 1, 3> yyw, gga;
        detail::Swizzle<4, T, 1, 2, 0> yzx, gbr;
        detail::Swizzle<4, T, 1, 2, 1> yzy, gbg;
        detail::Swizzle<4, T, 1, 2, 2> yzz, gbb;
        detail::Swizzle<4, T, 1, 2, 3> yzw, gba;
        detail::Swizzle<4, T, 1, 3, 0> ywx, gar;
        detail::Swizzle<4, T, 1, 3, 1> ywy, gag;
        detail::Swizzle<4, T, 1, 3, 2> ywz, gab;
        detail::Swizzle<4, T, 1, 3, 3> yww, gaa;
        detail::Swizzle<4, T, 2, 0, 0> zxx, brr;
        detail::Swizzle<4, T, 2, 0, 1> zxy, brg;
        detail::Swizzle<4, T, 2, 0, 2> zxz, brb;
        detail::Swizzle<4, T, 2, 0, 3> zxw, bra;
        detail::Swizzle<4, T, 2, 1, 0> zyx, bgr;
        detail::Swizzle<4, T, 2, 1, 1> zyy, bgg;
        detail::Swizzle<4, T, 2, 1, 2> zyz, bgb;
        detail::Swizzle<4, T, 2, 1, 3> zyw, bga;
        detail::Swizzle<4, T, 2, 2, 0> zzx, bbr;
        detail::Swizzle<4, T, 2, 2, 1> zzy, bbg;
        detail::Swizzle<4, T, 2, 2, 2> zzz, bbb;
        detail::Swizzle<4, T, 2, 2, 3> zzw, bba;
        detail::Swizzle<4, T, 2, 3, 0> zwx, bar;
        detail::Swizzle<4, T, 2, 3, 1> zwy, bag;
        detail::Swizzle<4, T, 2, 3, 2> zwz, bab;
        detail::Swizzle<4, T, 2, 3, 3> zww, baa;
        detail::Swizzle<4, T, 3, 0, 0> wxx, arr;
        detail::Swizzle<4, T, 3, 0, 1> wxy, arg;
        detail::Swizzle<4, T, 3, 0, 2> wxz, arb;
        detail::Swizzle<4, T, 3, 0, 3> wxw, ara;
        detail::Swizzle<4, T, 3, 1, 0> wyx, agr;
        detail::Swizzle<4, T, 3, 1, 1> wyy, agg;
        detail::Swizzle<4, T, 3, 1, 2> wyz, agb;
        detail::Swizzle<4, T, 3, 1, 3> wyw, aga;
        detail::Swizzle<4, T, 3, 2, 0> wzx, abr;
        detail::Swizzle<4, T, 3, 2, 1> wzy, abg;
        detail::Swizzle<4, T, 3, 2, 2> wzz, abb;
        detail::Swizzle<4, T, 3, 2, 3> wzw, aba;
        detail::Swizzle<4, T, 3, 3, 0> wwx, aar;
        detail::Swizzle<4, T, 3, 3, 1> wwy, aag;
        detail::Swizzle<4, T, 3, 3, 2> wwz, aab;
        detail::Swizzle<4, T, 3, 3, 3> www, aaa;
        detail::Swizzle<4, T, 0, 0, 0, 0> xxxx, rrrr;
        detail::Swizzle<4, T, 0, 0, 0, 1> xxxy, rrrg;
        detail::Swizzle<4, T, 0, 0, 0, 2> xxxz, rrrb;
        detail::Swizzle<4, T, 0, 0, 0, 3> xxxw, rrra;
        detail::Swizzle<4, T, 0, 0, 1, 0> xxyx, rrgr;
        detail::Swizzle<4, T, 0, 0, 1, 1> xxyy, rrgg;
        detail::Swizzle<4, T, 0, 0, 1, 2> xxyz, rrgb;
        detail::Swizzle<4, T, 0, 0, 1, 3> xxyw, rrga;
        detail::Swizzle<4, T, 0, 0, 2, 0> xxzx, rrbr;
        detail::Swizzle<4, T, 0, 0, 2, 1> xxzy, rrbg;
        detail::Swizzle<4, T, 0, 0, 2, 2> xxzz, rrbb;
        detail::Swizzle<4, T, 0, 0, 2, 3> xxzw, rrba;
        detail::Swizzle<4, T, 0, 0, 3, 0> xxwx, rrar;
        detail::Swizzle<4, T, 0, 0, 3, 1> xxwy, rrag;
        detail::Swizzle<4, T, 0, 0, 3, 2> xxwz, rrab;
        detail::Swizzle<4, T, 0, 0, 3, 3> xxww, rraa;
        detail::Swizzle<4, T, 0, 1, 0, 0> xyxx, rgrr;
        detail::Swizzle<4, T, 0, 1, 0, 1> xyxy, rgrg;
        detail::Swizzle<4, T, 0, 1, 0, 2> xyxz, rgrb;
        detail::Swizzle<4, T, 0, 1, 0, 3> xyxw, rgra;
        detail::Swizzle<4, T, 0, 1, 1, 0> xyyx, rggr;
        detail::Swizzle<4, T, 0, 1, 1, 1> xyyy, rggg;
        detail::Swizzle<4, T, 0, 1, 1, 2> xyyz, rggb;
        detail::Swizzle<4, T, 0, 1, 1, 3> xyyw, rgga;
        detail::Swizzle<4, T, 0, 1, 2, 0> xyzx, rgbr;
        detail::Swizzle<4, T, 0, 1, 2, 1> xyzy, rgbg;
        detail::Swizzle<4, T, 0, 1, 2, 2> xyzz, rgbb;
        detail::Swizzle<4, T, 0, 1, 2, 3> xyzw, rgba;
        detail::Swizzle<4, T, 0, 1, 3, 0> xywx, rgar;
        detail::Swizzle<4, T, 0, 1, 3, 1> xywy, rgag;
        detail::Swizzle<4, T, 0, 1, 3, 2> xywz, rgab;
        detail::Swizzle<4, T, 0, 1, 3, 3> xyww, rgaa;
        detail::Swizzle<4, T, 0, 2, 0, 0> xzxx, rbrr;
        detail::Swizzle<4, T, 0, 2, 0, 1> xzxy, rbrg;
        detail::Swizzle<4, T, 0, 2, 0, 2> xzxz, rbrb;
        detail::Swizzle<4, T, 0, 2, 0, 3> xzxw, rbra;
        detail::Swizzle<4, T, 0, 2, 1, 0> xzyx, rbgr;
        detail::Swizzle<4, T, 0, 2, 1, 1> xzyy, rbgg;
        detail::Swizzle<4, T, 0, 2, 1, 2> xzyz, rbgb;
        detail::Swizzle<4, T, 0, 2, 1, 3> xzyw, rbga;
        detail::Swizzle<4, T, 0, 2, 2, 0> xzzx, rbbr;
        detail::Swizzle<4, T, 0, 2, 2, 1> xzzy, rbbg;
        detail::Swizzle<4, T, 0, 2, 2, 2> xzzz, rbbb;
        detail::Swizzle<4, T, 0, 2, 2, 3> xzzw, rbba;
        detail::Swizzle<4, T, 0, 2, 3, 0> xzwx, rbar;
        detail::Swizzle<4, T, 0, 2, 3, 1> xzwy, rbag;
        detail::Swizzle<4, T, 0, 2, 3, 2> xzwz, rbab;
        detail::Swizzle<4, T, 0, 2, 3, 3> xzww, rbaa;
        detail::Swizzle<4, T, 0, 3, 0, 0> xwxx, rarr;
        detail::Swizzle<4, T, 0, 3, 0, 1> xwxy, rarg;
        detail::Swizzle<4, T, 0, 3, 0, 2> xwxz, rarb;
        detail::Swizzle<4, T, 0, 3, 0, 3> xwxw, rara;
        detail::Swizzle<4, T, 0, 3, 1, 0> xwyx, ragr;
        detail::Swizzle<4, T, 0, 3, 1, 1> xwyy, ragg;
        detail::Swizzle<4, T, 0, 3, 1, 2> xwyz, ragb;
        detail::Swizzle<4, T, 0, 3, 1, 3> xwyw, raga;
        detail::Swizzle<4, T, 0, 3, 2, 0> xwzx, rabr;
        detail::Swizzle<4, T, 0, 3, 2, 1> xwzy, rabg;
        detail::Swizzle<4, T, 0, 3, 2, 2> xwzz, rabb;
        detail::Swizzle<4, T, 0, 3, 2, 3> xwzw, raba;
        detail::Swizzle<4, T, 0, 3, 3, 0> xwwx, raar;
        detail::Swizzle<4, T, 0, 3, 3, 1> xwwy, raag;
        detail::Swizzle<4, T, 0, 3, 3, 2> xwwz, raab;
        detail::Swizzle<4, T, 0, 3, 3, 3> xwww, raaa;
        detail::Swizzle<4, T, 1, 0, 0, 0> yxxx, grrr;
        detail::Swizzle<4, T, 1, 0, 0, 1> yxxy, grrg;
        detail::Swizzle<4, T, 1, 0, 0, 2> yxxz, grrb;
        detail::Swizzle<4, T, 1, 0, 0, 3> yxxw, grra;
        detail::Swizzle<4, T, 1, 0, 1, 0> yxyx, grgr;
        detail::Swizzle<4, T, 1, 0, 1, 1> yxyy, grgg;
        detail::Swizzle<4, T, 1, 0, 1, 2> yxyz, grgb;
        detail::Swizzle<4, T, 1, 0, 1, 3> yxyw, grga;
        detail::Swizzle<4, T, 1, 0, 2, 0> yxzx, grbr;
        detail::Swizzle<4, T, 1, 0, 2, 1> yxzy, grbg;
        detail::Swizzle<4, T, 1, 0, 2, 2> yxzz, grbb;
        detail::Swizzle<4, T, 1, 0, 2, 3> yxzw, grba;
        detail::Swizzle<4, T, 1, 0, 3, 0> yxwx, grar;
        detail::Swizzle<4, T, 1, 0, 3, 1> yxwy, grag;
        detail::Swizzle<4, T, 1, 0, 3, 2> yxwz, grab;
        detail::Swizzle<4, T, 1, 0, 3, 3> yxww, graa;
        detail::Swizzle<4, T, 1, 1, 0, 0> yyxx, ggrr;
        detail::Swizzle<4, T, 1, 1, 0, 1> yyxy, ggrg;
        detail::Swizzle<4, T, 1, 1, 0, 2> yyxz, ggrb;
        detail::Swizzle<4, T, 1, 1, 0, 3> yyxw, ggra;
        detail::Swizzle<4, T, 1, 1, 1, 0> yyyx, gggr;
        detail::Swizzle<4, T, 1, 1, 1, 1> yyyy, gggg;
        detail::Swizzle<4, T, 1, 1, 1, 2> yyyz, gggb;
        detail::Swizzle<4, T, 1, 1, 1, 3> yyyw, ggga;
        detail::Swizzle<4, T, 1, 1, 2, 0> yyzx, ggbr;
        detail::Swizzle<4, T, 1, 1, 2, 1> yyzy, ggbg;
        detail::Swizzle<4, T, 1, 1, 2, 2> yyzz, ggbb;
        detail::Swizzle<4, T, 1, 1, 2, 3> yyzw, ggba;
        detail::Swizzle<4, T, 1, 1, 3, 0> yywx, ggar;
        detail::Swizzle<4, T, 1, 1, 3, 1> yywy, ggag;
        detail::Swizzle<4, T, 1, 1, 3, 2> yywz, ggab;
        detail::Swizzle<4, T, 1, 1, 3, 3> yyww, ggaa;
        detail::Swizzle<4, T, 1, 2, 0, 0> yzxx, gbrr;
        detail::Swizzle<4, T, 1, 2, 0, 1> yzxy, gbrg;
        detail::Swizzle<4, T, 1, 2, 0, 2> yzxz, gbrb;
        detail::Swizzle<4, T, 1, 2, 0, 3> yzxw, gbra;
        detail::Swizzle<4, T, 1, 2, 1, 0> yzyx, gbgr;
        detail::Swizzle<4, T, 1, 2, 1, 1> yzyy, gbgg;
        detail::Swizzle<4, T, 1, 2, 1, 2> yzyz, gbgb;
        detail::Swizzle<4, T, 1, 2, 1, 3> yzyw, gbga;
        detail::Swizzle<4, T, 1, 2, 2, 0> yzzx, gbbr;
        detail::Swizzle<4, T, 1, 2, 2, 1> yzzy, gbbg;
        detail::Swizzle<4, T, 1, 2, 2, 2> yzzz, gbbb;
        detail::Swizzle<4, T, 1, 2, 2, 3> yzzw, gbba;
        detail::Swizzle<4, T, 1, 2, 3, 0> yzwx, gbar;
        detail::Swizzle<4, T, 1, 2, 3, 1> yzwy, gbag;
        detail::Swizzle<4, T, 1, 2, 3, 2> yzwz, gbab;
        detail::Swizzle<4, T, 1, 2, 3, 3> yzww, gbaa;
        detail::Swizzle<4, T, 1, 3, 0, 0> ywxx, garr;
        detail::Swizzle<4, T, 1, 3, 0, 1> ywxy, garg;
        detail::Swizzle<4, T, 1, 3, 0, 2> ywxz, garb;
        detail::Swizzle<4, T, 1, 3, 0, 3> ywxw, gara;
        detail::Swizzle<4, T, 1, 3, 1, 0> ywyx, gagr;
        detail::Swizzle<4, T, 1, 3, 1, 1> ywyy, gagg;
        detail::Swizzle<4, T, 1, 3, 1, 2> ywyz, gagb;
        detail::Swizzle<4, T, 1, 3, 1, 3> ywyw, gaga;
        detail::Swizzle<4, T, 1, 3, 2, 0> ywzx, gabr;
        detail::Swizzle<4, T, 1, 3, 2, 1> ywzy, gabg;
        detail::Swizzle<4, T, 1, 3, 2, 2> ywzz, gabb;
        detail::Swizzle<4, T, 1, 3, 2, 3> ywzw, gaba;
        detail::Swizzle<4, T, 1, 3, 3, 0> ywwx, gaar;
        detail::Swizzle<4, T, 1, 3, 3, 1> ywwy, gaag;
        detail::Swizzle<4, T, 1, 3, 3, 2> ywwz, gaab;
        detail::Swizzle<4, T, 1, 3, 3, 3> ywww, gaaa;
        detail::Swizzle<4, T, 2, 0, 0, 0> zxxx, brrr;
        detail::Swizzle<4, T, 2, 0, 0, 1> zxxy, brrg;
        detail::Swizzle<4, T, 2, 0, 0, 2> zxxz, brrb;
        detail::Swizzle<4, T, 2, 0, 0, 3> zxxw, brra;
        detail::Swizzle<4, T, 2, 0, 1, 0> zxyx, brgr;
        detail::Swizzle<4, T, 2, 0, 1, 1> zxyy, brgg;
        detail::Swizzle<4, T, 2, 0, 1, 2> zxyz, brgb;
        detail::Swizzle<4, T, 2, 0, 1, 3> zxyw, brga;
        detail::Swizzle<4, T, 2, 0, 2, 0> zxzx, brbr;
        detail::Swizzle<4, T, 2, 0, 2, 1> zxzy, brbg;
        detail::Swizzle<4, T, 2, 0, 2, 2> zxzz, brbb;
        detail::Swizzle<4, T, 2, 0, 2, 3> zxzw, brba;
        detail::Swizzle<4, T, 2, 0, 3, 0> zxwx, brar;
        detail::Swizzle<4, T, 2, 0, 3, 1> zxwy, brag;
        detail::Swizzle<4, T, 2, 0, 3, 2> zxwz, brab;
        detail::Swizzle<4, T, 2, 0, 3, 3> zxww, braa;
        detail::Swizzle<4, T, 2, 1, 0, 0> zyxx, bgrr;
        detail::Swizzle<4, T, 2, 1, 0, 1> zyxy, bgrg;
        detail::Swizzle<4, T, 2, 1, 0, 2> zyxz, bgrb;
        detail::Swizzle<4, T, 2, 1, 0, 3> zyxw, bgra;
        detail::Swizzle<4, T, 2, 1, 1, 0> zyyx, bggr;
        detail::Swizzle<4, T, 2, 1, 1, 1> zyyy, bggg;
        detail::Swizzle<4, T, 2, 1, 1, 2> zyyz, bggb;
        detail::Swizzle<4, T, 2, 1, 1, 3> zyyw, bgga;
        detail::Swizzle<4, T, 2, 1, 2, 0> zyzx, bgbr;
        detail::Swizzle<4, T, 2, 1, 2, 1> zyzy, bgbg;
        detail::Swizzle<4, T, 2, 1, 2, 2> zyzz, bgbb;
        detail::Swizzle<4, T, 2, 1, 2, 3> zyzw, bgba;
        detail::Swizzle<4, T, 2, 1, 3, 0> zywx, bgar;
        detail::Swizzle<4, T, 2, 1, 3, 1> zywy, bgag;
        detail::Swizzle<4, T, 2, 1, 3, 2> zywz, bgab;
        detail::Swizzle<4, T, 2, 1, 3, 3> zyww, bgaa;
        detail::Swizzle<4, T, 2, 2, 0, 0> zzxx, bbrr;
        detail::Swizzle<4, T, 2, 2, 0, 1> zzxy, bbrg;
        detail::Swizzle<4, T, 2, 2, 0, 2> zzxz, bbrb;
        detail::Swizzle<4, T, 2, 2, 0, 3> zzxw, bbra;
        detail::Swizzle<4, T, 2, 2, 1, 0> zzyx, bbgr;
        detail::Swizzle<4, T, 2, 2, 1, 1> zzyy, bbgg;
        detail::Swizzle<4, T, 2, 2, 1, 2> zzyz, bbgb;
        detail::Swizzle<4, T, 2, 2, 1, 3> zzyw, bbga;
        detail::Swizzle<4, T, 2, 2, 2, 0> zzzx, bbbr;
        detail::Swizzle<4, T, 2, 2, 2, 1> zzzy, bbbg;
        detail::Swizzle<4, T, 2, 2, 2, 2> zzzz, bbbb;
        detail::Swizzle<4, T, 2, 2, 2, 3> zzzw, bbba;
        detail::Swizzle<4, T, 2, 2, 3, 0> zzwx, bbar;
        detail::Swizzle<4, T, 2, 2, 3, 1> zzwy, bbag;
        detail::Swizzle<4, T, 2, 2, 3, 2> zzwz, bbab;
        detail::Swizzle<4, T, 2, 2, 3, 3> zzww, bbaa;
        detail::Swizzle<4, T, 2, 3, 0, 0> zwxx, barr;
        detail::Swizzle<4, T, 2, 3, 0, 1> zwxy, barg;
        detail::Swizzle<4, T, 2, 3, 0, 2> zwxz, barb;
        detail::Swizzle<4, T, 2, 3, 0, 3> zwxw, bara;
        detail::Swizzle<4, T, 2, 3, 1, 0> zwyx, bagr;
        detail::Swizzle<4, T, 2, 3, 1, 1> zwyy, bagg;
        detail::Swizzle<4, T, 2, 3, 1, 2> zwyz, bagb;
        detail::Swizzle<4, T, 2, 3, 1, 3> zwyw, baga;
        detail::Swizzle<4, T, 2, 3, 2, 0> zwzx, babr;
        detail::Swizzle<4, T, 2, 3, 2, 1> zwzy, babg;
        detail::Swizzle<4, T, 2, 3, 2, 2> zwzz, babb;
        detail::Swizzle<4, T, 2, 3, 2, 3> zwzw, baba;
        detail::Swizzle<4, T, 2, 3, 3, 0> zwwx, baar;
        detail::Swizzle<4, T, 2, 3, 3, 1> zwwy, baag;
        detail::Swizzle<4, T, 2, 3, 3, 2> zwwz, baab;
        detail::Swizzle<4, T, 2, 3, 3, 3> zwww, baaa;
        detail::Swizzle<4, T, 3, 0, 0, 0> wxxx, arrr;
        detail::Swizzle<4, T, 3, 0, 0, 1> wxxy, arrg;
        detail::Swizzle<4, T, 3, 0, 0, 2> wxxz, arrb;
        detail::Swizzle<4, T, 3, 0, 0, 3> wxxw, arra;
        detail::Swizzle<4, T, 3, 0, 1, 0> wxyx, argr;
        detail::Swizzle<4, T, 3, 0, 1, 1> wxyy, argg;
        detail::Swizzle<4, T, 3, 0, 1, 2> wxyz, argb;
        detail::Swizzle<4, T, 3, 0, 1, 3> wxyw, arga;
        detail::Swizzle<4, T, 3, 0, 2, 0> wxzx, arbr;
        detail::Swizzle<4, T, 3, 0, 2, 1> wxzy, arbg;
        detail::Swizzle<4, T, 3, 0, 2, 2> wxzz, arbb;
        detail::Swizzle<4, T, 3, 0, 2, 3> wxzw, arba;
        detail::Swizzle<4, T, 3, 0, 3, 0> wxwx, arar;
        detail::Swizzle<4, T, 3, 0, 3, 1> wxwy, arag;
        detail::Swizzle<4, T, 3, 0, 3, 2> wxwz, arab;
        detail::Swizzle<4, T, 3, 0, 3, 3> wxww, araa;
        detail::Swizzle<4, T, 3, 1, 0, 0> wyxx, agrr;
        detail::Swizzle<4, T, 3, 1, 0, 1> wyxy, agrg;
        detail::Swizzle<4, T, 3, 1, 0, 2> wyxz, agrb;
        detail::Swizzle<4, T, 3, 1, 0, 3> wyxw, agra;
        detail::Swizzle<4, T, 3, 1, 1, 0> wyyx, aggr;
        detail::Swizzle<4, T, 3, 1, 1, 1> wyyy, aggg;
        detail::Swizzle<4, T, 3, 1, 1, 2> wyyz, aggb;
        detail::Swizzle<4, T, 3, 1, 1, 3> wyyw, agga;
        detail::Swizzle<4, T, 3, 1, 2, 0> wyzx, agbr;
        detail::Swizzle<4, T, 3, 1, 2, 1> wyzy, agbg;
        detail::Swizzle<4, T, 3, 1, 2, 2> wyzz, agbb;
        detail::Swizzle<4, T, 3, 1, 2, 3> wyzw, agba;
        detail::Swizzle<4, T, 3, 1, 3, 0> wywx, agar;
        detail::Swizzle<4, T, 3, 1, 3, 1> wywy, agag;
        detail::Swizzle<4, T, 3, 1, 3, 2> wywz, agab;
        detail::Swizzle<4, T, 3, 1, 3, 3> wyww, agaa;
        detail::Swizzle<4, T, 3, 2, 0, 0> wzxx, abrr;
        detail::Swizzle<4, T, 3, 2, 0, 1> wzxy, abrg;
        detail::Swizzle<4, T, 3, 2, 0, 2> wzxz, abrb;
        detail::Swizzle<4, T, 3, 2, 0, 3> wzxw, abra;
        detail::Swizzle<4, T, 3, 2, 1, 0> wzyx, abgr;
        detail::Swizzle<4, T, 3, 2, 1, 1> wzyy, abgg;
        detail::Swizzle<4, T, 3, 2, 1, 2> wzyz, abgb;
        detail::Swizzle<4, T, 3, 2, 1, 3> wzyw, abga;
        detail::Swizzle<4, T, 3, 2, 2, 0> wzzx, abbr;
        detail::Swizzle<4, T, 3, 2, 2, 1> wzzy, abbg;
        detail::Swizzle<4, T, 3, 2, 2, 2> wzzz, abbb;
        detail::Swizzle<4, T, 3, 2, 2, 3> wzzw, abba;
        detail::Swizzle<4, T, 3, 2, 3, 0> wzwx, abar;
        detail::Swizzle<4, T, 3, 2, 3, 1> wzwy, abag;
        detail::Swizzle<4, T, 3, 2, 3, 2> wzwz, abab;
        detail::Swizzle<4, T, 3, 2, 3, 3> wzww, abaa;
        detail::Swizzle<4, T, 3, 3, 0, 0> wwxx, aarr;
        detail::Swizzle<4, T, 3, 3, 0, 1> wwxy, aarg;
        detail::Swizzle<4, T, 3, 3, 0, 2> wwxz, aarb;
        detail::Swizzle<4, T, 3, 3, 0, 3> wwxw, aara;
        detail::Swizzle<4, T, 3, 3, 1, 0> wwyx, aagr;
        detail::Swizzle<4, T, 3, 3, 1, 1> wwyy, aagg;
        detail::Swizzle<4, T, 3, 3, 1, 2> wwyz, aagb;
        detail::Swizzle<4, T, 3, 3, 1, 3> wwyw, aaga;
        detail::Swizzle<4, T, 3, 3, 2, 0> wwzx, aabr;
        detail::Swizzle<4, T, 3, 3, 2, 1> wwzy, aabg;
        detail::Swizzle<4, T, 3, 3, 2, 2> wwzz, aabb;
        detail::Swizzle<4, T, 3, 3, 2, 3> wwzw, aaba;
        detail::Swizzle<4, T, 3, 3, 3, 0> wwwx, aaar;
        detail::Swizzle<4, T, 3, 3, 3, 1> wwwy, aaag;
        detail::Swizzle<4, T, 3, 3, 3, 2> wwwz, aaab;
        detail::Swizzle<4, T, 3, 3, 3, 3> wwww, aaaa;
    };
};


template <detail::numeric T>
using Vector2 = Vector<2, T>;

template <detail::numeric T>
using Vector3 = Vector<3, T>;

template <detail::numeric T>
using Vector4 = Vector<4, T>;


template <size_t N, detail::numeric T>
Vector(const T (&arr)[N]) -> Vector<N, T>;

template <detail::numeric T, std::same_as<T>... Ts>
Vector(T, Ts...) -> Vector<1 + sizeof...(Ts), T>;

template <std::derived_from<detail::Base> V>
Vector(V) -> Vector<V::dim, typename V::element_type>;

template <detail::numeric T, std::derived_from<detail::Base> V>
    requires std::is_same_v<typename V::element_type, T>
Vector(T, V) -> Vector<1 + V::dim, T>;

template <detail::numeric T, std::derived_from<detail::Base> V>
    requires std::is_same_v<typename V::element_type, T>
Vector(V, T) -> Vector<1 + V::dim, T>;

template <detail::numeric T, std::derived_from<detail::Base> V>
    requires std::is_same_v<typename V::element_type, T>
Vector(T, T, V) -> Vector<2 + V::dim, T>;

template <detail::numeric T, std::derived_from<detail::Base> V>
    requires std::is_same_v<typename V::element_type, T>
Vector(T, V, T) -> Vector<2 + V::dim, T>;

template <detail::numeric T, std::derived_from<detail::Base> V>
    requires std::is_same_v<typename V::element_type, T>
Vector(V, T, T) -> Vector<2 + V::dim, T>;

template <std::derived_from<detail::Base> V, std::derived_from<detail::Base> W>
    requires(V::dim == 2 && W::dim == 2 && std::is_same_v<typename V::element_type, typename W::element_type>)
Vector(V, W) -> Vector<4, typename V::element_type>;
