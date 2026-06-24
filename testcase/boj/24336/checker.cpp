#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const double EPS = 1e-6;

vector<double> readAnswer(InStream& stream, int q, TResult invalidResult, const string& who) {
    vector<double> values(q);
    for (int i = 0; i < q; ++i) {
        string token = stream.readToken();
        char* end = nullptr;
        errno = 0;
        double value = strtod(token.c_str(), &end);
        if (end != token.c_str() + token.size() || errno == ERANGE || !isfinite(value)) {
            stream.quitf(invalidResult,
                         "%s answer[%d] is not a finite real number: %s",
                         who.c_str(),
                         i + 1,
                         token.c_str());
        }
        values[i] = value;
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after %s answers", who.c_str());
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    inf.readInt();
    inf.readSpace();
    int q = inf.readInt();

    vector<double> jury = readAnswer(ans, q, _fail, "jury");
    vector<double> participant = readAnswer(ouf, q, _wa, "participant");

    for (int i = 0; i < q; ++i) {
        if (!doubleCompare(jury[i], participant[i], EPS)) {
            quitf(_wa,
                  "answer[%d] differs: expected %.12f, found %.12f, error %.12f",
                  i + 1,
                  jury[i],
                  participant[i],
                  doubleDelta(jury[i], participant[i]));
        }
    }

    quitf(_ok, "%d answers are within tolerance", q);
}
