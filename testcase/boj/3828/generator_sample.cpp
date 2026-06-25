#include "testlib.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {

const long double FIT_EPS = 1.0e-4L;

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

bool hasUniqueWrongValue(const vector<long double>& values, int degree) {
    int candidateCount = 0;
    for (int i = 0; i <= degree + 2; ++i) {
        if (isWrongCandidate(values, degree, i)) {
            ++candidateCount;
        }
    }
    return candidateCount == 1;
}

double printableValue(long double value) {
    if (fabsl(value) < 0.0000005L) {
        return 0.0;
    }
    return static_cast<double>(value);
}

vector<long double> makeDataset(int degree) {
    for (int attempt = 0; attempt < 10000; ++attempt) {
        vector<long double> values(degree + 3);
        vector<pair<long double, long double>> basePoints;
        for (int i = 0; i <= degree; ++i) {
            values[i] = rnd.next(-20, 20);
            basePoints.push_back({static_cast<long double>(i), values[i]});
        }
        for (int i = degree + 1; i <= degree + 2; ++i) {
            values[i] = interpolateAt(basePoints, degree, i);
        }

        bool inRange = true;
        for (long double value : values) {
            if (!(value > -90.0L && value < 90.0L)) {
                inRange = false;
            }
        }
        if (!inRange) {
            continue;
        }

        int wrongIndex = rnd.next(0, degree + 2);
        vector<int> shifts;
        for (int shift = -12; shift <= -2; ++shift) {
            shifts.push_back(shift);
        }
        for (int shift = 2; shift <= 12; ++shift) {
            shifts.push_back(shift);
        }
        shuffle(shifts.begin(), shifts.end());

        for (int shift : shifts) {
            vector<long double> candidate = values;
            candidate[wrongIndex] += shift;
            bool rangeOk = true;
            for (long double value : candidate) {
                if (!(value > -100.0L && value < 100.0L)) {
                    rangeOk = false;
                }
            }
            if (rangeOk && hasUniqueWrongValue(candidate, degree)) {
                return candidate;
            }
        }
    }

    quitf(_fail, "failed to generate a valid dataset for degree %d", degree);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasetCount = rnd.next(2, 8);
    cout << fixed << setprecision(6);
    for (int caseIndex = 0; caseIndex < datasetCount; ++caseIndex) {
        int degree = rnd.next(1, 5);
        println(degree);

        vector<long double> values = makeDataset(degree);
        for (long double value : values) {
            cout << printableValue(value) << '\n';
        }
    }
    println(0);

    return 0;
}
