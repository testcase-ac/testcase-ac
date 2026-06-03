#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "m");
    inf.readEoln();

    long long area = 1LL * n * m;
    ensuref(4 <= area && area <= 9000000LL, "n * m must be between 4 and 9000000, found %lld", area);

    array<int, 6> count = {};
    string pattern = "[0-5]{" + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        string row = inf.readLine(pattern, "A_i");
        for (char c : row) {
            ++count[c - '0'];
        }
    }

    for (int value = 2; value <= 5; ++value) {
        ensuref(count[value] == 1, "digit %d must appear exactly once, found %d", value, count[value]);
    }

    inf.readEof();
}
