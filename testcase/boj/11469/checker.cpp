#include "testlib.h"

#include <vector>

using namespace std;

vector<long long> years;

bool hasOnlyTwoAndThreePrimeFactors(long long value) {
    while (value % 2 == 0) {
        value /= 2;
    }
    while (value % 3 == 0) {
        value /= 3;
    }
    return value == 1;
}

void readAnswer(InStream& stream) {
    for (int tc = 0; tc < (int)years.size(); ++tc) {
        int m = stream.readInt(1, 100, format("m[%d]", tc + 1).c_str());
        stream.readEoln();
        vector<long long> cubes(m);
        long long sum = 0;

        for (int i = 0; i < m; ++i) {
            cubes[i] = stream.readLong(1LL, years[tc], format("cubes[%d][%d]", tc + 1, i + 1).c_str());
            if (!hasOnlyTwoAndThreePrimeFactors(cubes[i])) {
                stream.quitf(_wa,
                             "cubes[%d][%d]=%lld has a prime divisor other than 2 or 3",
                             tc + 1,
                             i + 1,
                             cubes[i]);
            }
            if (sum > years[tc] - cubes[i]) {
                stream.quitf(_wa, "sum of cubes for year %d exceeds %lld", tc + 1, years[tc]);
            }
            sum += cubes[i];
        }
        stream.readEoln();

        if (sum != years[tc]) {
            stream.quitf(_wa,
                         "sum of cubes for year %d is %lld instead of %lld",
                         tc + 1,
                         sum,
                         years[tc]);
        }

        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                if (cubes[i] % cubes[j] == 0 || cubes[j] % cubes[i] == 0) {
                    stream.quitf(_wa,
                                 "families %d and %d in year %d receive divisible amounts %lld and %lld",
                                 i + 1,
                                 j + 1,
                                 tc + 1,
                                 cubes[i],
                                 cubes[j]);
                }
            }
        }
    }

    stream.readEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    years.resize(t);
    for (int i = 0; i < t; ++i) {
        years[i] = inf.readLong();
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid distribution");
}
