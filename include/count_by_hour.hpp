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
    }
    void read(const raw_parsed_line& line, const options& o)
    {
    }
    void print(std::ostream& os, const options& o)
    {
    }
};
#endif
