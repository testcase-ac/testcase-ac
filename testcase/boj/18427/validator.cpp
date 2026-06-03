#include "testlib.h"

#include <set>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10, "M");
    inf.readSpace();
    inf.readInt(1, 1000, "H");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string line = inf.readLine();
        ensuref(!line.empty(), "student %d line is empty", i);
        for (char c : line) {
            ensuref(('0' <= c && c <= '9') || c == ' ',
                    "student %d line contains invalid character", i);
        }
        ensuref(line.front() != ' ' && line.back() != ' ',
                "student %d line has leading or trailing space", i);
        ensuref(line.find("  ") == string::npos,
                "student %d line has repeated spaces", i);

        istringstream in(line);
        set<int> seen;
        int count = 0;
        string token;
        while (in >> token) {
            ++count;
            ensuref(token == "0" || token.front() != '0',
                    "student %d has block height with leading zero: %s", i, token.c_str());
            int height = stoi(token);
            ensuref(1 <= height && height <= 1000,
                    "student %d has block height out of range: %d", i, height);
            ensuref(seen.insert(height).second,
                    "student %d has duplicate block height: %d", i, height);
        }

        ensuref(count <= m, "student %d has %d blocks, exceeding M=%d", i, count, m);
    }

    inf.readEof();
}
