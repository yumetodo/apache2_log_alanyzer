#ifndef APACHE2_LOG_ANALYZER_DATE_PARSER_HPP_
#define APACHE2_LOG_ANALYZER_DATE_PARSER_HPP_
#include <optional>
#include <date/date.h>
#include <iostream>
#include <sstream>

enum class count_mode {
    count_by_hour,
    count_by_remote,
};
enum class order_mode {
    descending,
    ascending,
};
struct options {
    count_mode mode;
    order_mode order = order_mode::descending;
    date::sys_seconds since;
    date::sys_seconds until;
    const char* const* files = nullptr;
    unsigned long long take = 0;
    bool verbose = false;
};
namespace detail {
inline constexpr const char* help_text = R"(NAME
    apache2_log_analyzer - tiny apache2 log analyzer

SYNOPSIS
    apache2_log_analyzer <operation> [options] [file]...

DESCRIPTION
    Apache2_log_analyzer is a tiny utility tool to anlyze apache2 log file(s).

    With no FILE, or when FILE is -, read standard input.

OPERATION
    count_by_hour
        count log data by hour.
    count_by_remote
        count log data by remote host name.
    -h, --help
        print help
OPTIONS
    --since <date>
        count log data after specific date.
        ex.)
            --since "2019-10-24 20:15:10 +0900"
            --since "2019-3-21 8:15:10 -0700"
    --until <date>
        count log data before specific date.
        ex.)
            --until "2019-10-24 20:15:10 +0900"
            --until "2019-3-21 8:15:10 -0700"
    --take <n>
        print only n items.
    --order <ascending|descending>
        result order. default is descending.
    --verbose
        Output progress info, etc.
)";
inline void print_help()
{
    std::cerr << help_text << std::flush;
}
inline date::sys_seconds date_parser(const char* date)
{
    std::stringstream ss(date);
    date::sys_seconds tp;
    date::from_stream(ss, "%Y-%m-%d %H:%M:%S %z", tp);
    return tp;
}
[[noreturn]] void print_help_and_abort(int code = 1)
{
    print_help();
    std::quick_exit(code);
}
}
inline options cmd_argument_parser(int argc, char** argv)
{
    using namespace std::string_view_literals;
    if (argc < 3) {
        detail::print_help_and_abort();
    }
    if (argv[1] == "--help"sv) {
        detail::print_help_and_abort(0);
    }
    options re;
    if (argv[1] == "count_by_hour"sv) {
        re.mode = count_mode::count_by_hour;
    }
    else if (argv[1] == "count_by_remote"sv) {
        re.mode = count_mode::count_by_remote;
    }
    else {
        detail::print_help_and_abort();
    }
    int i = 2;
    for (; i < argc; ++i) {
        if (argv[i] == "--since"sv) {
            if (i + 1 < argc)  {
                detail::print_help_and_abort();
            }
            re.since = detail::date_parser(argv[++i]);
        }
        else if (argv[i] == "--until"sv) {
            if (i + 1 < argc)  {
                detail::print_help_and_abort();
            }
            re.until = detail::date_parser(argv[++i]);
        }
        else if (argv[i] == "--take"sv) {
            if (i + 1 < argc)  {
                detail::print_help_and_abort();
            }
            re.take = std::stoull(argv[++i]);
        }
        else if (argv[i] == "--order") {
            if (i + 1 < argc)  {
                detail::print_help_and_abort();
            }
            ++i;
            //<ascending|descending>
            if (argv[i] == "ascending"sv) {
                re.order = order_mode::ascending;
            }
            else if (argv[i] == "descending"sv) {
                re.order = order_mode::descending;
            }
            else {
                detail::print_help_and_abort();
            }
        }
        else if (argv[i] == "--verbose"sv) {
            re.verbose = true;
        }
        else {
            break;
        }
    }
    if (i < argc && argv[i] != "-"sv) {
        re.files = argv + i;
    }
    return re;
}
#endif
