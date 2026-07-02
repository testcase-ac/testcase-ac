#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const double EPS = 1e-4;
const double COMPARE_SLACK = 1e-12;

vector<double> readOutput(InStream& stream, int testCount, TResult verdict) {
    vector<double> values;
    values.reserve(testCount);

    for (int tc = 1; tc <= testCount; ++tc) {
        string token = stream.readToken();
        char* end = nullptr;
        errno = 0;
        double value = strtod(token.c_str(), &end);
        if (errno == ERANGE || end != token.c_str() + token.size() || !isfinite(value)) {
            stream.quitf(verdict, "answer[%d] is not a finite real number", tc);
        }
        values.push_back(value);
    }

    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %d answer(s)", testCount);
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    vector<double> jury = readOutput(ans, testCount, _fail);
    vector<double> participant = readOutput(ouf, testCount, _wa);

    for (int tc = 1; tc <= testCount; ++tc) {
        double expected = jury[tc - 1];
        double found = participant[tc - 1];
        double error = fabs(expected - found);

        if (error > EPS + COMPARE_SLACK) {
            quitf(_wa,
                  "case %d: expected %.12g, found %.12g, absolute error %.12g exceeds %.12g",
                  tc,
                  expected,
                  found,
                  error,
                  EPS);
        }
    }

    quitf(_ok, "all %d answer(s) are within absolute tolerance %.12g", testCount, EPS);
}
