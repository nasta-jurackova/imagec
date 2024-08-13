#pragma once

#include <type_traits>
#include <variant>

namespace utils {
// idx of type in variant
template <typename T, typename variant_t>
struct idx_of_variant;

namespace details {
template <std::size_t I, typename T, typename first_t, typename... rest_t>
struct idx_of_variant_help : public idx_of_variant_help<I + 1, T, rest_t...> {};

template <std::size_t I, typename T, typename... rest_t>
struct idx_of_variant_help<I, T, T, rest_t...> : public std::integral_constant<std::size_t, I> {
    static_assert(!std::disjunction_v<std::is_same<T, rest_t>...>,
                  "Searched type appears in the tuple more than one time");
};
} // namespace details
template <typename T, typename... types_t>
struct idx_of_variant<T, std::variant<types_t...>> : public details::idx_of_variant_help<0, T, types_t...> {};

template <typename T, typename variant_t>
constexpr std::size_t idx_of_variant_v = idx_of_variant<T, variant_t>::value;
} // namespace utils