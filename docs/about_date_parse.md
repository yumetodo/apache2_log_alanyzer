# 日時のパースについて

かつてC/C++標準で提供されてきた日時を扱うライブラリはお世辞にも機能面・扱いやすさ・安全性のすべての面で十分なものではなかった。

C++20では`std::chrono`名前空間の下にカレンダーと時差を扱えるようにするライブラリ群が追加された。  
[P0355R7: Extending `<chrono>` to Calendars and Time Zones](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0355r7.html)

しかしながら2020年7月2日現在ではこれを完全に実装している処理系は存在していない。

そこで、提案段階で参考として実装されたライブラリを用いることとした。  
[HowardHinnant/date: A date and time library based on the C++11/14/17 `<chrono>` header](https://github.com/HowardHinnant/date)

その使用方法について参考にしたリンク集を下に示す。

## リンク集

- [vcpkg/CONTROL at 67a031a4d5680b4acb8eeec28ec8c0e7b3dd8102 · microsoft/vcpkg](https://github.com/microsoft/vcpkg/blob/67a031a4d5680b4acb8eeec28ec8c0e7b3dd8102/ports/date/CONTROL)
- [date](https://howardhinnant.github.io/date/date.html)
- [chrono - cpprefjp C++日本語リファレンス](https://cpprefjp.github.io/reference/chrono.html)
- [utc_time - cpprefjp C++日本語リファレンス](https://cpprefjp.github.io/reference/chrono/utc_time.html)
- [from_stream - cpprefjp C++日本語リファレンス](https://cpprefjp.github.io/reference/chrono/duration/from_stream.html)
- [year_month_day::operator sys_days - cpprefjp C++日本語リファレンス](https://cpprefjp.github.io/reference/chrono/year_month_day/op_sys_days.html)
- [minリテラル - cpprefjp C++日本語リファレンス](https://cpprefjp.github.io/reference/chrono/duration/op_min.html)
- [C++標準ライブラリのカレンダー(Calendar) - yohhoyの日記](https://yohhoy.hatenadiary.jp/entry/20180322/p1)
- [time - Extract year/month/day etc. from std::chrono::time_point in C++ - Stack Overflow](https://stackoverflow.com/questions/15957805/extract-year-month-day-etc-from-stdchronotime-point-in-c)
