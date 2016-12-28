// Copyright (c) 2016 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_cast_to_layout_compatible_HPP
#define BOOST_PFR_DETAIL_cast_to_layout_compatible_HPP

#if __cplusplus < 201402L
#   error C++14 is required for this header.
#endif

#include <type_traits>
#include <utility>      // metaprogramming stuff

namespace boost { namespace pfr { namespace detail {

template <class T, class U>
constexpr void static_assert_layout_compatible() noexcept {
    static_assert(
        std::alignment_of<T>::value == std::alignment_of<U>::value,
        "Alignment check failed, probably your structure has user-defined alignment for the whole structure or for some of the fields."
    );
    static_assert(sizeof(T) == sizeof(U), "Size check failed, probably your structure has bitfields or user-defined alignment.");
}

/// @cond
#ifdef __GNUC__
#define MAY_ALIAS __attribute__((__may_alias__))
#else
#define MAY_ALIAS
#endif
/// @endcond

template <class To, class From>
MAY_ALIAS const To& cast_to_layout_compatible(const From& val) noexcept {
    MAY_ALIAS const To* const t = reinterpret_cast<const To*>( std::addressof(val) );
    static_assert_layout_compatible<To, From>();
    return *t;
}

template <class To, class From>
MAY_ALIAS const volatile To& cast_to_layout_compatible(const volatile From& val) noexcept {
    MAY_ALIAS const volatile To* const t = reinterpret_cast<const volatile To*>( std::addressof(val) );
    static_assert_layout_compatible<To, From>();
    return *t;
}


template <class To, class From>
MAY_ALIAS volatile To& cast_to_layout_compatible(volatile From& val) noexcept {
    MAY_ALIAS volatile To* const t = reinterpret_cast<volatile To*>( std::addressof(val) );
    static_assert_layout_compatible<To, From>();
    return *t;
}



template <class To, class From>
MAY_ALIAS To& cast_to_layout_compatible(From& val) noexcept {
    MAY_ALIAS To* const t = reinterpret_cast<To*>( std::addressof(val) );
    static_assert_layout_compatible<To, From>();
    return *t;
}
/*
template <class To, class From>
MAY_ALIAS std::enable_if_t<std::is_rvalue_reference<From&&>::value, To&&> cast_to_layout_compatible(From&& val) noexcept {
    MAY_ALIAS To* const t = reinterpret_cast<To*>( std::addressof(val) );
    static_assert_layout_compatible<To, From>();
    return std::move(*t);
}*/

#undef MAY_ALIAS


}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_cast_to_layout_compatible_HPP
