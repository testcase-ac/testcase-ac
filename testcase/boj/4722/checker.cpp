#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

const double EPS = 0.005 + 1e-9;

int countTestCases() {
    int cases = 0;
    while (true) {
        int n = inf.readInt();
        if (n == 0) {
            break;
        }
        ++cases;
        for (int i = 0; i < n; ++i) {
            inf.readInt();
            inf.readInt();
        }
    }
    return cases;
}

vector<double> readAnswers(InStream& stream, int cases) {
    vector<double> values;
    values.reserve(cases);

    for (int i = 0; i < cases; ++i) {
        double value = stream.readDouble(0.0, 1e100, format("answer[%d]", i + 1).c_str());
        values.push_back(value);
        stream.readEoln();
    }
    stream.readEof();

    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int cases = countTestCases();
    vector<double> jury = readAnswers(ans, cases);
    vector<double> participant = readAnswers(ouf, cases);

    for (int i = 0; i < cases; ++i) {
        double delta = fabs(jury[i] - participant[i]);
        if (delta > EPS) {
            quitf(_wa,
                  "answer[%d] differs from jury: expected %.10f, found %.10f, error %.10f",
                  i + 1,
                  jury[i],
                  participant[i],
                  delta);
        }
    }

    quitf(_ok, "%d answer(s) within %.10f absolute tolerance", cases, EPS);
}
