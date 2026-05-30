#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; use the repo policy cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        string line = inf.readLine();
        ensuref(!line.empty(), "testcase %d is empty", tc);
        for (char ch : line) {
            ensuref(isdigit(static_cast<unsigned char>(ch)) || ch == ' ',
                    "testcase %d contains invalid character", tc);
        }
        ensuref(line.front() != ' ' && line.back() != ' ', "testcase %d has leading or trailing space", tc);

        int count = 0;
        size_t pos = 0;
        while (pos < line.size()) {
            size_t next = line.find(' ', pos);
            string token = line.substr(pos, next == string::npos ? string::npos : next - pos);

            ++count;
            ensuref(count <= 100, "testcase %d has more than 100 numbers", tc);
            ensuref(!token.empty(), "testcase %d has an empty number token", tc);
            ensuref(token[0] != '0', "number %d in testcase %d has a leading zero", count, tc);
            ensuref(token.size() <= 5, "number %d in testcase %d has too many digits", count, tc);

            int value = stoi(token);
            ensuref(value <= 10000, "value %d in testcase %d is %d, expected at most 10000",
                    count, tc, value);

            if (next == string::npos) {
                break;
            }
            pos = next + 1;
        }
    }

    inf.readEof();
    return 0;
}
