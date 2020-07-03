#include "../include/count_by_remote.hpp"
#include "../iutest/include/iutest.hpp"
constexpr const char* input[] = {
    "127.0.0.1",
    "8.8.8.8",
    "127.0.0.1",
};
constexpr const char* ascending_expected = R"(8.8.8.8:1
127.0.0.1:2
)";
constexpr const char* descending_expected = R"(127.0.0.1:2
8.8.8.8:1
)";
IUTEST(CountByRemote, ascending)
{
    count_by_remote counter;
    options o;
    o.order = order_mode::ascending;
    for (auto&& i : input) {
        raw_parsed_line l;
        l.time = "30/Jun/2020:11:30:43 +0900";
        l.host = i;
        counter.read(l, o);
    }
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT_EQ(ascending_expected, ss.str());
}
IUTEST(CountByRemote, descending)
{
    count_by_remote counter;
    options o;
    o.order = order_mode::descending;
    for (auto&& i : input) {
        raw_parsed_line l;
        l.time = "30/Jun/2020:11:30:43 +0900";
        l.host = i;
        counter.read(l, o);
    }
    std::stringstream ss;
    counter.print(ss, o);
    IUTEST_ASSERT_EQ(descending_expected, ss.str());
}
