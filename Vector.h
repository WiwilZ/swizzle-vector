#pragma once

#include <type_traits>


#ifdef _MSC_VER
#pragma warning(push) 
#pragma warning(disable: 26495)
#endif


template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <std::size_t N, arithmetic T>
struct Vector;

namespace detail {
    //Vector和Swizzle的基类，实现了共有的方法
    template <class Derived, std::size_t... I>
    struct Base {
        constexpr auto operator[](std::size_t index) const noexcept {
            constexpr std::size_t indices[]{I...};
            return static_cast<const Derived*>(this)->data[indices[index]];
        }
        constexpr auto& operator[](std::size_t index) noexcept {
            constexpr std::size_t indices[]{I...};
            return static_cast<Derived*>(this)->data[indices[index]];
        }


        template <class Derived2, std::size_t... J>
            requires(sizeof...(I) == sizeof...(J))
        constexpr bool equals(const Base<Derived2, J...>& rhs) const noexcept {
            return equals_impl(rhs, std::make_index_sequence<sizeof...(I)>{});
        }
        template <class Derived2, std::size_t... J>
            requires(sizeof...(I) == sizeof...(J))
        constexpr bool not_equals(const Base<Derived2, J...>& rhs) const noexcept {
            return not_equals_impl(rhs, std::make_index_sequence<sizeof...(I)>{});
        }


        constexpr bool all() const noexcept {
            return (... && (*this)[I]);
        }
        constexpr bool any() const noexcept {
            return (... || (*this)[I]);
        }


        constexpr auto operator+() const noexcept { return Vector{+(*this)[I]...}; }
        constexpr auto operator-() const noexcept { return Vector{-(*this)[I]...}; }
        constexpr auto operator~() const noexcept { return Vector{~(*this)[I]...}; }
        constexpr auto operator!() const noexcept { return Vector{!(*this)[I]...}; }


        constexpr auto& operator=(const auto& rhs) noexcept {
            apply_iop(rhs, [](auto& l, auto r) noexcept { l = r; });
            return *static_cast<Derived*>(this);
        }

        constexpr void operator+=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l += r; }); }
        constexpr void operator-=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l -= r; }); }
        constexpr void operator*=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l *= r; }); }
        constexpr void operator/=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l /= r; }); }
        constexpr void operator%=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l %= r; }); }
        constexpr void operator&=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l &= r; }); }
        constexpr void operator|=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l |= r; }); }
        constexpr void operator^=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l ^= r; }); }
        constexpr void operator<<=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l <<= r; }); }
        constexpr void operator>>=(const auto& rhs) noexcept { apply_iop(rhs, [](auto& l, auto r) noexcept { l >>= r; }); }


        constexpr auto operator+(const auto& rhs) const noexcept { return apply_op(*this, rhs, add{}); }
        constexpr auto operator-(const auto& rhs) const noexcept { return apply_op(*this, rhs, sub{}); }
        constexpr auto operator*(const auto& rhs) const noexcept { return apply_op(*this, rhs, mul{}); }
        constexpr auto operator/(const auto& rhs) const noexcept { return apply_op(*this, rhs, div{}); }
        constexpr auto operator%(const auto& rhs) const noexcept { return apply_op(*this, rhs, mod{}); }
        constexpr auto operator&(const auto& rhs) const noexcept { return apply_op(*this, rhs, bit_and{}); }
        constexpr auto operator|(const auto& rhs) const noexcept { return apply_op(*this, rhs, bit_or{}); }
        constexpr auto operator^(const auto& rhs) const noexcept { return apply_op(*this, rhs, bit_xor{}); }
        constexpr auto operator<<(const auto& rhs) const noexcept { return apply_op(*this, rhs, lshift{}); }
        constexpr auto operator>>(const auto& rhs) const noexcept { return apply_op(*this, rhs, rshift{}); }
        constexpr auto operator&&(const auto& rhs) const noexcept { return apply_op(*this, rhs, logical_and{}); }
        constexpr auto operator||(const auto& rhs) const noexcept { return apply_op(*this, rhs, logical_or{}); }
        constexpr auto operator<(const auto& rhs) const noexcept { return apply_op(*this, rhs, less_than{}); }
        constexpr auto operator<=(const auto& rhs) const noexcept { return apply_op(*this, rhs, less_equal{}); }
        constexpr auto operator>(const auto& rhs) const noexcept { return apply_op(*this, rhs, greater_than{}); }
        constexpr auto operator>=(const auto& rhs) const noexcept { return apply_op(*this, rhs, greater_equal{}); }
        constexpr auto operator==(const auto& rhs) const noexcept { return apply_op(*this, rhs, equal{}); }
        constexpr auto operator!=(const auto& rhs) const noexcept { return apply_op(*this, rhs, not_equal{}); }


        friend constexpr auto operator+(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, add{}); }
        friend constexpr auto operator-(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, sub{}); }
        friend constexpr auto operator*(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, mul{}); }
        friend constexpr auto operator/(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, div{}); }
        friend constexpr auto operator%(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, mod{}); }
        friend constexpr auto operator&(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, bit_and{}); }
        friend constexpr auto operator|(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, bit_or{}); }
        friend constexpr auto operator^(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, bit_xor{}); }
        friend constexpr auto operator<<(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, lshift{}); }
        friend constexpr auto operator>>(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, rshift{}); }
        friend constexpr auto operator&&(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, logical_and{}); }
        friend constexpr auto operator||(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, logical_or{}); }
        friend constexpr auto operator<(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, less_than{}); }
        friend constexpr auto operator<=(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, less_equal{}); }
        friend constexpr auto operator>(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, greater_than{}); }
        friend constexpr auto operator>=(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, greater_equal{}); }
        friend constexpr auto operator==(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, equal{}); }
        friend constexpr auto operator!=(arithmetic auto lhs, const Base& rhs) noexcept { return apply_op(lhs, rhs, not_equal{}); }

    private:
        struct add { constexpr auto operator()(auto l, auto r) const noexcept { return l + r; } };
        struct sub { constexpr auto operator()(auto l, auto r) const noexcept { return l - r; } };
        struct mul { constexpr auto operator()(auto l, auto r) const noexcept { return l * r; } };
        struct div { constexpr auto operator()(auto l, auto r) const noexcept { return l / r; } };
        struct mod { constexpr auto operator()(auto l, auto r) const noexcept { return l % r; } };
        struct bit_and { constexpr auto operator()(auto l, auto r) const noexcept { return l & r; } };
        struct bit_or { constexpr auto operator()(auto l, auto r) const noexcept { return l | r; } };
        struct bit_xor { constexpr auto operator()(auto l, auto r) const noexcept { return l ^ r; } };
        struct lshift { constexpr auto operator()(auto l, auto r) const noexcept { return l << r; } };
        struct rshift { constexpr auto operator()(auto l, auto r) const noexcept { return l >> r; } };
        struct logical_and { constexpr auto operator()(auto l, auto r) const noexcept { return l && r; } };
        struct logical_or { constexpr auto operator()(auto l, auto r) const noexcept { return l || r; } };
        struct less_than { constexpr auto operator()(auto l, auto r) const noexcept { return l < r; } };
        struct less_equal { constexpr auto operator()(auto l, auto r) const noexcept { return l <= r; } };
        struct greater_than { constexpr auto operator()(auto l, auto r) const noexcept { return l > r; } };
        struct greater_equal { constexpr auto operator()(auto l, auto r) const noexcept { return l >= r; } };
        struct equal { constexpr auto operator()(auto l, auto r) const noexcept { return l == r; } };
        struct not_equal { constexpr auto operator()(auto l, auto r) const noexcept { return l != r; } };


        template <std::size_t... K>
        constexpr bool equals_impl(const auto& rhs, std::index_sequence<K...>) const noexcept {
            return (... && ((*this)[K] == rhs[K]));
        }
        template <std::size_t... K>
        constexpr bool not_equals_impl(const auto& rhs, std::index_sequence<K...>) const noexcept {
            return (... || ((*this)[K] != rhs[K]));
        }


        constexpr void apply_iop(const auto& rhs, const auto& op) noexcept {
            return apply_iop_impl(rhs, op, std::make_index_sequence<sizeof...(I)>{});
        }
        template <std::size_t... K>
        constexpr void apply_iop_impl(arithmetic auto rhs, const auto& op, std::index_sequence<K...>) noexcept {
            (op((*this)[K], rhs), ...);
        }
        template <class Derived2, std::size_t... J, std::size_t... K>
            requires(sizeof...(I) == sizeof...(J))
        constexpr void apply_iop_impl(const Base<Derived2, J...>& rhs, const auto& op, std::index_sequence<K...>) noexcept {
            decltype(rhs[0]) v[]{rhs[K]...};
            (op((*this)[K], v[K]), ...);
        }


        static constexpr auto apply_op(const auto& lhs, const auto& rhs, const auto& op) noexcept {
            return apply_op_impl(lhs, rhs, op, std::make_index_sequence<sizeof...(I)>{});
        }
        template <std::size_t... K>
        static constexpr auto apply_op_impl(const Base& lhs, arithmetic auto rhs, const auto& op, std::index_sequence<K...>) noexcept {
            return Vector{op(lhs[K], rhs)...};
        }
        template <std::size_t... K>
        static constexpr auto apply_op_impl(arithmetic auto lhs, const Base& rhs, const auto& op, std::index_sequence<K...>) noexcept {
            return Vector{op(lhs, rhs[K])...};
        }
        template <class Derived2, std::size_t... J, std::size_t... K>
            requires(sizeof...(I) == sizeof...(J))
        static constexpr auto apply_op_impl(const Base& lhs, const Base<Derived2, J...>& rhs, const auto& op, std::index_sequence<K...>) noexcept {
            return Vector{op(lhs[K], rhs[K])...};
        }
    };



    //Swizzle属性，N表示其所在Vector的维度，I...为其所在Vector的swizzle组合，sizeof...(I) 不一定等于 N
    template <std::size_t N, arithmetic T, std::size_t... I>
    struct Swizzle : Base<Swizzle<N, T, I...>, I...> {
        using Base<Swizzle<N, T, I...>, I...>::operator=;
        T data[N];
    };
    //限制含有重复元素的组合为只读
    template <std::size_t I0, std::size_t I1, std::size_t I2 = static_cast<std::size_t>(-1), std::size_t I3 = static_cast<std::size_t>(-2)>
    constexpr bool Duplicated = I0 == I1 || I0 == I2 || I0 == I3 || I1 == I2 || I1 == I3 || I2 == I3;

    template <std::size_t N, arithmetic T, std::size_t... I>
    using SwizzleProperty = std::conditional_t<Duplicated<I...>, const Swizzle<N, T, I...>, Swizzle<N, T, I...>>;



    //实现各维度Vector共有的构造函数。对于Vector，I...一定是 0...N-1 的序列
    template <std::size_t N, arithmetic T, std::size_t... I>
    Base<Vector<N, T>, I...> helper(std::index_sequence<I...>);

    template <std::size_t N, arithmetic T>
    using VectorBaseType = decltype(helper<N, T>(std::make_index_sequence<N>{}));

    template <std::size_t N, arithmetic T>
    struct VectorBase : VectorBaseType<N, T> {
        using VectorBaseType<N, T>::operator=;


        constexpr VectorBase() noexcept {
            impl(0, std::make_index_sequence<N>{});
        }

        template <arithmetic... U>
            requires(N == sizeof...(U))
        constexpr VectorBase(U... e) noexcept {
            T v[]{e...};
            impl(v, std::make_index_sequence<N>{});
        }

        constexpr explicit VectorBase(arithmetic auto e) noexcept {
            impl(e, std::make_index_sequence<N>{});
        }

        template <arithmetic U>
        constexpr explicit VectorBase(const U(&v)[N]) noexcept {
            impl(v, std::make_index_sequence<N>{});
        }

        template <class Derived, std::size_t... I>
            requires(N == sizeof...(I))
        constexpr explicit VectorBase(const Base<Derived, I...>& v) noexcept {
            impl(v, std::make_index_sequence<N>{});
        }

        template <class Derived, std::size_t... I>
            requires(sizeof...(I) == N - 1)
        constexpr VectorBase(arithmetic auto e, const detail::Base<Derived, I...>& v) noexcept {
            static_cast<Vector<N, T>*>(this)->data[0] = e;
            impl2(v, std::make_index_sequence<N - 1>{});
        }

        template <class Derived, std::size_t... I>
            requires(sizeof...(I) == N - 1)
        constexpr VectorBase(const detail::Base<Derived, I...>& v, arithmetic auto e) noexcept {
            impl(v, std::make_index_sequence<N - 1>{});
            static_cast<Vector<N, T>*>(this)->data[N - 1] = e;
        }

    private:
        template <std::size_t... K>
        constexpr void impl(arithmetic auto rhs, std::index_sequence<K...>) noexcept {
            ((static_cast<Vector<N, T>*>(this)->data[K] = rhs), ...);
        }
        template <std::size_t... K>
        constexpr void impl(const auto& v, std::index_sequence<K...>) noexcept {
            ((static_cast<Vector<N, T>*>(this)->data[K] = v[K]), ...);
        }
        template <std::size_t... K>
        constexpr void impl2(const auto& v, std::index_sequence<K...>) noexcept {
            ((static_cast<Vector<N, T>*>(this)->data[K + 1] = v[K]), ...);
        }
    };
} // namespace detail



