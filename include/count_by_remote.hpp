/*=============================================================================
  Copyright (C) 2020 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef APACHE2_LOG_ANALYZER_COUNT_BY_REMOTE_HPP_
#define APACHE2_LOG_ANALYZER_COUNT_BY_REMOTE_HPP_
#include "counter_base.hpp"
#include <unordered_map>
#include <vector>
#include <string>
class count_by_remote : public counter_base {
private:
    std::unordered_map<std::string, std::size_t> table_;
    using tmp_array_elem_t = std::pair<std::string, std::size_t>;
public:
    count_by_remote() = default;
    count_by_remote(const count_by_remote&) = default;
    count_by_remote(count_by_remote&&) = default;
    count_by_remote& operator=(const count_by_remote&) = default;
    count_by_remote& operator=(count_by_remote&&) = default;
    void read(const raw_parsed_line& line, const options& o)
    {
        if (need_skip_read(line.time, o)) return;
        ++this->table_[std::string(line.host)];
    }
private:
    template<typename Compare>
    void print_impl(std::ostream& os, std::size_t take, Compare&& comp)
    {
        std::vector<tmp_array_elem_t> tmp(this->table_.begin(), this->table_.end());
        std::sort(tmp.begin(), tmp.end(), std::forward<Compare>(comp));
        std::size_t n = 0;
        for (auto&& [h, c] : tmp) {
            if (c != 0) {
                os << h << ':' << c << '\n';
                if (++n == take) break;
            }
        }
    }
public:
    void print(std::ostream& os, const options& o)
    {
        switch(o.order) {
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
            throw std::invalid_argument("not known such a order_mode");
            break;
        }
        os << std::flush;
    }
};
#endif