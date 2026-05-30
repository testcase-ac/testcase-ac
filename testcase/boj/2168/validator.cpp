#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string line = inf.readLine("[^]+", "x_y");
    size_t pos = 0;

    auto readNatural = [&](const char* name) {
        ensuref(pos < line.size() && isdigit(static_cast<unsigned char>(line[pos])),
                "%s must start with a digit", name);
        ensuref(line[pos] != '0', "%s must be a natural number without leading zeroes", name);

        long long value = 0;
        while (pos < line.size() && isdigit(static_cast<unsigned char>(line[pos]))) {
            value = value * 10 + (line[pos] - '0');
            ensuref(value <= 1000000000LL, "%s must be at most 1000000000", name);
            ++pos;
        }
        return value;
    };

    long long x = readNatural("x");
    ensuref(pos < line.size() && line[pos] == ' ', "x and y must be separated by spaces");
    while (pos < line.size() && line[pos] == ' ') {
        ++pos;
    }
    long long y = readNatural("y");
    ensuref(pos == line.size(), "unexpected character after y");
    ensuref(x <= 1000000000LL, "x must be at most 1000000000");
    ensuref(y <= 1000000000LL, "y must be at most 1000000000");

    inf.readEof();
    return 0;
}
