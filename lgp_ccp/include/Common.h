#ifndef COMMON_H
#define COMMON_H

#include "std_lib.h"

using u64 = std::uint_fast64_t;
using u32 = std::uint_fast32_t;
using u16 = std::uint_fast16_t;
using u8  = std::uint_fast8_t;

using i64 = std::int_fast64_t;
using i32 = std::int_fast32_t;
using i16 = std::int_fast16_t;
using i8  = std::int_fast8_t;

using std::size_t;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

template<typename T, size_t N>
constexpr size_t arraySize(T(&)[N]) noexcept
{ return N; }

#define UNUSED(x) ((void)x)

constexpr auto NREGISTERS = (3);
constexpr auto NCONSTANTS = (9);

typedef double reg_type;
using rand_type = std::uint_fast32_t;

#define better(y1, y2)	(y1<y2)

#define _CRT_SECURE_NO_WARNINGS

#endif	/* COMMON_H */