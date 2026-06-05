#include "testlib.h"

#include <string>

using namespace std;

namespace {

const int kLimit = 300000000;
const int kMaxCases = 100000;

int parseCanonicalInt(const string& line, int& pos, char stop, const char* name) {
    int start = pos;
    ensuref(pos < static_cast<int>(line.size()) && line[pos] >= '0' && line[pos] <= '9',
            "%s must start with a digit", name);

    while (pos < static_cast<int>(line.size()) && line[pos] >= '0' && line[pos] <= '9') {
        ++pos;
    }

    if (stop == '\0') {
        ensuref(pos == static_cast<int>(line.size()), "%s must end the line", name);
    } else {
        ensuref(pos < static_cast<int>(line.size()) && line[pos] == stop,
                "%s must be followed by '%c'", name, stop);
    }

    string token = line.substr(start, pos - start);
    ensuref(token == "0" || token[0] != '0', "%s has leading zero: %s", name, token.c_str());

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        ensuref(value <= kLimit, "%s exceeds %d: %s", name, kLimit, token.c_str());
    }

    return static_cast<int>(value);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        string line = inf.readLine("[A-Z0-9]+", "line");
        ensuref(line[0] == 'R', "line must start with R");

        int pos = 1;
        int row = parseCanonicalInt(line, pos, 'C', "row");
        ++pos;
        int column = parseCanonicalInt(line, pos, '\0', "column");
        ensuref(pos == static_cast<int>(line.size()), "line has extra characters");

        if (row == 0 && column == 0) {
            break;
        }

        ensuref(row >= 1, "row must be positive before terminator");
        ensuref(column >= 1, "column must be positive before terminator");

        ++cases;
        // CHECK: the statement gives no case-count limit; cap repeated lines by local default.
        ensuref(cases <= kMaxCases, "too many input lines before terminator: %d", cases);
    }

    inf.readEof();
}
