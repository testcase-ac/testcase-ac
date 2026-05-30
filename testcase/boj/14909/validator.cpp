#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string line = inf.readLine("[^]+", "numbers");

    ensuref(!line.empty(), "the line must contain at least one integer");
    ensuref(line.front() != ' ', "leading space is not allowed");
    ensuref(line.back() != ' ', "trailing space is not allowed");

    int count = 0;
    size_t pos = 0;
    while (pos < line.size()) {
        size_t next = line.find(' ', pos);
        string token = line.substr(pos, next == string::npos ? string::npos : next - pos);

        ensuref(!token.empty(), "repeated spaces are not allowed");
        ensuref(++count <= 1000000, "too many integers: %d", count);

        size_t digitStart = 0;
        bool negative = false;
        if (token[0] == '-') {
            negative = true;
            digitStart = 1;
            ensuref(token.size() > 1, "minus sign without digits at integer %d", count);
        }

        ensuref(token[digitStart] >= '0' && token[digitStart] <= '9',
                "invalid integer at position %d: %s", count, token.c_str());
        for (size_t i = digitStart + 1; i < token.size(); ++i) {
            ensuref(token[i] >= '0' && token[i] <= '9',
                    "invalid integer at position %d: %s", count, token.c_str());
        }

        if (token[digitStart] == '0') {
            ensuref(token.size() == digitStart + 1,
                    "non-canonical leading zero at integer %d: %s", count, token.c_str());
            ensuref(!negative, "non-canonical negative zero at integer %d", count);
        }

        long long value = stoll(token);
        ensuref(-1000000 <= value && value <= 1000000,
                "integer %d is out of range: %lld", count, value);

        if (next == string::npos) {
            break;
        }
        pos = next + 1;
    }

    inf.readEof();
}
