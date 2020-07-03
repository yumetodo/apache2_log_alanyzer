#include "../include/count_by_hour.hpp"
#include "../include/count_by_remote.hpp"
#include <fstream>
#include <exception>
template<typename Counter, typename std::enable_if_t<is_counter_v<Counter>, std::nullptr_t> = nullptr>
void read(std::istream& is, options o, Counter& c)
{
    for(std::string buf; std::getline(is, buf); ) {
        const auto l = line_splitter(buf);
        c.read(l, o);
    }
}
template<typename Counter, typename std::enable_if_t<is_counter_v<Counter>, std::nullptr_t> = nullptr>
void read(options o, Counter& c)
{
    using namespace std::string_view_literals;
    if (o.files == nullptr || o.files[0] == "-"sv) {
        read(std::cin, o, c);
    }
    else {
        for (std::size_t i = 0; o.files[i]; ++i) {
            if (o.verbose) {
                std::cerr << "open " << o.files[i] << std::endl;
            }
            std::ifstream ifs(o.files[i]);
            if (!ifs) {
                throw std::runtime_error("fail to open file.");
            }
            read(ifs, o, c);
        }
    }
}
template<typename Counter, typename std::enable_if_t<is_counter_v<Counter>, std::nullptr_t> = nullptr>
void exec(options o)
{
    Counter counter;
    read(o, counter);
    counter.print(std::cout, o);
}
int main(int argc, char* argv[])
{
    try {
        const auto o = cmd_argument_parser(argc, argv);
        switch (o.mode)
        {
        case count_mode::count_by_hour:
            exec<count_by_hour>(o);
            break;
        case count_mode::count_by_remote:
            exec<count_by_remote>(o);
            break;
        default:
            throw std::logic_error("unreachable place");
            break;
        }
        return 0;
    }
    catch (const std::exception& er) {
        std::cerr << er.what() << std::endl;
        return 1;
    }
}