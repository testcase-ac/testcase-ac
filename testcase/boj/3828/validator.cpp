#include "testlib.h"

#include <cmath>
#include <cctype>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

const int MAX_CASES = 100000;
const long double FIT_EPS = 1.0e-4L;

bool isZeroToken(const string& token) {
    for (char ch : token) {
        if (isdigit(static_cast<unsigned char>(ch)) && ch != '0') {
            return false;
        }
    }
    return true;
}

long double readRealValue(const string& name) {
    string token = inf.readToken("-?[0-9][0-9.]{0,63}", name);

    size_t pos = 0;
    bool negative = false;
    if (token[pos] == '-') {
        negative = true;
        ++pos;
        ensuref(pos < token.size(), "%s has no digits: %s", name.c_str(), token.c_str());
    }

    size_t intBegin = pos;
    while (pos < token.size() && isdigit(static_cast<unsigned char>(token[pos]))) {
        ++pos;
    }
    ensuref(pos > intBegin, "%s has no integer part: %s", name.c_str(), token.c_str());

    string intPart = token.substr(intBegin, pos - intBegin);
    ensuref(intPart == "0" || intPart[0] != '0',
            "%s has leading zeroes: %s", name.c_str(), token.c_str());

    if (pos < token.size()) {
        ensuref(token[pos] == '.', "%s has invalid decimal separator: %s",
                name.c_str(), token.c_str());
        ++pos;
        size_t fracBegin = pos;
        while (pos < token.size() && isdigit(static_cast<unsigned char>(token[pos]))) {
            ++pos;
        }
        ensuref(pos > fracBegin, "%s has no fractional digits: %s",
                name.c_str(), token.c_str());
    }

    ensuref(pos == token.size(), "%s has invalid characters: %s",
            name.c_str(), token.c_str());
    ensuref(!negative || !isZeroToken(token), "%s uses negative zero: %s",
            name.c_str(), token.c_str());

    long double value = stold(token);
    ensuref(-100.0L < value && value < 100.0L,
            "%s is outside (-100.0, 100.0): %s", name.c_str(), token.c_str());
    return value;
}

long double interpolateAt(const vector<pair<long double, long double>>& points,
                          int degree, long double x) {
    long double result = 0.0L;
    for (int i = 0; i <= degree; ++i) {
        long double term = points[i].second;
        for (int j = 0; j <= degree; ++j) {
            if (i == j) {
                continue;
            }
            term *= (x - points[j].first) / (points[i].first - points[j].first);
        }
        result += term;
    }
    return result;
}

bool isWrongCandidate(const vector<long double>& values, int degree, int wrongIndex) {
    vector<pair<long double, long double>> kept;
    for (int i = 0; i <= degree + 2; ++i) {
        if (i != wrongIndex) {
            kept.push_back({static_cast<long double>(i), values[i]});
        }
    }

    for (const auto& point : kept) {
        long double expected = interpolateAt(kept, degree, point.first);
        if (fabsl(point.second - expected) > FIT_EPS) {
            return false;
        }
    }

    long double wrongExpected = interpolateAt(kept, degree, wrongIndex);
    return fabsl(values[wrongIndex] - wrongExpected) > 1.0L;
}

void validateDataset(int caseIndex, int degree) {
    setTestCase(caseIndex);

    vector<long double> values(degree + 3);
    for (int i = 0; i <= degree + 2; ++i) {
        values[i] = readRealValue("v_i");
        inf.readEoln();
    }

    int candidateCount = 0;
    for (int i = 0; i <= degree + 2; ++i) {
        if (isWrongCandidate(values, degree, i)) {
            ++candidateCount;
        }
    }

    ensuref(candidateCount == 1,
            "dataset must have exactly one value with error greater than 1.0, found %d",
            candidateCount);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int degree = inf.readInt(0, 5, "d");
        inf.readEoln();
        if (degree == 0) {
            break;
        }

        ++caseCount;
        // CHECK: The statement gives no test case count, so cap datasets locally.
        ensuref(caseCount <= MAX_CASES, "too many datasets: %d", caseCount);
        validateDataset(caseCount, degree);
    }

    inf.readEof();
}
