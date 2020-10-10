// SLGP共通設定
#pragma once
#include "std_lib.h"

// 数値定義は高速化可能な下記を使用する
using u64 = std::uint_fast64_t;
using u32 = std::uint_fast32_t;
using u16 = std::uint_fast16_t;
using u8  = std::uint_fast8_t;

using i64 = std::int_fast64_t;
using i32 = std::int_fast32_t;
using i16 = std::int_fast16_t;
using i8  = std::int_fast8_t;

// 配列サイズ取得
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept
{ return N; }

#define UNUSED(x) ((void)x)

// レジスタ数
#define NREGISTERS (9)
// 定数 0 ~ NCONSTANTS
#define NCONSTANTS (9)