template <arithmetic T>
struct Vector<2, T> : detail::VectorBase<2, T> {
    using detail::VectorBase<2, T>::VectorBase;
    using detail::VectorBase<2, T>::operator=;


    union {
        T data[2];
        struct { T x, y; };
        struct { T u, v; };
        detail::SwizzleProperty<2, T, 0, 0> xx, uu;
        detail::SwizzleProperty<2, T, 0, 1> xy, uv;
        detail::SwizzleProperty<2, T, 1, 0> yx, vu;
        detail::SwizzleProperty<2, T, 1, 1> yy, vv;
        detail::SwizzleProperty<2, T, 0, 0, 0> xxx, uuu;
        detail::SwizzleProperty<2, T, 0, 0, 1> xxy, uuv;
        detail::SwizzleProperty<2, T, 0, 1, 0> xyx, uvu;
        detail::SwizzleProperty<2, T, 0, 1, 1> xyy, uvv;
        detail::SwizzleProperty<2, T, 1, 0, 0> yxx, vuu;
        detail::SwizzleProperty<2, T, 1, 0, 1> yxy, vuv;
        detail::SwizzleProperty<2, T, 1, 1, 0> yyx, vvu;
        detail::SwizzleProperty<2, T, 1, 1, 1> yyy, vvv;
        detail::SwizzleProperty<2, T, 0, 0, 0, 0> xxxx, uuuu;
        detail::SwizzleProperty<2, T, 0, 0, 0, 1> xxxy, uuuv;
        detail::SwizzleProperty<2, T, 0, 0, 1, 0> xxyx, uuvu;
        detail::SwizzleProperty<2, T, 0, 0, 1, 1> xxyy, uuvv;
        detail::SwizzleProperty<2, T, 0, 1, 0, 0> xyxx, uvuu;
        detail::SwizzleProperty<2, T, 0, 1, 0, 1> xyxy, uvuv;
        detail::SwizzleProperty<2, T, 0, 1, 1, 0> xyyx, uvvu;
        detail::SwizzleProperty<2, T, 0, 1, 1, 1> xyyy, uvvv;
        detail::SwizzleProperty<2, T, 1, 0, 0, 0> yxxx, vuuu;
        detail::SwizzleProperty<2, T, 1, 0, 0, 1> yxxy, vuuv;
        detail::SwizzleProperty<2, T, 1, 0, 1, 0> yxyx, vuvu;
        detail::SwizzleProperty<2, T, 1, 0, 1, 1> yxyy, vuvv;
        detail::SwizzleProperty<2, T, 1, 1, 0, 0> yyxx, vvuu;
        detail::SwizzleProperty<2, T, 1, 1, 0, 1> yyxy, vvuv;
        detail::SwizzleProperty<2, T, 1, 1, 1, 0> yyyx, vvvu;
        detail::SwizzleProperty<2, T, 1, 1, 1, 1> yyyy, vvvv;
    };
};


