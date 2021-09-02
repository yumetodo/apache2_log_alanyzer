/*=============================================================================
  Copyright (C) 2020 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <date/date.h>
#include "../include/cmd_argument_parser.hpp"
#include "../iutest/include/iutest.hpp"
IUTEST(CmdArgumentParser, countByHour)
{
    const char* argv[] = {
      "foo",
      "count_by_hour"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(count_mode::count_by_hour, actual.mode);
    IUTEST_ASSERT_EQ(order_mode::chronological, actual.order);
}
IUTEST(CmdArgumentParser, countByRemote)
{
    const char* argv[] = {
      "foo",
      "count_by_remote"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(count_mode::count_by_remote, actual.mode);
}
IUTEST(CmdArgumentParser, since)
{
    using namespace date::literals;
    using namespace std::chrono_literals;
    const char* argv[] = {
      "foo",
      "count_by_remote",
      "--since",
      "2020-6-30 12:40:00 +0900"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ((date::sys_days(2020_y/6/30) + 12h + 40min + 0s - 9h), actual.since);
}
IUTEST(CmdArgumentParser, until)
{
    using namespace date::literals;
    using namespace std::chrono_literals;
    const char* argv[] = {
      "foo",
      "count_by_remote",
      "--until",
      "2020-6-30 12:40:00 +0900"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ((date::sys_days(2020_y/6/30) + 12h + 40min + 0s - 9h), actual.until);
}
IUTEST(CmdArgumentParser, take)
{
    const char* argv[] = {
      "foo",
      "count_by_remote",
      "--take",
      "5"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(count_mode::count_by_remote, actual.mode);
    IUTEST_ASSERT_EQ(order_mode::descending, actual.order);
    IUTEST_ASSERT_EQ(5, actual.take);
}
IUTEST(CmdArgumentParser, orderAscending)
{
    const char* argv[] = {
      "foo",
      "count_by_remote",
      "--order",
      "ascending"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(order_mode::ascending, actual.order);
}
IUTEST(CmdArgumentParser, orderDescending)
{
    const char* argv[] = {
      "foo",
      "count_by_remote",
      "--order",
      "descending"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(order_mode::descending, actual.order);
}
IUTEST(CmdArgumentParser, orderChronological)
{
    const char* argv[] = {
      "foo",
      "count_by_hour",
      "--order",
      "chronological"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(count_mode::count_by_hour, actual.mode);
    IUTEST_ASSERT_EQ(order_mode::chronological, actual.order);
}
IUTEST(CmdArgumentParser, verbose)
{
    const char* argv[] = {
      "foo",
      "count_by_hour",
      "--verbose"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(true, actual.verbose);
}
IUTEST(CmdArgumentParser, filepath)
{
    const char* argv[] = {
      "foo",
      "count_by_hour",
      "/path/to/file1",
      "/path/to/file2"
    };
    const auto actual = cmd_argument_parser(int(std::size(argv)), argv);
    IUTEST_ASSERT_EQ(argv + 2, actual.files);
}
