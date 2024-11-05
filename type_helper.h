#pragma once


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


    template <size_t I0, size_t... Is>
    constexpr bool is_duplicated_v = (... || (I0 == Is)) || is_duplicated_v<Is...>;

    template <size_t I0>
    constexpr bool is_duplicated_v<I0> = false;
}// namespace detail
