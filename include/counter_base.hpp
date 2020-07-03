#ifndef APACHE2_LOG_ANALYZER_COUONTER_BASE_HPP_
#define APACHE2_LOG_ANALYZER_COUONTER_BASE_HPP_
#include "cmd_argument_parser.hpp"
#include "line_splitter.hpp"
#include "date_parser.hpp"
#include <type_traits>
class counter_base {
protected:
    static bool need_skip_read(date::sys_seconds date, const options& o)
    {
        if (date < o.since) return true;
        if (o.until != date::sys_seconds{} && o.until < date) return true;
        return false;
    }
    static bool need_skip_read(std::string_view time, const options& o)
    {
        const auto date = date_parser(time);
        return need_skip_read(date, o);
    }
public:
    counter_base() = default;
    counter_base(const counter_base&) = default;
    counter_base(counter_base&&) = default;
    counter_base& operator=(const counter_base&) = default;
    counter_base& operator=(counter_base&&) = default;
};
template<typename T>
struct is_counter : std::is_base_of<counter_base, T> {};
template<typename T>
inline constexpr bool is_counter_v = is_counter<T>::value;
#endif
