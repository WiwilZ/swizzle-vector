#pragma once


#include <cstddef>
#include <cstdint>
#include <concepts>


namespace detail {
    template <typename T, typename... Ts>
    constexpr bool is_any_of_v = (std::is_same_v<T, Ts> || ...);

    template <typename T>
    concept signed_integral = is_any_of_v<std::remove_cv_t<T>, int8_t, int16_t, int32_t, int64_t>;

    template <typename T>
    concept unsigned_integral = is_any_of_v<std::remove_cv_t<T>, bool, uint8_t, uint16_t, uint32_t, uint64_t>;

    template <typename T>
    concept integral = signed_integral<T> || unsigned_integral<T>;

    template <typename T>
    concept floating = is_any_of_v<std::remove_cv_t<T>, float, double>;

    template <typename T>
    concept numeric = integral<T> || floating<T>;

    template <numeric T>
    using to_floating = std::conditional_t<floating<T>, std::remove_cv_t<T>, float>;

    template <numeric L, numeric R>
    constexpr auto common_type_impl() noexcept {
        if constexpr (std::is_same_v<L, R>) {
            return L{};
        } else {
            if constexpr (floating<L> || floating<R>) {
                return std::common_type_t<L, R>{};
            } else {
                using LL = std::conditional_t<std::is_same_v<L, bool>, uint8_t, L>;
                using RR = std::conditional_t<std::is_same_v<R, bool>, uint8_t, R>;
                if constexpr (std::is_signed_v<LL> == std::is_signed_v<RR>) {
                    return std::conditional_t<(sizeof(LL) > sizeof(R)), LL, RR>{};
                } else {
                    using S = std::conditional_t<std::is_signed_v<LL>, LL, RR>;
                    using U = std::conditional_t<std::is_signed_v<LL>, RR, LL>;
                    return std::conditional_t<(sizeof(U) >= sizeof(S)), U, S>{};
                }
            }
        }
    }

    template <numeric L, numeric R>
    using common_type_t = decltype(common_type_impl<std::remove_cv_t<L>, std::remove_cv_t<R>>());


    template <size_t I0, size_t I1, size_t I2 = static_cast<size_t>(-1), size_t I3 = static_cast<size_t>(-2)>
    constexpr bool is_duplicated_v = I0 == I1 || I0 == I2 || I0 == I3 || I1 == I2 || I1 == I3 || I2 == I3;


    template <size_t Start, size_t End, size_t... Indices>
    struct make_index_sequence_impl : make_index_sequence_impl<Start, End - 1, End - 1, Indices...> {};

    template <size_t Start, size_t... Indices>
    struct make_index_sequence_impl<Start, Start, Indices...> {
        using type = std::index_sequence<Indices...>;
    };

    template <size_t Start, size_t End>
    using make_index_sequence = typename make_index_sequence_impl<Start, End>::type;


    template <typename T>
    struct extract_element_type {
        using type = typename T::element_type;
    };
    template <numeric T>
    struct extract_element_type<T> {
        using type = std::remove_cv_t<T>;
    };

    template <typename Op, typename... T>
    struct operator_result {
        using type = decltype(Op{}(std::declval<typename extract_element_type<T>::type>()...));
    };
} // namespace detail