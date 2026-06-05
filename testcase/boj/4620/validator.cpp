#include "testlib.h"

#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int boards = 0;
    while (true) {
        string header = inf.readLine("[^]+", "n_or_sentinel");
        if (header == "-1") {
            break;
        }

        ensuref(!header.empty(), "board size line must not be empty");
        ensuref(header[0] != '0', "board size has leading zero: %s", header.c_str());
        for (char ch : header) {
            ensuref('0' <= ch && ch <= '9', "board size must be a positive integer: %s", header.c_str());
        }

        int n = atoi(header.c_str());
        ensuref(4 <= n && n <= 34, "n must be between 4 and 34, found %d", n);

        ++boards;
        setTestCase(boards);
        ensuref(boards <= 30, "input contains more than 30 boards");

        string rowPattern = "[0-9]{" + to_string(n) + "," + to_string(n) + "}";
        for (int row = 0; row < n; ++row) {
            inf.readLine(rowPattern, "board_row");
        }
    }

    ensuref(boards >= 1, "input must contain at least one board");
    inf.readEof();
    return 0;
}