template <arithmetic T>
struct Vector<3, T> : detail::VectorBase<3, T> {
    using detail::VectorBase<3, T>::VectorBase;
    using detail::VectorBase<3, T>::operator=;


    union {
        T data[3];
        struct { T x, y, z; };
        struct { T u, v, w; };
        struct { T r, g, b; };
        detail::SwizzleProperty<3, T, 0, 0> xx, uu, rr;
        detail::SwizzleProperty<3, T, 0, 1> xy, uv, rg;
        detail::SwizzleProperty<3, T, 0, 2> xz, uw, rb;
        detail::SwizzleProperty<3, T, 1, 0> yx, vu, gr;
        detail::SwizzleProperty<3, T, 1, 1> yy, vv, gg;
        detail::SwizzleProperty<3, T, 1, 2> yz, vw, gb;
        detail::SwizzleProperty<3, T, 2, 0> zx, wu, br;
        detail::SwizzleProperty<3, T, 2, 1> zy, wv, bg;
        detail::SwizzleProperty<3, T, 2, 2> zz, ww, bb;
        detail::SwizzleProperty<3, T, 0, 0, 0> xxx, uuu, rrr;
        detail::SwizzleProperty<3, T, 0, 0, 1> xxy, uuv, rrg;
        detail::SwizzleProperty<3, T, 0, 0, 2> xxz, uuw, rrb;
        detail::SwizzleProperty<3, T, 0, 1, 0> xyx, uvu, rgr;
        detail::SwizzleProperty<3, T, 0, 1, 1> xyy, uvv, rgg;
        detail::SwizzleProperty<3, T, 0, 1, 2> xyz, uvw, rgb;
        detail::SwizzleProperty<3, T, 0, 2, 0> xzx, uwu, rbr;
        detail::SwizzleProperty<3, T, 0, 2, 1> xzy, uwv, rbg;
        detail::SwizzleProperty<3, T, 0, 2, 2> xzz, uww, rbb;
        detail::SwizzleProperty<3, T, 1, 0, 0> yxx, vuu, grr;
        detail::SwizzleProperty<3, T, 1, 0, 1> yxy, vuv, grg;
        detail::SwizzleProperty<3, T, 1, 0, 2> yxz, vuw, grb;
        detail::SwizzleProperty<3, T, 1, 1, 0> yyx, vvu, ggr;
        detail::SwizzleProperty<3, T, 1, 1, 1> yyy, vvv, ggg;
        detail::SwizzleProperty<3, T, 1, 1, 2> yyz, vvw, ggb;
        detail::SwizzleProperty<3, T, 1, 2, 0> yzx, vwu, gbr;
        detail::SwizzleProperty<3, T, 1, 2, 1> yzy, vwv, gbg;
        detail::SwizzleProperty<3, T, 1, 2, 2> yzz, vww, gbb;
        detail::SwizzleProperty<3, T, 2, 0, 0> zxx, wuu, brr;
        detail::SwizzleProperty<3, T, 2, 0, 1> zxy, wuv, brg;
        detail::SwizzleProperty<3, T, 2, 0, 2> zxz, wuw, brb;
        detail::SwizzleProperty<3, T, 2, 1, 0> zyx, wvu, bgr;
        detail::SwizzleProperty<3, T, 2, 1, 1> zyy, wvv, bgg;
        detail::SwizzleProperty<3, T, 2, 1, 2> zyz, wvw, bgb;
        detail::SwizzleProperty<3, T, 2, 2, 0> zzx, wwu, bbr;
        detail::SwizzleProperty<3, T, 2, 2, 1> zzy, wwv, bbg;
        detail::SwizzleProperty<3, T, 2, 2, 2> zzz, www, bbb;
        detail::SwizzleProperty<3, T, 0, 0, 0, 0> xxxx, uuuu, rrrr;
        detail::SwizzleProperty<3, T, 0, 0, 0, 1> xxxy, uuuv, rrrg;
        detail::SwizzleProperty<3, T, 0, 0, 0, 2> xxxz, uuuw, rrrb;
        detail::SwizzleProperty<3, T, 0, 0, 1, 0> xxyx, uuvu, rrgr;
        detail::SwizzleProperty<3, T, 0, 0, 1, 1> xxyy, uuvv, rrgg;
        detail::SwizzleProperty<3, T, 0, 0, 1, 2> xxyz, uuvw, rrgb;
        detail::SwizzleProperty<3, T, 0, 0, 2, 0> xxzx, uuwu, rrbr;
        detail::SwizzleProperty<3, T, 0, 0, 2, 1> xxzy, uuwv, rrbg;
        detail::SwizzleProperty<3, T, 0, 0, 2, 2> xxzz, uuww, rrbb;
        detail::SwizzleProperty<3, T, 0, 1, 0, 0> xyxx, uvuu, rgrr;
        detail::SwizzleProperty<3, T, 0, 1, 0, 1> xyxy, uvuv, rgrg;
        detail::SwizzleProperty<3, T, 0, 1, 0, 2> xyxz, uvuw, rgrb;
        detail::SwizzleProperty<3, T, 0, 1, 1, 0> xyyx, uvvu, rggr;
        detail::SwizzleProperty<3, T, 0, 1, 1, 1> xyyy, uvvv, rggg;
        detail::SwizzleProperty<3, T, 0, 1, 1, 2> xyyz, uvvw, rggb;
        detail::SwizzleProperty<3, T, 0, 1, 2, 0> xyzx, uvwu, rgbr;
        detail::SwizzleProperty<3, T, 0, 1, 2, 1> xyzy, uvwv, rgbg;
        detail::SwizzleProperty<3, T, 0, 1, 2, 2> xyzz, uvww, rgbb;
        detail::SwizzleProperty<3, T, 0, 2, 0, 0> xzxx, uwuu, rbrr;
        detail::SwizzleProperty<3, T, 0, 2, 0, 1> xzxy, uwuv, rbrg;
        detail::SwizzleProperty<3, T, 0, 2, 0, 2> xzxz, uwuw, rbrb;
        detail::SwizzleProperty<3, T, 0, 2, 1, 0> xzyx, uwvu, rbgr;
        detail::SwizzleProperty<3, T, 0, 2, 1, 1> xzyy, uwvv, rbgg;
        detail::SwizzleProperty<3, T, 0, 2, 1, 2> xzyz, uwvw, rbgb;
        detail::SwizzleProperty<3, T, 0, 2, 2, 0> xzzx, uwwu, rbbr;
        detail::SwizzleProperty<3, T, 0, 2, 2, 1> xzzy, uwwv, rbbg;
        detail::SwizzleProperty<3, T, 0, 2, 2, 2> xzzz, uwww, rbbb;
        detail::SwizzleProperty<3, T, 1, 0, 0, 0> yxxx, vuuu, grrr;
        detail::SwizzleProperty<3, T, 1, 0, 0, 1> yxxy, vuuv, grrg;
        detail::SwizzleProperty<3, T, 1, 0, 0, 2> yxxz, vuuw, grrb;
        detail::SwizzleProperty<3, T, 1, 0, 1, 0> yxyx, vuvu, grgr;
        detail::SwizzleProperty<3, T, 1, 0, 1, 1> yxyy, vuvv, grgg;
        detail::SwizzleProperty<3, T, 1, 0, 1, 2> yxyz, vuvw, grgb;
        detail::SwizzleProperty<3, T, 1, 0, 2, 0> yxzx, vuwu, grbr;
        detail::SwizzleProperty<3, T, 1, 0, 2, 1> yxzy, vuwv, grbg;
        detail::SwizzleProperty<3, T, 1, 0, 2, 2> yxzz, vuww, grbb;
        detail::SwizzleProperty<3, T, 1, 1, 0, 0> yyxx, vvuu, ggrr;
        detail::SwizzleProperty<3, T, 1, 1, 0, 1> yyxy, vvuv, ggrg;
        detail::SwizzleProperty<3, T, 1, 1, 0, 2> yyxz, vvuw, ggrb;
        detail::SwizzleProperty<3, T, 1, 1, 1, 0> yyyx, vvvu, gggr;
        detail::SwizzleProperty<3, T, 1, 1, 1, 1> yyyy, vvvv, gggg;
        detail::SwizzleProperty<3, T, 1, 1, 1, 2> yyyz, vvvw, gggb;
        detail::SwizzleProperty<3, T, 1, 1, 2, 0> yyzx, vvwu, ggbr;
        detail::SwizzleProperty<3, T, 1, 1, 2, 1> yyzy, vvwv, ggbg;
        detail::SwizzleProperty<3, T, 1, 1, 2, 2> yyzz, vvww, ggbb;
        detail::SwizzleProperty<3, T, 1, 2, 0, 0> yzxx, vwuu, gbrr;
        detail::SwizzleProperty<3, T, 1, 2, 0, 1> yzxy, vwuv, gbrg;
        detail::SwizzleProperty<3, T, 1, 2, 0, 2> yzxz, vwuw, gbrb;
        detail::SwizzleProperty<3, T, 1, 2, 1, 0> yzyx, vwvu, gbgr;
        detail::SwizzleProperty<3, T, 1, 2, 1, 1> yzyy, vwvv, gbgg;
        detail::SwizzleProperty<3, T, 1, 2, 1, 2> yzyz, vwvw, gbgb;
        detail::SwizzleProperty<3, T, 1, 2, 2, 0> yzzx, vwwu, gbbr;
        detail::SwizzleProperty<3, T, 1, 2, 2, 1> yzzy, vwwv, gbbg;
        detail::SwizzleProperty<3, T, 1, 2, 2, 2> yzzz, vwww, gbbb;
        detail::SwizzleProperty<3, T, 2, 0, 0, 0> zxxx, wuuu, brrr;
        detail::SwizzleProperty<3, T, 2, 0, 0, 1> zxxy, wuuv, brrg;
        detail::SwizzleProperty<3, T, 2, 0, 0, 2> zxxz, wuuw, brrb;
        detail::SwizzleProperty<3, T, 2, 0, 1, 0> zxyx, wuvu, brgr;
        detail::SwizzleProperty<3, T, 2, 0, 1, 1> zxyy, wuvv, brgg;
        detail::SwizzleProperty<3, T, 2, 0, 1, 2> zxyz, wuvw, brgb;
        detail::SwizzleProperty<3, T, 2, 0, 2, 0> zxzx, wuwu, brbr;
        detail::SwizzleProperty<3, T, 2, 0, 2, 1> zxzy, wuwv, brbg;
        detail::SwizzleProperty<3, T, 2, 0, 2, 2> zxzz, wuww, brbb;
        detail::SwizzleProperty<3, T, 2, 1, 0, 0> zyxx, wvuu, bgrr;
        detail::SwizzleProperty<3, T, 2, 1, 0, 1> zyxy, wvuv, bgrg;
        detail::SwizzleProperty<3, T, 2, 1, 0, 2> zyxz, wvuw, bgrb;
        detail::SwizzleProperty<3, T, 2, 1, 1, 0> zyyx, wvvu, bggr;
        detail::SwizzleProperty<3, T, 2, 1, 1, 1> zyyy, wvvv, bggg;
        detail::SwizzleProperty<3, T, 2, 1, 1, 2> zyyz, wvvw, bggb;
        detail::SwizzleProperty<3, T, 2, 1, 2, 0> zyzx, wvwu, bgbr;
        detail::SwizzleProperty<3, T, 2, 1, 2, 1> zyzy, wvwv, bgbg;
        detail::SwizzleProperty<3, T, 2, 1, 2, 2> zyzz, wvww, bgbb;
        detail::SwizzleProperty<3, T, 2, 2, 0, 0> zzxx, wwuu, bbrr;
        detail::SwizzleProperty<3, T, 2, 2, 0, 1> zzxy, wwuv, bbrg;
        detail::SwizzleProperty<3, T, 2, 2, 0, 2> zzxz, wwuw, bbrb;
        detail::SwizzleProperty<3, T, 2, 2, 1, 0> zzyx, wwvu, bbgr;
        detail::SwizzleProperty<3, T, 2, 2, 1, 1> zzyy, wwvv, bbgg;
        detail::SwizzleProperty<3, T, 2, 2, 1, 2> zzyz, wwvw, bbgb;
        detail::SwizzleProperty<3, T, 2, 2, 2, 0> zzzx, wwwu, bbbr;
        detail::SwizzleProperty<3, T, 2, 2, 2, 1> zzzy, wwwv, bbbg;
        detail::SwizzleProperty<3, T, 2, 2, 2, 2> zzzz, wwww, bbbb;
    };
};


