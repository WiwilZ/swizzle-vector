#pragma once


#include <cstddef>

#include <type_traits>



namespace math {
    template <typename T>
    concept arithmetic = std::is_arithmetic_v<T>;

    template <size_t Dimension, arithmetic T>
    struct Vector;


    template <class T, class... Ts>
    Vector(T, Ts...) -> Vector<1 + sizeof...(Ts), std::common_type_t<T, Ts...>>;
}