#include "testlib.h"

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<long long> values;
};

vector<TestCase> cases;

bool isAscending(const vector<long long>& values) {
    for (int i = 1; i < static_cast<int>(values.size()); ++i) {
        if (values[i - 1] > values[i]) {
            return false;
        }
    }
    return true;
}

bool isDescending(const vector<long long>& values) {
    for (int i = 1; i < static_cast<int>(values.size()); ++i) {
        if (values[i - 1] < values[i]) {
            return false;
        }
    }
    return true;
}

void readClaim(InStream& stream) {
    int t = stream.readInt(1, static_cast<int>(cases.size()), "T");
    if (t != static_cast<int>(cases.size())) {
        stream.quitf(_wa, "T is %d, expected %d", t, static_cast<int>(cases.size()));
    }

    for (int tc = 0; tc < t; ++tc) {
        int n = stream.readInt(3, 1000, format("N[%d]", tc + 1).c_str());
        if (n != cases[tc].n) {
            stream.quitf(_wa, "N[%d] is %d, expected %d", tc + 1, n, cases[tc].n);
        }

        vector<long long> output(n);
        for (int i = 0; i < n; ++i) {
            output[i] = stream.readLong(static_cast<long long>(INT_MIN),
                                        static_cast<long long>(INT_MAX),
                                        format("S[%d][%d]", tc + 1, i + 1).c_str());
        }

        vector<long long> sortedOutput = output;
        sort(sortedOutput.begin(), sortedOutput.end());
        if (sortedOutput != cases[tc].values) {
            stream.quitf(_wa, "case %d does not contain exactly the input numbers", tc + 1);
        }

        if (isAscending(output)) {
            stream.quitf(_wa, "case %d is sorted in ascending order", tc + 1);
        }
        if (isDescending(output)) {
            stream.quitf(_wa, "case %d is sorted in descending order", tc + 1);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after all test cases");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        cases[tc].n = n;
        cases[tc].values.resize(n);
        for (int i = 0; i < n; ++i) {
            cases[tc].values[i] = inf.readLong();
        }
        sort(cases[tc].values.begin(), cases[tc].values.end());
    }

    readClaim(ans);
    readClaim(ouf);

    quitf(_ok, "valid antisort output for %d case(s)", t);
}
