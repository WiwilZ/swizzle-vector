#pragma once


#include <type_traits>


namespace math {
    template <typename T>
    concept arithmetic = std::is_arithmetic_v<T>;

    template <size_t N, arithmetic T>
    struct Vector;

    namespace detail {
        template <class Derived, size_t N, arithmetic T, size_t... Is>
        struct Base {
            constexpr T operator[](size_t index) const noexcept {
                constexpr size_t indices[]{Is...};
                return static_cast<const Derived*>(this)->data[indices[index]];
            }

            constexpr T& operator[](size_t index) noexcept {
                constexpr size_t indices[]{Is...};
                return static_cast<Derived*>(this)->data[indices[index]];
            }


            constexpr auto operator+() const noexcept { return Vector((*this)[Is]...); }
            constexpr auto operator-() const noexcept { return Vector(-(*this)[Is]...); }
            constexpr auto operator~() const noexcept { return Vector(~(*this)[Is]...); }
            constexpr auto operator!() const noexcept { return Vector(!(*this)[Is]...); }


            constexpr Derived& operator++() noexcept {
                T t[]{((*this)[Is] + 1)...};
                for (size_t i = 0; i < N; ++i) {
                    (*this)[i] = t[i];
                }
                return *static_cast<Derived*>(this);
            }
            constexpr Derived& operator--() noexcept {
                T t[]{((*this)[Is] - 1)...};
                for (size_t i = 0; i < N; ++i) {
                    (*this)[i] = t[i];
                }
                return *static_cast<Derived*>(this);
            }
            constexpr auto operator++(int) noexcept {
                T t[]{((*this)[Is])...};
                for (size_t i = 0; i < N; ++i) {
                    (*this)[i] = t[i] + 1;
                }
                return Vector(t);
            }
            constexpr auto operator--(int) noexcept {
                T t[]{((*this)[Is])...};
                for (size_t i = 0; i < N; ++i) {
                    (*this)[i] = t[i] - 1;
                }
                return Vector(t);
            }


            constexpr Derived& operator=(auto&& rhs) noexcept {
                apply_iop(rhs, [](T& e, T t) { e = t; });
                return *static_cast<Derived*>(this);
            }

