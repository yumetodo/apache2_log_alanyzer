/*=============================================================================
  Copyright (C) 2020 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "../include/count_by_hour.hpp"
#include "../iutest/include/iutest.hpp"
IUTEST(CountByHour, CountByHour)
{
    count_by_hour counter;
    options o;
    o.order = order_mode::chronological;
    raw_parsed_line l;
    l.time = "30/Jun/2020:11:30:43 +0900";
    counter.read(l, o);
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT("02:1\n" == ss.str());
}
constexpr const char* input[] = {
    "30/Jun/2020:11:30:43 +0900",
    "30/Jun/2020:12:41:46 +0900",
    "30/Jun/2020:12:41:46 +0900",
    "30/Jun/2020:12:47:45 +0900",
    "30/Jun/2020:12:55:13 +0900",
    "30/Jun/2020:13:33:59 +0900",
    "30/Jun/2020:13:52:39 +0900",
};
constexpr const char* chronological_expected = R"(02:1
03:4
04:2
)";
constexpr const char* ascending_expected = R"(02:1
04:2
03:4
)";
constexpr const char* ascending_take_2_expected = R"(02:1
04:2
)";
constexpr const char* descending_expected = R"(03:4
04:2
02:1
)";
constexpr const char* descending_take_2_expected = R"(03:4
04:2
)";
IUTEST(CountByHour, chronological)
{
    count_by_hour counter;
    options o;
    o.order = order_mode::chronological;
    for (auto&& i : input) {
        raw_parsed_line l;
        l.time = i;
        counter.read(l, o);
    }
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT_EQ(chronological_expected, ss.str());
}
IUTEST(CountByHour, ascending)
{
    count_by_hour counter;
    options o;
    o.order = order_mode::ascending;
    for (auto&& i : input) {
        raw_parsed_line l;
        l.time = i;
        counter.read(l, o);
    }
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT_EQ(ascending_expected, ss.str());
}
IUTEST(CountByHour, AscendingTake2)
{
    count_by_hour counter;
    options o;
    o.order = order_mode::ascending;
    o.take = 2;
    for (auto&& i : input) {
        raw_parsed_line l;
        l.time = i;
        counter.read(l, o);
    }
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT_EQ(ascending_take_2_expected, ss.str());
}
IUTEST(CountByHour, descending)
{
    count_by_hour counter;
    options o;
    o.order = order_mode::descending;
    for (auto&& i : input) {
        raw_parsed_line l;
        l.time = i;
        counter.read(l, o);
    }
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT_EQ(descending_expected, ss.str());
}
IUTEST(CountByHour, DescendingTake2)
{
    count_by_hour counter;
    options o;
    o.order = order_mode::descending;
    o.take = 2;
    for (auto&& i : input) {
        raw_parsed_line l;
        l.time = i;
        counter.read(l, o);
    }
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT_EQ(descending_take_2_expected, ss.str());
}