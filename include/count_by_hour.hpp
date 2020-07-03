#ifndef APACHE2_LOG_ANALYZER_COUNT_BY_HOUR_HPP_
#define APACHE2_LOG_ANALYZER_COUNT_BY_HOUR_HPP_
#include "cmd_argument_parser.hpp"
#include "line_splitter.hpp"
#include "date_parser.hpp"
#include <date/date.h>
#include <chrono>
#include <array>
#include <ostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
class count_by_hour {
private:
    std::array<std::size_t, 24> table_{};
    using tmp_array_elem_t = std::pair<std::size_t, std::size_t>;
    using tmp_array_t = std::array<tmp_array_elem_t, 24>;
public:
    count_by_hour() = default;
    count_by_hour(const count_by_hour&) = default;
    count_by_hour(count_by_hour&&) = default;
    count_by_hour& operator=(const count_by_hour&) = default;
    count_by_hour& operator=(count_by_hour&&) = default;
    void read(date::sys_seconds tp)
    {
        const auto dp = std::chrono::floor<date::days>(tp);
        const auto h = date::hh_mm_ss{tp - dp}.hours().count();
        ++this->table_.at(h - 1);
    }
    void read(const raw_parsed_line& line, const options& o)
    {
        const auto date = date_parser(line.time);
        if (date < o.since) return;
        if (o.until != date::sys_seconds{} && o.until < date) return;
        this->read(date);
    }
private:
    template<typename Compare>
    void print_impl(std::ostream& os, std::size_t take, Compare&& comp)
    {
        tmp_array_t tmp;
        std::size_t j = 0;
        std::transform(
            this->table_.begin(), this->table_.end(), tmp.begin(),
            [&j](std::size_t e) { return tmp_array_elem_t{j++, e}; }
        );
        std::sort(tmp.begin(), tmp.end(), std::forward<Compare>(comp));
        std::size_t n = 0;
        for (auto&& [i, e] : tmp) {
            if (e != 0) {
                os << std::setw(2) << std::setfill('0') << i + 1 << ':' << e << '\n';
                if (++n == take) break;
            }
        }
    }
public:
    void print(std::ostream& os, const options& o)
    {
        switch(o.order) {
        case order_mode::chronological:
            {
                std::size_t i = 1;
                for (auto&& e : this->table_) {
                    if (e != 0) {
                        os << std::setw(2) << std::setfill('0') << i << ':' << e << '\n';
                    }
                    ++i;
                }
            }
            break;
        case order_mode::ascending:
            this->print_impl(os, o.take, [](const tmp_array_elem_t& l, const tmp_array_elem_t& r){
                return l.second < r.second;
            });
            break;
        case order_mode::descending:
            this->print_impl(os, o.take, [](const tmp_array_elem_t& l, const tmp_array_elem_t& r){
                return l.second > r.second;
            });
            break;
        default:
            break;
        }
        os << std::flush;
    }
};
#endif