template <arithmetic T>
struct Vector<4, T> : detail::VectorBase<4, T> {
    using detail::VectorBase<4, T>::VectorBase;
    using detail::VectorBase<4, T>::operator=;


    template <class Derived, std::size_t I0, std::size_t I1>
    constexpr Vector(arithmetic auto e0, arithmetic auto e1, const detail::Base<Derived, I0, I1>& v) noexcept : Vector(e0, e1, v[0], v[1]) {}

    template <class Derived, std::size_t I0, std::size_t I1>
    constexpr Vector(arithmetic auto e0, const detail::Base<Derived, I0, I1>& v, arithmetic auto e1) noexcept : Vector(e0, v[0], v[1], e1) {}

    template <class Derived, std::size_t I0, std::size_t I1>
    constexpr Vector(const detail::Base<Derived, I0, I1>& v, arithmetic auto e0, arithmetic auto e1) noexcept : Vector(v[0], v[1], e0, e1) {}


    union {
        T data[4];
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        detail::SwizzleProperty<4, T, 0, 0> xx, rr;
        detail::SwizzleProperty<4, T, 0, 1> xy, rg;
        detail::SwizzleProperty<4, T, 0, 2> xz, rb;
        detail::SwizzleProperty<4, T, 0, 3> xw, ra;
        detail::SwizzleProperty<4, T, 1, 0> yx, gr;
        detail::SwizzleProperty<4, T, 1, 1> yy, gg;
        detail::SwizzleProperty<4, T, 1, 2> yz, gb;
        detail::SwizzleProperty<4, T, 1, 3> yw, ga;
        detail::SwizzleProperty<4, T, 2, 0> zx, br;
        detail::SwizzleProperty<4, T, 2, 1> zy, bg;
        detail::SwizzleProperty<4, T, 2, 2> zz, bb;
        detail::SwizzleProperty<4, T, 2, 3> zw, ba;
        detail::SwizzleProperty<4, T, 3, 0> wx, ar;
        detail::SwizzleProperty<4, T, 3, 1> wy, ag;
        detail::SwizzleProperty<4, T, 3, 2> wz, ab;
        detail::SwizzleProperty<4, T, 3, 3> ww, aa;
        detail::SwizzleProperty<4, T, 0, 0, 0> xxx, rrr;
        detail::SwizzleProperty<4, T, 0, 0, 1> xxy, rrg;
        detail::SwizzleProperty<4, T, 0, 0, 2> xxz, rrb;
        detail::SwizzleProperty<4, T, 0, 0, 3> xxw, rra;
        detail::SwizzleProperty<4, T, 0, 1, 0> xyx, rgr;
        detail::SwizzleProperty<4, T, 0, 1, 1> xyy, rgg;
        detail::SwizzleProperty<4, T, 0, 1, 2> xyz, rgb;
        detail::SwizzleProperty<4, T, 0, 1, 3> xyw, rga;
        detail::SwizzleProperty<4, T, 0, 2, 0> xzx, rbr;
        detail::SwizzleProperty<4, T, 0, 2, 1> xzy, rbg;
        detail::SwizzleProperty<4, T, 0, 2, 2> xzz, rbb;
        detail::SwizzleProperty<4, T, 0, 2, 3> xzw, rba;
        detail::SwizzleProperty<4, T, 0, 3, 0> xwx, rar;
        detail::SwizzleProperty<4, T, 0, 3, 1> xwy, rag;
        detail::SwizzleProperty<4, T, 0, 3, 2> xwz, rab;
        detail::SwizzleProperty<4, T, 0, 3, 3> xww, raa;
        detail::SwizzleProperty<4, T, 1, 0, 0> yxx, grr;
        detail::SwizzleProperty<4, T, 1, 0, 1> yxy, grg;
        detail::SwizzleProperty<4, T, 1, 0, 2> yxz, grb;
        detail::SwizzleProperty<4, T, 1, 0, 3> yxw, gra;
        detail::SwizzleProperty<4, T, 1, 1, 0> yyx, ggr;
        detail::SwizzleProperty<4, T, 1, 1, 1> yyy, ggg;
        detail::SwizzleProperty<4, T, 1, 1, 2> yyz, ggb;
        detail::SwizzleProperty<4, T, 1, 1, 3> yyw, gga;
        detail::SwizzleProperty<4, T, 1, 2, 0> yzx, gbr;
        detail::SwizzleProperty<4, T, 1, 2, 1> yzy, gbg;
        detail::SwizzleProperty<4, T, 1, 2, 2> yzz, gbb;
        detail::SwizzleProperty<4, T, 1, 2, 3> yzw, gba;
        detail::SwizzleProperty<4, T, 1, 3, 0> ywx, gar;
        detail::SwizzleProperty<4, T, 1, 3, 1> ywy, gag;
        detail::SwizzleProperty<4, T, 1, 3, 2> ywz, gab;
        detail::SwizzleProperty<4, T, 1, 3, 3> yww, gaa;
        detail::SwizzleProperty<4, T, 2, 0, 0> zxx, brr;
        detail::SwizzleProperty<4, T, 2, 0, 1> zxy, brg;
        detail::SwizzleProperty<4, T, 2, 0, 2> zxz, brb;
        detail::SwizzleProperty<4, T, 2, 0, 3> zxw, bra;
        detail::SwizzleProperty<4, T, 2, 1, 0> zyx, bgr;
        detail::SwizzleProperty<4, T, 2, 1, 1> zyy, bgg;
        detail::SwizzleProperty<4, T, 2, 1, 2> zyz, bgb;
        detail::SwizzleProperty<4, T, 2, 1, 3> zyw, bga;
        detail::SwizzleProperty<4, T, 2, 2, 0> zzx, bbr;
        detail::SwizzleProperty<4, T, 2, 2, 1> zzy, bbg;
        detail::SwizzleProperty<4, T, 2, 2, 2> zzz, bbb;
        detail::SwizzleProperty<4, T, 2, 2, 3> zzw, bba;
        detail::SwizzleProperty<4, T, 2, 3, 0> zwx, bar;
        detail::SwizzleProperty<4, T, 2, 3, 1> zwy, bag;
        detail::SwizzleProperty<4, T, 2, 3, 2> zwz, bab;
        detail::SwizzleProperty<4, T, 2, 3, 3> zww, baa;
        detail::SwizzleProperty<4, T, 3, 0, 0> wxx, arr;
        detail::SwizzleProperty<4, T, 3, 0, 1> wxy, arg;
        detail::SwizzleProperty<4, T, 3, 0, 2> wxz, arb;
        detail::SwizzleProperty<4, T, 3, 0, 3> wxw, ara;
        detail::SwizzleProperty<4, T, 3, 1, 0> wyx, agr;
        detail::SwizzleProperty<4, T, 3, 1, 1> wyy, agg;
        detail::SwizzleProperty<4, T, 3, 1, 2> wyz, agb;
        detail::SwizzleProperty<4, T, 3, 1, 3> wyw, aga;
        detail::SwizzleProperty<4, T, 3, 2, 0> wzx, abr;
        detail::SwizzleProperty<4, T, 3, 2, 1> wzy, abg;
        detail::SwizzleProperty<4, T, 3, 2, 2> wzz, abb;
        detail::SwizzleProperty<4, T, 3, 2, 3> wzw, aba;
        detail::SwizzleProperty<4, T, 3, 3, 0> wwx, aar;
        detail::SwizzleProperty<4, T, 3, 3, 1> wwy, aag;
        detail::SwizzleProperty<4, T, 3, 3, 2> wwz, aab;
        detail::SwizzleProperty<4, T, 3, 3, 3> www, aaa;
        detail::SwizzleProperty<4, T, 0, 0, 0, 0> xxxx, rrrr;
        detail::SwizzleProperty<4, T, 0, 0, 0, 1> xxxy, rrrg;
        detail::SwizzleProperty<4, T, 0, 0, 0, 2> xxxz, rrrb;
        detail::SwizzleProperty<4, T, 0, 0, 0, 3> xxxw, rrra;
        detail::SwizzleProperty<4, T, 0, 0, 1, 0> xxyx, rrgr;
        detail::SwizzleProperty<4, T, 0, 0, 1, 1> xxyy, rrgg;
        detail::SwizzleProperty<4, T, 0, 0, 1, 2> xxyz, rrgb;
        detail::SwizzleProperty<4, T, 0, 0, 1, 3> xxyw, rrga;
        detail::SwizzleProperty<4, T, 0, 0, 2, 0> xxzx, rrbr;
        detail::SwizzleProperty<4, T, 0, 0, 2, 1> xxzy, rrbg;
        detail::SwizzleProperty<4, T, 0, 0, 2, 2> xxzz, rrbb;
        detail::SwizzleProperty<4, T, 0, 0, 2, 3> xxzw, rrba;
        detail::SwizzleProperty<4, T, 0, 0, 3, 0> xxwx, rrar;
        detail::SwizzleProperty<4, T, 0, 0, 3, 1> xxwy, rrag;
        detail::SwizzleProperty<4, T, 0, 0, 3, 2> xxwz, rrab;
        detail::SwizzleProperty<4, T, 0, 0, 3, 3> xxww, rraa;
        detail::SwizzleProperty<4, T, 0, 1, 0, 0> xyxx, rgrr;
        detail::SwizzleProperty<4, T, 0, 1, 0, 1> xyxy, rgrg;
        detail::SwizzleProperty<4, T, 0, 1, 0, 2> xyxz, rgrb;
        detail::SwizzleProperty<4, T, 0, 1, 0, 3> xyxw, rgra;
        detail::SwizzleProperty<4, T, 0, 1, 1, 0> xyyx, rggr;
        detail::SwizzleProperty<4, T, 0, 1, 1, 1> xyyy, rggg;
        detail::SwizzleProperty<4, T, 0, 1, 1, 2> xyyz, rggb;
        detail::SwizzleProperty<4, T, 0, 1, 1, 3> xyyw, rgga;
        detail::SwizzleProperty<4, T, 0, 1, 2, 0> xyzx, rgbr;
        detail::SwizzleProperty<4, T, 0, 1, 2, 1> xyzy, rgbg;
        detail::SwizzleProperty<4, T, 0, 1, 2, 2> xyzz, rgbb;
        detail::SwizzleProperty<4, T, 0, 1, 2, 3> xyzw, rgba;
        detail::SwizzleProperty<4, T, 0, 1, 3, 0> xywx, rgar;
        detail::SwizzleProperty<4, T, 0, 1, 3, 1> xywy, rgag;
        detail::SwizzleProperty<4, T, 0, 1, 3, 2> xywz, rgab;
        detail::SwizzleProperty<4, T, 0, 1, 3, 3> xyww, rgaa;
        detail::SwizzleProperty<4, T, 0, 2, 0, 0> xzxx, rbrr;
        detail::SwizzleProperty<4, T, 0, 2, 0, 1> xzxy, rbrg;
        detail::SwizzleProperty<4, T, 0, 2, 0, 2> xzxz, rbrb;
        detail::SwizzleProperty<4, T, 0, 2, 0, 3> xzxw, rbra;
        detail::SwizzleProperty<4, T, 0, 2, 1, 0> xzyx, rbgr;
        detail::SwizzleProperty<4, T, 0, 2, 1, 1> xzyy, rbgg;
        detail::SwizzleProperty<4, T, 0, 2, 1, 2> xzyz, rbgb;
        detail::SwizzleProperty<4, T, 0, 2, 1, 3> xzyw, rbga;
        detail::SwizzleProperty<4, T, 0, 2, 2, 0> xzzx, rbbr;
        detail::SwizzleProperty<4, T, 0, 2, 2, 1> xzzy, rbbg;
        detail::SwizzleProperty<4, T, 0, 2, 2, 2> xzzz, rbbb;
        detail::SwizzleProperty<4, T, 0, 2, 2, 3> xzzw, rbba;
        detail::SwizzleProperty<4, T, 0, 2, 3, 0> xzwx, rbar;
        detail::SwizzleProperty<4, T, 0, 2, 3, 1> xzwy, rbag;
        detail::SwizzleProperty<4, T, 0, 2, 3, 2> xzwz, rbab;
        detail::SwizzleProperty<4, T, 0, 2, 3, 3> xzww, rbaa;
        detail::SwizzleProperty<4, T, 0, 3, 0, 0> xwxx, rarr;
        detail::SwizzleProperty<4, T, 0, 3, 0, 1> xwxy, rarg;
        detail::SwizzleProperty<4, T, 0, 3, 0, 2> xwxz, rarb;
        detail::SwizzleProperty<4, T, 0, 3, 0, 3> xwxw, rara;
        detail::SwizzleProperty<4, T, 0, 3, 1, 0> xwyx, ragr;
        detail::SwizzleProperty<4, T, 0, 3, 1, 1> xwyy, ragg;
        detail::SwizzleProperty<4, T, 0, 3, 1, 2> xwyz, ragb;
        detail::SwizzleProperty<4, T, 0, 3, 1, 3> xwyw, raga;
        detail::SwizzleProperty<4, T, 0, 3, 2, 0> xwzx, rabr;
        detail::SwizzleProperty<4, T, 0, 3, 2, 1> xwzy, rabg;
        detail::SwizzleProperty<4, T, 0, 3, 2, 2> xwzz, rabb;
        detail::SwizzleProperty<4, T, 0, 3, 2, 3> xwzw, raba;
        detail::SwizzleProperty<4, T, 0, 3, 3, 0> xwwx, raar;
        detail::SwizzleProperty<4, T, 0, 3, 3, 1> xwwy, raag;
        detail::SwizzleProperty<4, T, 0, 3, 3, 2> xwwz, raab;
        detail::SwizzleProperty<4, T, 0, 3, 3, 3> xwww, raaa;
        detail::SwizzleProperty<4, T, 1, 0, 0, 0> yxxx, grrr;
        detail::SwizzleProperty<4, T, 1, 0, 0, 1> yxxy, grrg;
        detail::SwizzleProperty<4, T, 1, 0, 0, 2> yxxz, grrb;
        detail::SwizzleProperty<4, T, 1, 0, 0, 3> yxxw, grra;
        detail::SwizzleProperty<4, T, 1, 0, 1, 0> yxyx, grgr;
        detail::SwizzleProperty<4, T, 1, 0, 1, 1> yxyy, grgg;
        detail::SwizzleProperty<4, T, 1, 0, 1, 2> yxyz, grgb;
        detail::SwizzleProperty<4, T, 1, 0, 1, 3> yxyw, grga;
        detail::SwizzleProperty<4, T, 1, 0, 2, 0> yxzx, grbr;
        detail::SwizzleProperty<4, T, 1, 0, 2, 1> yxzy, grbg;
        detail::SwizzleProperty<4, T, 1, 0, 2, 2> yxzz, grbb;
        detail::SwizzleProperty<4, T, 1, 0, 2, 3> yxzw, grba;
        detail::SwizzleProperty<4, T, 1, 0, 3, 0> yxwx, grar;
        detail::SwizzleProperty<4, T, 1, 0, 3, 1> yxwy, grag;
        detail::SwizzleProperty<4, T, 1, 0, 3, 2> yxwz, grab;
        detail::SwizzleProperty<4, T, 1, 0, 3, 3> yxww, graa;
        detail::SwizzleProperty<4, T, 1, 1, 0, 0> yyxx, ggrr;
        detail::SwizzleProperty<4, T, 1, 1, 0, 1> yyxy, ggrg;
        detail::SwizzleProperty<4, T, 1, 1, 0, 2> yyxz, ggrb;
        detail::SwizzleProperty<4, T, 1, 1, 0, 3> yyxw, ggra;
        detail::SwizzleProperty<4, T, 1, 1, 1, 0> yyyx, gggr;
        detail::SwizzleProperty<4, T, 1, 1, 1, 1> yyyy, gggg;
        detail::SwizzleProperty<4, T, 1, 1, 1, 2> yyyz, gggb;
        detail::SwizzleProperty<4, T, 1, 1, 1, 3> yyyw, ggga;
        detail::SwizzleProperty<4, T, 1, 1, 2, 0> yyzx, ggbr;
        detail::SwizzleProperty<4, T, 1, 1, 2, 1> yyzy, ggbg;
        detail::SwizzleProperty<4, T, 1, 1, 2, 2> yyzz, ggbb;
        detail::SwizzleProperty<4, T, 1, 1, 2, 3> yyzw, ggba;
        detail::SwizzleProperty<4, T, 1, 1, 3, 0> yywx, ggar;
        detail::SwizzleProperty<4, T, 1, 1, 3, 1> yywy, ggag;
        detail::SwizzleProperty<4, T, 1, 1, 3, 2> yywz, ggab;
        detail::SwizzleProperty<4, T, 1, 1, 3, 3> yyww, ggaa;
        detail::SwizzleProperty<4, T, 1, 2, 0, 0> yzxx, gbrr;
        detail::SwizzleProperty<4, T, 1, 2, 0, 1> yzxy, gbrg;
        detail::SwizzleProperty<4, T, 1, 2, 0, 2> yzxz, gbrb;
        detail::SwizzleProperty<4, T, 1, 2, 0, 3> yzxw, gbra;
        detail::SwizzleProperty<4, T, 1, 2, 1, 0> yzyx, gbgr;
        detail::SwizzleProperty<4, T, 1, 2, 1, 1> yzyy, gbgg;
        detail::SwizzleProperty<4, T, 1, 2, 1, 2> yzyz, gbgb;
        detail::SwizzleProperty<4, T, 1, 2, 1, 3> yzyw, gbga;
        detail::SwizzleProperty<4, T, 1, 2, 2, 0> yzzx, gbbr;
        detail::SwizzleProperty<4, T, 1, 2, 2, 1> yzzy, gbbg;
        detail::SwizzleProperty<4, T, 1, 2, 2, 2> yzzz, gbbb;
        detail::SwizzleProperty<4, T, 1, 2, 2, 3> yzzw, gbba;
        detail::SwizzleProperty<4, T, 1, 2, 3, 0> yzwx, gbar;
        detail::SwizzleProperty<4, T, 1, 2, 3, 1> yzwy, gbag;
        detail::SwizzleProperty<4, T, 1, 2, 3, 2> yzwz, gbab;
        detail::SwizzleProperty<4, T, 1, 2, 3, 3> yzww, gbaa;
        detail::SwizzleProperty<4, T, 1, 3, 0, 0> ywxx, garr;
        detail::SwizzleProperty<4, T, 1, 3, 0, 1> ywxy, garg;
        detail::SwizzleProperty<4, T, 1, 3, 0, 2> ywxz, garb;
        detail::SwizzleProperty<4, T, 1, 3, 0, 3> ywxw, gara;
        detail::SwizzleProperty<4, T, 1, 3, 1, 0> ywyx, gagr;
        detail::SwizzleProperty<4, T, 1, 3, 1, 1> ywyy, gagg;
        detail::SwizzleProperty<4, T, 1, 3, 1, 2> ywyz, gagb;
        detail::SwizzleProperty<4, T, 1, 3, 1, 3> ywyw, gaga;
        detail::SwizzleProperty<4, T, 1, 3, 2, 0> ywzx, gabr;
        detail::SwizzleProperty<4, T, 1, 3, 2, 1> ywzy, gabg;
        detail::SwizzleProperty<4, T, 1, 3, 2, 2> ywzz, gabb;
        detail::SwizzleProperty<4, T, 1, 3, 2, 3> ywzw, gaba;
        detail::SwizzleProperty<4, T, 1, 3, 3, 0> ywwx, gaar;
        detail::SwizzleProperty<4, T, 1, 3, 3, 1> ywwy, gaag;
        detail::SwizzleProperty<4, T, 1, 3, 3, 2> ywwz, gaab;
        detail::SwizzleProperty<4, T, 1, 3, 3, 3> ywww, gaaa;
        detail::SwizzleProperty<4, T, 2, 0, 0, 0> zxxx, brrr;
        detail::SwizzleProperty<4, T, 2, 0, 0, 1> zxxy, brrg;
        detail::SwizzleProperty<4, T, 2, 0, 0, 2> zxxz, brrb;
        detail::SwizzleProperty<4, T, 2, 0, 0, 3> zxxw, brra;
        detail::SwizzleProperty<4, T, 2, 0, 1, 0> zxyx, brgr;
        detail::SwizzleProperty<4, T, 2, 0, 1, 1> zxyy, brgg;
        detail::SwizzleProperty<4, T, 2, 0, 1, 2> zxyz, brgb;
        detail::SwizzleProperty<4, T, 2, 0, 1, 3> zxyw, brga;
        detail::SwizzleProperty<4, T, 2, 0, 2, 0> zxzx, brbr;
        detail::SwizzleProperty<4, T, 2, 0, 2, 1> zxzy, brbg;
        detail::SwizzleProperty<4, T, 2, 0, 2, 2> zxzz, brbb;
        detail::SwizzleProperty<4, T, 2, 0, 2, 3> zxzw, brba;
        detail::SwizzleProperty<4, T, 2, 0, 3, 0> zxwx, brar;
        detail::SwizzleProperty<4, T, 2, 0, 3, 1> zxwy, brag;
        detail::SwizzleProperty<4, T, 2, 0, 3, 2> zxwz, brab;
        detail::SwizzleProperty<4, T, 2, 0, 3, 3> zxww, braa;
        detail::SwizzleProperty<4, T, 2, 1, 0, 0> zyxx, bgrr;
        detail::SwizzleProperty<4, T, 2, 1, 0, 1> zyxy, bgrg;
        detail::SwizzleProperty<4, T, 2, 1, 0, 2> zyxz, bgrb;
        detail::SwizzleProperty<4, T, 2, 1, 0, 3> zyxw, bgra;
        detail::SwizzleProperty<4, T, 2, 1, 1, 0> zyyx, bggr;
        detail::SwizzleProperty<4, T, 2, 1, 1, 1> zyyy, bggg;
        detail::SwizzleProperty<4, T, 2, 1, 1, 2> zyyz, bggb;
        detail::SwizzleProperty<4, T, 2, 1, 1, 3> zyyw, bgga;
        detail::SwizzleProperty<4, T, 2, 1, 2, 0> zyzx, bgbr;
        detail::SwizzleProperty<4, T, 2, 1, 2, 1> zyzy, bgbg;
        detail::SwizzleProperty<4, T, 2, 1, 2, 2> zyzz, bgbb;
        detail::SwizzleProperty<4, T, 2, 1, 2, 3> zyzw, bgba;
        detail::SwizzleProperty<4, T, 2, 1, 3, 0> zywx, bgar;
        detail::SwizzleProperty<4, T, 2, 1, 3, 1> zywy, bgag;
        detail::SwizzleProperty<4, T, 2, 1, 3, 2> zywz, bgab;
        detail::SwizzleProperty<4, T, 2, 1, 3, 3> zyww, bgaa;
        detail::SwizzleProperty<4, T, 2, 2, 0, 0> zzxx, bbrr;
        detail::SwizzleProperty<4, T, 2, 2, 0, 1> zzxy, bbrg;
        detail::SwizzleProperty<4, T, 2, 2, 0, 2> zzxz, bbrb;
        detail::SwizzleProperty<4, T, 2, 2, 0, 3> zzxw, bbra;
        detail::SwizzleProperty<4, T, 2, 2, 1, 0> zzyx, bbgr;
        detail::SwizzleProperty<4, T, 2, 2, 1, 1> zzyy, bbgg;
        detail::SwizzleProperty<4, T, 2, 2, 1, 2> zzyz, bbgb;
        detail::SwizzleProperty<4, T, 2, 2, 1, 3> zzyw, bbga;
        detail::SwizzleProperty<4, T, 2, 2, 2, 0> zzzx, bbbr;
        detail::SwizzleProperty<4, T, 2, 2, 2, 1> zzzy, bbbg;
        detail::SwizzleProperty<4, T, 2, 2, 2, 2> zzzz, bbbb;
        detail::SwizzleProperty<4, T, 2, 2, 2, 3> zzzw, bbba;
        detail::SwizzleProperty<4, T, 2, 2, 3, 0> zzwx, bbar;
        detail::SwizzleProperty<4, T, 2, 2, 3, 1> zzwy, bbag;
        detail::SwizzleProperty<4, T, 2, 2, 3, 2> zzwz, bbab;
        detail::SwizzleProperty<4, T, 2, 2, 3, 3> zzww, bbaa;
        detail::SwizzleProperty<4, T, 2, 3, 0, 0> zwxx, barr;
        detail::SwizzleProperty<4, T, 2, 3, 0, 1> zwxy, barg;
        detail::SwizzleProperty<4, T, 2, 3, 0, 2> zwxz, barb;
        detail::SwizzleProperty<4, T, 2, 3, 0, 3> zwxw, bara;
        detail::SwizzleProperty<4, T, 2, 3, 1, 0> zwyx, bagr;
        detail::SwizzleProperty<4, T, 2, 3, 1, 1> zwyy, bagg;
        detail::SwizzleProperty<4, T, 2, 3, 1, 2> zwyz, bagb;
        detail::SwizzleProperty<4, T, 2, 3, 1, 3> zwyw, baga;
        detail::SwizzleProperty<4, T, 2, 3, 2, 0> zwzx, babr;
        detail::SwizzleProperty<4, T, 2, 3, 2, 1> zwzy, babg;
        detail::SwizzleProperty<4, T, 2, 3, 2, 2> zwzz, babb;
        detail::SwizzleProperty<4, T, 2, 3, 2, 3> zwzw, baba;
        detail::SwizzleProperty<4, T, 2, 3, 3, 0> zwwx, baar;
        detail::SwizzleProperty<4, T, 2, 3, 3, 1> zwwy, baag;
        detail::SwizzleProperty<4, T, 2, 3, 3, 2> zwwz, baab;
        detail::SwizzleProperty<4, T, 2, 3, 3, 3> zwww, baaa;
        detail::SwizzleProperty<4, T, 3, 0, 0, 0> wxxx, arrr;
        detail::SwizzleProperty<4, T, 3, 0, 0, 1> wxxy, arrg;
        detail::SwizzleProperty<4, T, 3, 0, 0, 2> wxxz, arrb;
        detail::SwizzleProperty<4, T, 3, 0, 0, 3> wxxw, arra;
        detail::SwizzleProperty<4, T, 3, 0, 1, 0> wxyx, argr;
        detail::SwizzleProperty<4, T, 3, 0, 1, 1> wxyy, argg;
        detail::SwizzleProperty<4, T, 3, 0, 1, 2> wxyz, argb;
        detail::SwizzleProperty<4, T, 3, 0, 1, 3> wxyw, arga;
        detail::SwizzleProperty<4, T, 3, 0, 2, 0> wxzx, arbr;
        detail::SwizzleProperty<4, T, 3, 0, 2, 1> wxzy, arbg;
        detail::SwizzleProperty<4, T, 3, 0, 2, 2> wxzz, arbb;
        detail::SwizzleProperty<4, T, 3, 0, 2, 3> wxzw, arba;
        detail::SwizzleProperty<4, T, 3, 0, 3, 0> wxwx, arar;
        detail::SwizzleProperty<4, T, 3, 0, 3, 1> wxwy, arag;
        detail::SwizzleProperty<4, T, 3, 0, 3, 2> wxwz, arab;
        detail::SwizzleProperty<4, T, 3, 0, 3, 3> wxww, araa;
        detail::SwizzleProperty<4, T, 3, 1, 0, 0> wyxx, agrr;
        detail::SwizzleProperty<4, T, 3, 1, 0, 1> wyxy, agrg;
        detail::SwizzleProperty<4, T, 3, 1, 0, 2> wyxz, agrb;
        detail::SwizzleProperty<4, T, 3, 1, 0, 3> wyxw, agra;
        detail::SwizzleProperty<4, T, 3, 1, 1, 0> wyyx, aggr;
        detail::SwizzleProperty<4, T, 3, 1, 1, 1> wyyy, aggg;
        detail::SwizzleProperty<4, T, 3, 1, 1, 2> wyyz, aggb;
        detail::SwizzleProperty<4, T, 3, 1, 1, 3> wyyw, agga;
        detail::SwizzleProperty<4, T, 3, 1, 2, 0> wyzx, agbr;
        detail::SwizzleProperty<4, T, 3, 1, 2, 1> wyzy, agbg;
        detail::SwizzleProperty<4, T, 3, 1, 2, 2> wyzz, agbb;
        detail::SwizzleProperty<4, T, 3, 1, 2, 3> wyzw, agba;
        detail::SwizzleProperty<4, T, 3, 1, 3, 0> wywx, agar;
        detail::SwizzleProperty<4, T, 3, 1, 3, 1> wywy, agag;
        detail::SwizzleProperty<4, T, 3, 1, 3, 2> wywz, agab;
        detail::SwizzleProperty<4, T, 3, 1, 3, 3> wyww, agaa;
        detail::SwizzleProperty<4, T, 3, 2, 0, 0> wzxx, abrr;
        detail::SwizzleProperty<4, T, 3, 2, 0, 1> wzxy, abrg;
        detail::SwizzleProperty<4, T, 3, 2, 0, 2> wzxz, abrb;
        detail::SwizzleProperty<4, T, 3, 2, 0, 3> wzxw, abra;
        detail::SwizzleProperty<4, T, 3, 2, 1, 0> wzyx, abgr;
        detail::SwizzleProperty<4, T, 3, 2, 1, 1> wzyy, abgg;
        detail::SwizzleProperty<4, T, 3, 2, 1, 2> wzyz, abgb;
        detail::SwizzleProperty<4, T, 3, 2, 1, 3> wzyw, abga;
        detail::SwizzleProperty<4, T, 3, 2, 2, 0> wzzx, abbr;
        detail::SwizzleProperty<4, T, 3, 2, 2, 1> wzzy, abbg;
        detail::SwizzleProperty<4, T, 3, 2, 2, 2> wzzz, abbb;
        detail::SwizzleProperty<4, T, 3, 2, 2, 3> wzzw, abba;
        detail::SwizzleProperty<4, T, 3, 2, 3, 0> wzwx, abar;
        detail::SwizzleProperty<4, T, 3, 2, 3, 1> wzwy, abag;
        detail::SwizzleProperty<4, T, 3, 2, 3, 2> wzwz, abab;
        detail::SwizzleProperty<4, T, 3, 2, 3, 3> wzww, abaa;
        detail::SwizzleProperty<4, T, 3, 3, 0, 0> wwxx, aarr;
        detail::SwizzleProperty<4, T, 3, 3, 0, 1> wwxy, aarg;
        detail::SwizzleProperty<4, T, 3, 3, 0, 2> wwxz, aarb;
        detail::SwizzleProperty<4, T, 3, 3, 0, 3> wwxw, aara;
        detail::SwizzleProperty<4, T, 3, 3, 1, 0> wwyx, aagr;
        detail::SwizzleProperty<4, T, 3, 3, 1, 1> wwyy, aagg;
        detail::SwizzleProperty<4, T, 3, 3, 1, 2> wwyz, aagb;
        detail::SwizzleProperty<4, T, 3, 3, 1, 3> wwyw, aaga;
        detail::SwizzleProperty<4, T, 3, 3, 2, 0> wwzx, aabr;
        detail::SwizzleProperty<4, T, 3, 3, 2, 1> wwzy, aabg;
        detail::SwizzleProperty<4, T, 3, 3, 2, 2> wwzz, aabb;
        detail::SwizzleProperty<4, T, 3, 3, 2, 3> wwzw, aaba;
        detail::SwizzleProperty<4, T, 3, 3, 3, 0> wwwx, aaar;
        detail::SwizzleProperty<4, T, 3, 3, 3, 1> wwwy, aaag;
        detail::SwizzleProperty<4, T, 3, 3, 3, 2> wwwz, aaab;
        detail::SwizzleProperty<4, T, 3, 3, 3, 3> wwww, aaaa;
    };
};


