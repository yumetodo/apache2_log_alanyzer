#ifndef APACHE2_LOG_ANALYZER_LINE_SPLITTER_HPP_
#define APACHE2_LOG_ANALYZER_LINE_SPLITTER_HPP_
#include <string_view>
struct raw_parsed_line
{
    std::string_view host;
    std::string_view time;
};
//127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] "GET /apache_pb.gif HTTP/1.0" 200 2326

inline raw_parsed_line line_splitter(std::string_view line)
{
    return {};
}
#endif