            constexpr void operator+=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e += t; }); }
            constexpr void operator-=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e -= t; }); }
            constexpr void operator*=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e *= t; }); }
            constexpr void operator/=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e /= t; }); }
            constexpr void operator%=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e %= t; }); }
            constexpr void operator&=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e &= t; }); }
            constexpr void operator|=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e |= t; }); }
            constexpr void operator^=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e ^= t; }); }
            constexpr void operator<<=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e <<= t; }); }
            constexpr void operator>>=(auto&& rhs) noexcept { apply_iop(rhs, [](T& e, T t) { e >>= t; }); }


            constexpr auto operator+(auto&& rhs) const noexcept { return apply_op(rhs, add{}); }
            constexpr auto operator-(auto&& rhs) const noexcept { return apply_op(rhs, sub{}); }
            constexpr auto operator*(auto&& rhs) const noexcept { return apply_op(rhs, mul{}); }
            constexpr auto operator/(auto&& rhs) const noexcept { return apply_op(rhs, div{}); }
            constexpr auto operator%(auto&& rhs) const noexcept { return apply_op(rhs, mod{}); }
            constexpr auto operator&(auto&& rhs) const noexcept { return apply_op(rhs, bit_and{}); }
            constexpr auto operator|(auto&& rhs) const noexcept { return apply_op(rhs, bit_or{}); }
            constexpr auto operator^(auto&& rhs) const noexcept { return apply_op(rhs, bit_xor{}); }
            constexpr auto operator<<(auto&& rhs) const noexcept { return apply_op(rhs, lshift{}); }
            constexpr auto operator>>(auto&& rhs) const noexcept { return apply_op(rhs, rshift{}); }
            constexpr auto operator&&(auto&& rhs) const noexcept { return apply_op(rhs, logical_and{}); }
            constexpr auto operator||(auto&& rhs) const noexcept { return apply_op(rhs, logical_or{}); }


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


            template <class Derived1, size_t... Is1>
                requires(sizeof...(Is1) == N)
            constexpr bool operator==(const Base<Derived1, N, T, Is1...>& rhs) const noexcept {
                for (size_t i = 0; i < N; ++i) {
                    if ((*this)[i] != rhs[i]) {
                        return false;
                    }
                }
                return true;
            }
            template <class Derived1, size_t... Is1>
                requires(sizeof...(Is1) == N)
            constexpr bool operator!=(const Base<Derived1, N, T, Is1...>& rhs) const noexcept {
                return !(*this == rhs);
            }

        private:
            struct add { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l + r; } };
            struct sub { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l - r; } };
            struct mul { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l * r; } };
            struct div { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l / r; } };
            struct mod { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l % r; } };
            struct bit_and { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l & r; } };
            struct bit_or { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l | r; } };
            struct bit_xor { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l ^ r; } };
            struct lshift { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l << r; } };
            struct rshift { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l >> r; } };
            struct logical_and { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l && r; } };
            struct logical_or { constexpr auto operator()(T l, arithmetic auto r) const noexcept { return l || r; } };


            template <class Op, arithmetic U>
            constexpr void apply_iop(U rhs, const Op& op) noexcept {
                T t = static_cast<T>(rhs);
                for (size_t i = 0; i < N; ++i) {
                    op((*this)[i], t);
                }
            }
            template <class Op, class Derived1, arithmetic U, size_t... Is1>
                requires(sizeof...(Is1) == N)
            constexpr void apply_iop(const Base<Derived1, N, U, Is1...>& rhs, const Op& op) noexcept {
                T t[]{static_cast<T>(rhs[Is1])...};
                for (size_t i = 0; i < N; ++i) {
                    op((*this)[i], t[i]);
                }
            }


            template <class Op, arithmetic U>
            constexpr auto apply_op(U rhs, const Op& op) const noexcept {
                decltype(op(std::declval<T>(), std::declval<U>())) t[N];
                for (size_t i = 0; i < N; ++i) {
                    t[i] = op((*this)[i], rhs);
                }
                return Vector(t);
            }
            template <class Op, class Derived1, arithmetic U, size_t... Is1>
                requires(sizeof...(Is1) == N)
            constexpr auto apply_op(const Base<Derived1, N, U, Is1...>& rhs, const Op& op) const noexcept {
                decltype(op(std::declval<T>(), std::declval<U>())) t[N];
                for (size_t i = 0; i < N; ++i) {
                    t[i] = op((*this)[i], rhs[i]);
                }
                return Vector(t);
            }
            template <class Op, arithmetic U>
            static constexpr auto apply_op(U lhs, const Base& rhs, const Op& op) noexcept {
                decltype(op(std::declval<U>(), std::declval<T>())) t[N];
                for (size_t i = 0; i < N; ++i) {
                    t[i] = op(lhs, rhs[i]);
                }
                return Vector(t);
            }
        };



        template <size_t N, arithmetic T, size_t... Is>
        struct Swizzle : Base<Swizzle<N, T, Is...>, N, T, Is...> {
            using Base<Swizzle<N, T, Is...>, N, T, Is...>::operator=;
            T data[N];
        };



        template <size_t I0, size_t I1, size_t I2 = static_cast<size_t>(-1), size_t I3 = static_cast<size_t>(-2)>
        constexpr bool ContainsDuplicate = I0 == I1 || I0 == I2 || I0 == I3 || I1 == I2 || I1 == I3 || I2 == I3;

        template <size_t N, arithmetic T, size_t... Is>
        using SwizzleProperty = std::conditional_t<ContainsDuplicate<Is...>, const Swizzle<N, T, Is...>, Swizzle<N, T, Is...>>;
    }  // namespace detail



    template <arithmetic T>
    struct Vector<2, T> : detail::Base<Vector<2, T>, 2, T, 0, 1> {
        using detail::Base<Vector<2, T>, 2, T, 0, 1>::operator=;


        constexpr Vector(arithmetic auto e0, arithmetic auto e1) noexcept : data{static_cast<T>(e0), static_cast<T>(e1)} {}

        constexpr Vector() noexcept : Vector(0, 0) {}

        constexpr explicit Vector(arithmetic auto e) noexcept : Vector(e, e) {}

        template <arithmetic U>
        constexpr explicit Vector(const U(&v)[2]) noexcept : Vector(v[0], v[1]) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1>
        constexpr explicit Vector(const detail::Base<Derived, 2, U, I0, I1>& v) noexcept : Vector(v[0], v[1]) {}


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
    struct Vector<3, T> : detail::Base<Vector<3, T>, 3, T, 0, 1, 2> {
        using detail::Base<Vector<3, T>, 3, T, 0, 1, 2>::operator=;


        constexpr Vector(arithmetic auto e0, arithmetic auto e1, arithmetic auto e2) noexcept : data{static_cast<T>(e0), static_cast<T>(e1), static_cast<T>(e2)} {}

        constexpr Vector() noexcept : Vector(0, 0, 0) {}

        constexpr explicit Vector(arithmetic auto e) noexcept : Vector(e, e, e) {}

        template <arithmetic U>
        constexpr explicit Vector(const U(&v)[3]) noexcept : Vector(v[0], v[1], v[2]) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1>
        constexpr Vector(arithmetic auto e, const detail::Base<Derived, 2, U, I0, I1>& v) noexcept : Vector(e, v[0], v[1]) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1>
        constexpr Vector(const detail::Base<Derived, 2, U, I0, I1>& v, arithmetic auto e) noexcept : Vector(v[0], v[1], e) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1, size_t I2>
        constexpr explicit Vector(const detail::Base<Derived, 3, U, I0, I1, I2>& v) noexcept : Vector(v[0], v[1], v[2]) {}


        union {
            T data[3];
            struct { T x, y, z; };
            struct { T r, g, b; };
            struct { T u, v, w; };
            detail::SwizzleProperty<3, T, 0, 0, 0> xxx, rrr, uuu;
            detail::SwizzleProperty<3, T, 0, 0, 1> xxy, rrg, uuv;
            detail::SwizzleProperty<3, T, 0, 0, 2> xxz, rrb, uuw;
            detail::SwizzleProperty<3, T, 0, 1, 1> xyy, rgg, uvv;
            detail::SwizzleProperty<3, T, 0, 1, 2> xyz, rgb, uvw;
            detail::SwizzleProperty<3, T, 0, 2, 2> xzz, rbb, uww;
            detail::SwizzleProperty<3, T, 1, 1, 1> yyy, ggg, vvv;
            detail::SwizzleProperty<3, T, 1, 1, 2> yyz, ggb, vvw;
            detail::SwizzleProperty<3, T, 1, 2, 2> yzz, gbb, vww;
            detail::SwizzleProperty<3, T, 2, 2, 2> zzz, bbb, www;
            detail::SwizzleProperty<4, T, 0, 0, 0, 0> xxxx, rrrr, uuuu;
            detail::SwizzleProperty<4, T, 0, 0, 0, 1> xxxy, rrrg, uuuv;
            detail::SwizzleProperty<4, T, 0, 0, 0, 2> xxxz, rrrb, uuuw;
            detail::SwizzleProperty<4, T, 0, 0, 1, 1> xxyy, rrgg, uuvv;
            detail::SwizzleProperty<4, T, 0, 0, 1, 2> xxyz, rrgb, uuvw;
            detail::SwizzleProperty<4, T, 0, 0, 2, 2> xxzz, rrbb, uuww;
            detail::SwizzleProperty<4, T, 0, 1, 1, 1> xyyy, rggg, uvvv;
            detail::SwizzleProperty<4, T, 0, 1, 1, 2> xyyz, rggb, uvvw;
            detail::SwizzleProperty<4, T, 0, 1, 2, 2> xyzz, rgbb, uvww;
            detail::SwizzleProperty<4, T, 0, 2, 2, 2> xzzz, rbbb, uwww;
            detail::SwizzleProperty<4, T, 1, 1, 1, 1> yyyy, gggg, vvvv;
            detail::SwizzleProperty<4, T, 1, 1, 1, 2> yyyz, gggb, vvvw;
            detail::SwizzleProperty<4, T, 1, 1, 2, 2> yyzz, ggbb, vvww;
            detail::SwizzleProperty<4, T, 1, 2, 2, 2> yzzz, gbbb, vwww;
            detail::SwizzleProperty<4, T, 2, 2, 2, 2> zzzz, bbbb, wwww;
        };
    };


    template <arithmetic T>
    struct Vector<4, T> : detail::Base<Vector<4, T>, 4, T, 0, 1, 2, 3> {
        using detail::Base<Vector<4, T>, 4, T, 0, 1, 2, 3>::operator=;


        constexpr Vector(arithmetic auto e0, arithmetic auto e1, arithmetic auto e2, arithmetic auto e3) noexcept : data{static_cast<T>(e0), static_cast<T>(e1), static_cast<T>(e2), static_cast<T>(e3)} {}

        constexpr Vector() noexcept : Vector(0, 0, 0, 0) {}

        constexpr explicit Vector(arithmetic auto e) noexcept : Vector(e, e, e, e) {}

        template <arithmetic U>
        constexpr explicit Vector(const U(&v)[4]) noexcept : Vector(v[0], v[1], v[2], v[3]) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1, size_t I2>
        constexpr Vector(arithmetic auto e, const detail::Base<Derived, 3, U, I0, I1, I2>& v) noexcept : Vector(e, v[0], v[1], v[2]) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1, size_t I2>
        constexpr Vector(const detail::Base<Derived, 3, U, I0, I1, I2>& v, arithmetic auto e) noexcept : Vector(v[0], v[1], v[2], e) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1>
        constexpr Vector(arithmetic auto e0, arithmetic auto e1, const detail::Base<Derived, 2, U, I0, I1>& v) noexcept : Vector(e0, e1, v[0], v[1]) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1>
        constexpr Vector(arithmetic auto e0, const detail::Base<Derived, 2, U, I0, I1>& v, arithmetic auto e1) noexcept : Vector(e0, v[0], v[1], e1) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1>
        constexpr Vector(const detail::Base<Derived, 2, U, I0, I1>& v, arithmetic auto e0, arithmetic auto e1) noexcept : Vector(v[0], v[1], e0, e1) {}

        template <class Derived0, arithmetic U0, size_t I00, size_t I01,
            class Derived1, arithmetic U1, size_t I10, size_t I11>
        constexpr Vector(const detail::Base<Derived0, 2, U0, I00, I01>& v0, const detail::Base<Derived1, 2, U1, I10, I11>& v1) noexcept : Vector(v0[0], v0[1], v1[0], v1[1]) {}

        template <class Derived, arithmetic U, size_t I0, size_t I1, size_t I2, size_t I3>
        constexpr explicit Vector(const detail::Base<Derived, 4, U, I0, I1, I2, I3>& v) noexcept : Vector(v[0], v[1], v[2], v[3]) {}


        union {
            T data[4];
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            detail::SwizzleProperty<4, T, 0, 0, 0, 0> xxxx, rrrr;
            detail::SwizzleProperty<4, T, 0, 0, 0, 1> xxxy, rrrg;
            detail::SwizzleProperty<4, T, 0, 0, 0, 2> xxxz, rrrb;
            detail::SwizzleProperty<4, T, 0, 0, 0, 3> xxxw, rrra;
            detail::SwizzleProperty<4, T, 0, 0, 1, 1> xxyy, rrgg;
            detail::SwizzleProperty<4, T, 0, 0, 1, 2> xxyz, rrgb;
            detail::SwizzleProperty<4, T, 0, 0, 1, 3> xxyw, rrga;
            detail::SwizzleProperty<4, T, 0, 0, 2, 2> xxzz, rrbb;
            detail::SwizzleProperty<4, T, 0, 0, 2, 3> xxzw, rrba;
            detail::SwizzleProperty<4, T, 0, 0, 3, 3> xxww, rraa;
            detail::SwizzleProperty<4, T, 0, 1, 1, 1> xyyy, rggg;
            detail::SwizzleProperty<4, T, 0, 1, 1, 2> xyyz, rggb;
            detail::SwizzleProperty<4, T, 0, 1, 1, 3> xyyw, rgga;
            detail::SwizzleProperty<4, T, 0, 1, 2, 2> xyzz, rgbb;
            detail::SwizzleProperty<4, T, 0, 1, 2, 3> xyzw, rgba;
            detail::SwizzleProperty<4, T, 0, 1, 3, 3> xyww, rgaa;
            detail::SwizzleProperty<4, T, 0, 2, 2, 2> xzzz, rbbb;
            detail::SwizzleProperty<4, T, 0, 2, 2, 3> xzzw, rbba;
            detail::SwizzleProperty<4, T, 0, 2, 3, 3> xzww, rbaa;
            detail::SwizzleProperty<4, T, 0, 3, 3, 3> xwww, raaa;
            detail::SwizzleProperty<4, T, 1, 1, 1, 1> yyyy, gggg;
            detail::SwizzleProperty<4, T, 1, 1, 1, 2> yyyz, gggb;
            detail::SwizzleProperty<4, T, 1, 1, 1, 3> yyyw, ggga;
            detail::SwizzleProperty<4, T, 1, 1, 2, 2> yyzz, ggbb;
            detail::SwizzleProperty<4, T, 1, 1, 2, 3> yyzw, ggba;
            detail::SwizzleProperty<4, T, 1, 1, 3, 3> yyww, ggaa;
            detail::SwizzleProperty<4, T, 1, 2, 2, 2> yzzz, gbbb;
            detail::SwizzleProperty<4, T, 1, 2, 2, 3> yzzw, gbba;
            detail::SwizzleProperty<4, T, 1, 2, 3, 3> yzww, gbaa;
            detail::SwizzleProperty<4, T, 1, 3, 3, 3> ywww, gaaa;
            detail::SwizzleProperty<4, T, 2, 2, 2, 2> zzzz, bbbb;
            detail::SwizzleProperty<4, T, 2, 2, 2, 3> zzzw, bbba;
            detail::SwizzleProperty<4, T, 2, 2, 3, 3> zzww, bbaa;
            detail::SwizzleProperty<4, T, 2, 3, 3, 3> zwww, baaa;
            detail::SwizzleProperty<4, T, 3, 3, 3, 3> wwww, aaaa;
        };
    };



    template <typename... Ts>
    Vector(Ts...) -> Vector<sizeof...(Ts), std::common_type_t<Ts...>>;
    template <size_t N, typename T>
    Vector(const T(&)[N]) -> Vector<N, T>;



    template <arithmetic T>
    using Vector2 = Vector<2, T>;
    template <arithmetic T>
    using Vector3 = Vector<3, T>;
    template <arithmetic T>
    using Vector4 = Vector<4, T>;
}  // namespace math
