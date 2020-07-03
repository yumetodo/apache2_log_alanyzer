/*=============================================================================
  Copyright (C) 2020 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <date/date.h>
#include <utility>
#include "../include/date_parser.hpp"
#include "../iutest/include/iutest.hpp"
IUTEST(DateParser, DateParser)
{
    using namespace date::literals;
    using namespace std::chrono_literals;
    constexpr std::pair<const char*, date::sys_seconds> input[] = {
        {
            "30/Jun/2020:11:30:43 +0900",
            date::sys_days(2020_y/6/30) + 11h + 30min + 43s - 9h
        },
        {
            "10/Oct/2000:13:55:36 -0700",
            date::sys_days(2000_y/10/10) + 13h + 55min + 36s +7h
        }
    };
    for (auto&& [i, expected] : input) {
        const auto re = date_parser(i);
        IUTEST_ASSERT_EQ(expected, re);
    }
}