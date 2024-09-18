#pragma once

#include <type_traits>
#include <variant>

namespace utils::traits {
/* ======= idx of type in variant ======= */
template <typename T, typename variant_t>
struct idx_of_variant;

namespace details {
template <std::size_t I, typename T, typename first_t, typename... rest_t>
struct idx_of_variant_help : public idx_of_variant_help<I + 1, T, rest_t...> {};

template <std::size_t I, typename T, typename... rest_t>
struct idx_of_variant_help<I, T, T, rest_t...> : public std::integral_constant<std::size_t, I> {};
} // namespace details
template <typename T, typename... types_t>
struct idx_of_variant<T, std::variant<types_t...>> : public details::idx_of_variant_help<0, T, types_t...> {};

template <typename T, typename variant_t>
constexpr std::size_t idx_of_variant_v = idx_of_variant<T, variant_t>::value;

/* ======= is any of variant ======= */
template <typename T, typename variant_t>
struct any_of_variant;

template <typename T, typename... types_t>
struct any_of_variant<T, std::variant<types_t...>> : public std::disjunction<std::is_same<T, types_t>...> {};

template <typename T, typename variant_t>
constexpr std::size_t any_of_variant_v = any_of_variant<T, variant_t>::value;
} // namespace utils