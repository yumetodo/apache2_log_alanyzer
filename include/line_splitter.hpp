/*=============================================================================
  Copyright (C) 2020 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef APACHE2_LOG_ANALYZER_LINE_SPLITTER_HPP_
#define APACHE2_LOG_ANALYZER_LINE_SPLITTER_HPP_
#include <string_view>
#include <string>
#include <utility>
#include <tuple>
#include <stdexcept>
struct raw_parsed_line
{
    std::string_view host;
    std::string_view time;
};
//192.35.168.144 - - [30/Jun/2020:11:30:43 +0900] "GET / HTTP/1.1" 200 3421 "-" "Mozilla/5.0 zgrab/0.x"
//127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] "GET /apache_pb.gif HTTP/1.0" 200 2326
#define INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE( MESSAGE ) throw invalid_line_syntax(__FILE__, __FUNCTION__, __LINE__, MESSAGE);
#define INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE_IF( EXPR, MESSAGE ) if( EXPR ){ throw invalid_line_syntax(__FILE__, __FUNCTION__, __LINE__, #EXPR, MESSAGE); }
class invalid_line_syntax : public std::runtime_error {
public:
    invalid_line_syntax(const char* sorce_name, const char* func_name, uint64_t line, const char* expression, const std::string& msg)
        : std::runtime_error(
            std::string("exception : invalid_line_syntax\n")
            + "  in " + sorce_name + "\n"
            + "  " + func_name + "() (line." + std::to_string(line) + ")\n"
            + "  follow by below\n"
            + "    " + expression
            + ((msg.empty() || msg[0] == '\0') ? "\n" : "\n  MESSAGE : " + msg + "\n")
        )
    {}
    invalid_line_syntax(const char* sorce_name, const char* func_name, uint64_t line, const std::string& msg)
        : std::runtime_error(
            std::string("exception : invalid_line_syntax\n")
            + " in " + sorce_name + "\n"
            + "  " + func_name + "() (line." + std::to_string(line) + ")\n"
            + ((msg.empty() || msg[0] == '\0') ? "\n" : " MESSAGE : " + msg + "\n")
        )
    {}

};
namespace {
    inline std::pair<std::string_view, std::string_view> extract_first_elem(std::string_view s, const char (&corresponding)[3] = "''")
    {
        using namespace std::string_literals;
        if (s[0] == corresponding[0]) {
            const auto last = s.find_first_of(corresponding[1], 1);
            INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE_IF(last == std::string_view::npos, "no match corresponding "s + corresponding[1] + '.');
            INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE_IF(
                last + 1 <= s.length() && s[last + 1] != ' ',
                "space will be required just after "s + corresponding[1] + '.'
            );
            // "a"
            // 012
            return { s.substr(1u, last - 1), s.length() == last ? std::string_view{} : s.substr(last + 1) };
        }
        INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE_IF(s[0] == ' ', "too many space was detected.");
        const auto last = s.find_first_of(' ');
        if (last == std::string_view::npos) {
            return { s, {} };
        }
        // abc
        // 0123
        return { s.substr(0, last),  s.length() == last ? std::string_view{} : s.substr(last + 1) };
    }
}
inline raw_parsed_line line_splitter(std::string_view line)
{
    raw_parsed_line re{};
    std::string_view next;
    std::tie(re.host, next) = extract_first_elem(line);
    INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE_IF(next.empty(), "too few element");
    std::tie(std::ignore, next) = extract_first_elem(next);
    INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE_IF(next.empty(), "too few element");
    std::tie(std::ignore, next) = extract_first_elem(next);
    INVALID_LINE_SYNTAX_THROW_WITH_MESSAGE_IF(next.empty(), "too few element");
    std::tie(re.time, std::ignore) = extract_first_elem(next, "[]");
    return re;
}
#endif