//CTAD
template <typename... Ts>
Vector(Ts...) -> Vector<sizeof...(Ts), std::common_type_t<Ts...>>;

template <std::size_t N, typename T>
Vector(const T(&)[N]) -> Vector<N, T>;

template <std::size_t N, arithmetic T, std::size_t... I>
Vector(const detail::Swizzle<N, T, I...>&) -> Vector<sizeof...(I), T>;


template <arithmetic E, std::size_t N, arithmetic T, std::size_t... I>
    requires(sizeof...(I) <= 3)
Vector(E, const detail::Swizzle<N, T, I...>&)->Vector<1 + sizeof...(I), std::common_type_t<E, T>>;

template <arithmetic E, std::size_t N, arithmetic T>
    requires(N <= 3)
Vector(E, const Vector<N, T>&)->Vector<1 + N, std::common_type_t<E, T>>;


template <arithmetic E, std::size_t N, arithmetic T, std::size_t... I>
    requires(sizeof...(I) <= 3)
Vector(const detail::Swizzle<N, T, I...>&, E)->Vector<1 + sizeof...(I), std::common_type_t<E, T>>;

template <arithmetic E, std::size_t N, arithmetic T>
    requires(N <= 3)
Vector(const Vector<N, T>&, E)->Vector<1 + N, std::common_type_t<E, T>>;


