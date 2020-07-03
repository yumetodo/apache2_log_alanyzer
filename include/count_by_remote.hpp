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
    }
    void print(std::ostream& os, const options& o)
    {
    }
};
#endif