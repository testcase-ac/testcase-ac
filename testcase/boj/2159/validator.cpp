#include "testlib.h"
#include <string>
#include <utility>
using namespace std;

pair<int, int> readPointLine(const string& name) {
    string line = inf.readLine("[^]*", name);
    size_t split = line.find(' ');
    ensuref(split != string::npos, "%s: missing space between coordinates", name.c_str());
    size_t yStart = line.find_first_not_of(' ', split);
    ensuref(yStart != string::npos, "%s: missing Y coordinate", name.c_str());
    ensuref(line.find(' ', yStart) == string::npos, "%s: trailing data after Y coordinate", name.c_str());

    string xToken = line.substr(0, split);
    string yToken = line.substr(yStart);
    ensuref(!xToken.empty(), "%s: missing X coordinate", name.c_str());
    for (char c : xToken) {
        ensuref('0' <= c && c <= '9', "%s: X coordinate must be decimal", name.c_str());
    }
    for (char c : yToken) {
        ensuref('0' <= c && c <= '9', "%s: Y coordinate must be decimal", name.c_str());
    }
    ensuref(xToken[0] != '0', "%s: X coordinate must be positive", name.c_str());
    ensuref(yToken[0] != '0', "%s: Y coordinate must be positive", name.c_str());
    ensuref(xToken.size() <= 6, "%s: X coordinate is too large", name.c_str());
    ensuref(yToken.size() <= 6, "%s: Y coordinate is too large", name.c_str());

    long long x = stoll(xToken);
    long long y = stoll(yToken);
    ensuref(x <= 100000, "%s: X coordinate must be at most 100000", name.c_str());
    ensuref(y <= 100000, "%s: Y coordinate must be at most 100000", name.c_str());
    return {(int)x, (int)y};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    readPointLine("start");

    for (int i = 1; i <= n; i++) {
        readPointLine(format("customer_%d", i));
    }

    inf.readEof();
    return 0;
}
