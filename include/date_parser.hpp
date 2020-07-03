/*=============================================================================
  Copyright (C) 2020 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef APACHE2_LOG_ANALYZER_DATE_PARSER_HPP_
#define APACHE2_LOG_ANALYZER_DATE_PARSER_HPP_
#include <date/date.h>
#include <sstream>
#include <string_view>
#include <stdexcept>
#include <algorithm>
#define INVALID_DATE_SYNTAX_THROW_WITH_MESSAGE( MESSAGE ) throw invalid_date_syntax(__FILE__, __FUNCTION__, __LINE__, MESSAGE);
#define INVALID_DATE_SYNTAX_THROW_WITH_MESSAGE_IF( EXPR, MESSAGE ) if( EXPR ){ throw invalid_date_syntax(__FILE__, __FUNCTION__, __LINE__, #EXPR, MESSAGE); }
class invalid_date_syntax : public std::runtime_error {
public:
    invalid_date_syntax(const char* sorce_name, const char* func_name, uint64_t line, const char* expression, const std::string& msg)
        : std::runtime_error(
            std::string("exception : invalid_date_syntax\n")
            + "  in " + sorce_name + "\n"
            + "  " + func_name + "() (line." + std::to_string(line) + ")\n"
            + "  follow by below\n"
            + "    " + expression
            + ((msg.empty() || msg[0] == '\0') ? "\n" : "\n  MESSAGE : " + msg + "\n")
        )
    {}
    invalid_date_syntax(const char* sorce_name, const char* func_name, uint64_t line, const std::string& msg)
        : std::runtime_error(
            std::string("exception : invalid_date_syntax\n")
            + " in " + sorce_name + "\n"
            + "  " + func_name + "() (line." + std::to_string(line) + ")\n"
            + ((msg.empty() || msg[0] == '\0') ? "\n" : " MESSAGE : " + msg + "\n")
        )
    {}

};
namespace detail {
    inline std::size_t month_str_to_month_num(std::string_view s)
    {
        constexpr const char* table[] = {
            "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
        };
        const auto it = std::find(std::begin(table), std::end(table), s);
        return it == std::end(table) ? 0u : it - table + 1;
    }
}
inline date::sys_seconds date_parser(std::string_view s)
{
    std::stringstream ss;
    const auto first_sep = s.find_first_of('/');
    INVALID_DATE_SYNTAX_THROW_WITH_MESSAGE_IF(first_sep == std::string_view::npos, "missing /.");
    INVALID_DATE_SYNTAX_THROW_WITH_MESSAGE_IF(first_sep == s.length(), "missing month info.");
    const auto month_front = first_sep + 1;
    const auto second_sep = s.find_first_of('/', month_front);
    INVALID_DATE_SYNTAX_THROW_WITH_MESSAGE_IF(second_sep == std::string_view::npos, "missing /.");
    const auto month_str = s.substr(month_front, second_sep - month_front);
    const auto month = detail::month_str_to_month_num(month_str);
    INVALID_DATE_SYNTAX_THROW_WITH_MESSAGE_IF(month == 0, "not known such a month: " + std::string(month_str));
    ss << s.substr(0, month_front) << month << s.substr(second_sep);
    date::sys_seconds tp;
    date::from_stream(ss, "%d/%m/%Y:%H:%M:%S %z", tp);
    INVALID_DATE_SYNTAX_THROW_WITH_MESSAGE_IF(tp == date::sys_seconds{}, "fail to parse.");
    return tp;
}
#endif