template <arithmetic E0, arithmetic E1, std::size_t N, arithmetic T, std::size_t I0, std::size_t I1>
Vector(E0, E1, const detail::Swizzle<N, T, I0, I1>&) -> Vector<4, std::common_type_t<E0, E1, T>>;

template <arithmetic E0, arithmetic E1, arithmetic T>
Vector(E0, E1, const Vector<2, T>&) -> Vector<4, std::common_type_t<E0, E1, T>>;


template <arithmetic E0, arithmetic E1, std::size_t N, arithmetic T, std::size_t I0, std::size_t I1>
Vector(E0, const detail::Swizzle<N, T, I0, I1>&, E1) -> Vector<4, std::common_type_t<E0, E1, T>>;

template <arithmetic E0, arithmetic E1, arithmetic T>
Vector(E0, const Vector<2, T>&, E1) -> Vector<4, std::common_type_t<E0, E1, T>>;


template <arithmetic E0, arithmetic E1, std::size_t N, arithmetic T, std::size_t I0, std::size_t I1>
Vector(const detail::Swizzle<N, T, I0, I1>&, E0, E1) -> Vector<4, std::common_type_t<E0, E1, T>>;

template <arithmetic E0, arithmetic E1, arithmetic T>
Vector(const Vector<2, T>&, E0, E1) -> Vector<4, std::common_type_t<E0, E1, T>>;


template <arithmetic T>
using Vector2 = Vector<2, T>;
template <arithmetic T>
using Vector3 = Vector<3, T>;
template <arithmetic T>
using Vector4 = Vector<4, T>;


#ifdef _MSC_VER
#pragma warning(pop)
#endif
