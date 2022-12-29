#pragma once


#include "definition.hpp"


namespace math {
    namespace detail {
        template <size_t Dimension, arithmetic T, size_t... Indices>
        struct Swizzle {
            template <arithmetic U>
            constexpr Swizzle& operator=(U rhs) noexcept {
                T t = static_cast<T>(rhs);
                for (size_t i = 0; i < Dimension; ++i) {
                    (*this)[i] = t;
                }
                return *this;
            }

            template <arithmetic U>
            constexpr Swizzle& operator=(const Vector<Dimension, U>& rhs) noexcept {
                T t[Dimension];
                for (size_t i = 0; i < Dimension; ++i) {
                    t[i] = static_cast<T>(rhs[i]);
                }
                for (size_t i = 0; i < Dimension; ++i) {
                    (*this)[i] = t[i];
                }
                return *this;
            }


#define OPERATION(...) \
            template <arithmetic U> \
            constexpr Swizzle& operator __VA_ARGS__##=(const Vector<Dimension, U>& rhs) noexcept { \
                T t[Dimension]; \
                for (size_t i = 0; i < Dimension; ++i) { \
                    t[i] = static_cast<T>(rhs[i]); \
                } \
                for (size_t i = 0; i < Dimension; ++i) { \
                    (*this)[i] __VA_ARGS__##= t[i]; \
                } \
                return *this; \
            }

            //OPERATION()
            //OPERATION(+)
            //    OPERATION(-)
            //    OPERATION(*)
            //    OPERATION(/ )
            //    OPERATION(%)

#undef OPERATION
                //template <arithmetic U>
                //constexpr Swizzle& operator=(const Vector<Dimension, U>& rhs) noexcept {
                //	_apply_op(rhs, _assign<U>{});
                //	return *this;
                //}

                //template <arithmetic U>
                //constexpr Swizzle& operator+=(const Vector<Dimension, U>& rhs) noexcept {
                //	_apply_op(rhs, _add<U>{});
                //	return *this;
                //}

                //template <arithmetic U>
                //constexpr Swizzle& operator-=(const Vector<Dimension, U>& rhs) noexcept {
                //	_apply_op(rhs, _sub<U>{});
                //	return *this;
                //}

                //template <arithmetic U>
                //constexpr Swizzle& operator*=(const Vector<Dimension, U>& rhs) noexcept {
                //	_apply_op(rhs, _mul<U>{});
                //	return *this;
                //}

                //template <arithmetic U>
                //constexpr Swizzle& operator/=(const Vector<Dimension, U>& rhs) noexcept {
                //	_apply_op(rhs, _div<U>{});
                //	return *this;
                //}

                //template <arithmetic U>
                //constexpr Swizzle& operator%=(const Vector<Dimension, U>& rhs) noexcept {
                //	_apply_op(rhs, _mod<U>{});
                //	return *this;
                //}


            //constexpr operator Vector<Dimension, T>() const noexcept {
            //    return Vector<Dimension, T>((*this)[Indices]...);
            //}


            //private:
            T data[Dimension];

            static inline constexpr size_t indices[]{Indices...};


            template <class Self>
            constexpr auto&& operator[](this Self&& self, size_t index) noexcept {
                return std::forward<Self>(self).data[indices[index]];
            }

            //template <arithmetic U>
            //struct _assign {
            //	static constexpr void operator()(T& e, const U& t) const noexcept { e = t; }
            //};
            //template <arithmetic U>
            //struct _add {
            //	static constexpr void operator()(T& l, const U& r) const noexcept { l += r; }
            //};
            //template <arithmetic U>
            //struct _sub {
            //	static constexpr void operator()(T& l, const U& r) const noexcept { l -= r; }
            //};
            //template <arithmetic U>
            //struct _mul {
            //	static constexpr void operator()(T& l, const U& r) const noexcept { l *= r; }
            //};
            //template <arithmetic U>
            //struct _div {
            //	static constexpr void operator()(T& l, const U& r) const noexcept { l /= r; }
            //};
            //template <arithmetic U>
            //struct _mod {
            //	static constexpr void operator()(T& l, const U& r) const noexcept { l %= r; }
            //};

            //template <arithmetic U, typename Op>
            //constexpr void _apply_op(const Vector<Dimension, U>& rhs, const Op& op) {
            //	T t[Dimension];
            //	for (size_t i = 0; i < Dimension; ++i) {
            //		t[i] = rhs[i];
            //	}
            //	for (size_t i = 0; i < Dimension; ++i) {
            //		op((*this)[i], t[i]);
            //	}
            //}
        };


        template <size_t I0, size_t I1, size_t I2 = -1, size_t I3 = -2>
        inline constexpr bool ContainsDuplicate() noexcept {
            return I0 == I1 || I0 == I2 || I0 == I3 || I1 == I2 || I1 == I3 || I2 == I3;
        }


        template <size_t Dimension, arithmetic T, size_t... Indices>
        using SwizzleContainer = std::conditional_t<ContainsDuplicate<Indices...>(), const Swizzle<Dimension, T, Indices...>, Swizzle<Dimension, T, Indices...>>;
    }
}