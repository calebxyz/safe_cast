#pragma once

#include <stdint.h>
#include <bit>
#include <concepts>

namespace bits{

template <typename T1, typename T2>
concept larger_size = sizeof(T1) > sizeof(T2);

template <typename T1, typename T2>
concept equal_size = sizeof(T1) == sizeof(T2);

template <typename T>
concept pointer = std::is_pointer_v<T>;
template <typename T>
concept not_pointer = not std::is_pointer_v<T>;

template <typename T>
concept integral_bool = std::same_as<T, bool>;

template <typename T>
concept integral_not_bool = std::integral<T> and (not std::same_as<T, bool>);

template <typename T>
concept arithmetic_not_bool = std::is_arithmetic_v<T> and (not std::same_as<T, bool>);



namespace details {

template <not_pointer To, pointer From>
To bit_cast_size(From from){
  //only byte types are allowed to be reinterpret casted (not a UB allowed behaviour)
  //note if you using that you will not enjoin constexpr because reinterpret_cast is always runtime
  static_assert(sizeof(std::remove_pointer_t<From>) == 1, "only byte type pointer is supported");
  return *reinterpret_cast<To*>(from);
}

template <not_pointer To, not_pointer From>
constexpr To bit_cast_size(From from) requires equal_size<To, From>
{
  return std::bit_cast<To>(from);
}

template <std::floating_point To, std::floating_point From>
constexpr To bit_cast_size(From from)
  requires larger_size<To, From>
{
  return std::bit_cast<To>(static_cast<uint64_t>(std::bit_cast<uint32_t>(from)));
}

template <std::floating_point To, std::floating_point From>
constexpr To bit_cast_size(From from)
  requires larger_size<From, To>
{
  return std::bit_cast<To>(static_cast<uint32_t>(std::bit_cast<uint64_t>(from)));
}

template <std::floating_point To, integral_not_bool From>
constexpr To bit_cast_size(From from)
  requires larger_size<To, From>
{
  if constexpr (std::same_as<To, double>) {
    return std::bit_cast<To>(static_cast<uint64_t>(from));
  } else {
    return std::bit_cast<To>(static_cast<uint32_t>(from));
  }
}

template <std::floating_point To, integral_not_bool From>
constexpr To bit_cast_size(From from)
  requires larger_size<From, To>
{
  //the only way integral type will be larger than a floating point is only if the integral type is 64 bits and
  //the float point is a 32 bits type
  return std::bit_cast<To>(static_cast<uint32_t>(from));
}

template <integral_not_bool To, std::floating_point From>
constexpr To bit_cast_size(From from)
  requires larger_size<From, To>
{
  if constexpr (std::same_as<From, float>){
    return std::bit_cast<To>(static_cast<std::make_unsigned_t<To>>(std::bit_cast<uint32_t>(from)));
  } else {
    return std::bit_cast<To>(static_cast<std::make_unsigned_t<To>>(std::bit_cast<uint64_t>(from)));
  }
}

template <integral_not_bool To, std::floating_point From>
constexpr To bit_cast_size(From from)
  requires larger_size<To, From>
{
  //if To is integral type and, it's larger than a float type that means that its 64bit integral and that means that
  //the floating point number is float (32bits)
  return std::bit_cast<To>(static_cast<uint64_t>(std::bit_cast<uint32_t>(from)));
}

template <integral_not_bool To, integral_not_bool From>
constexpr To bit_cast_size(From from) requires (not equal_size<To, From>)
{
  //if both are integral all we want is to get the bits we need extend zeroext them or just cut them
  //we will never want to sign extend because that will change the bits
  return std::bit_cast<To>(static_cast<std::make_unsigned_t<To>>(static_cast<std::make_unsigned_t<From>>(from)));
}

template <integral_bool To, arithmetic_not_bool From>
constexpr bool bit_cast_size(From from){
  constexpr uint8_t MASK{1};
  if constexpr (std::integral<From>) {
    return from & MASK;
  } else {
    if constexpr (std::same_as<From, double>) {
        return std::bit_cast<uint64_t>(from) & MASK;
    } else {
        return std::bit_cast<uint32_t>(from) & MASK;
    }
  }
}

template <arithmetic_not_bool To, integral_bool From>
constexpr To bit_cast_size(From from){
  if constexpr (std::integral<To>){
      return std::bit_cast<To>(static_cast<std::make_unsigned_t<To>>(from));
  } else {
    if constexpr (std::same_as<To, double >) {
        return std::bit_cast<double>(static_cast<uint64_t>(from));
    } else {
        return std::bit_cast<float>(static_cast<uint32_t>(from));
    }
  }
}


template <not_pointer To>
constexpr To bit_cast(auto from) {
  return bit_cast_size<std::decay_t<To>, std::decay_t<decltype(from)>>(from);
}

}

template <typename To>
constexpr To bit_cast(auto from){
  return details::bit_cast<To>(from);
}

}
