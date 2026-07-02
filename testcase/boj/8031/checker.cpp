#include "testlib.h"

#include <vector>

using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

void readAnswer(InStream& stream, const vector<int>& values, TResult verdict) {
    for (int caseIndex = 0; caseIndex < (int)values.size(); ++caseIndex) {
        int target = values[caseIndex];
        int count = stream.readInt(1, 100000, format("m[%d]", caseIndex + 1).c_str());
        stream.readEoln();

        long long sum = 0;
        int previous = 0;
        for (int i = 0; i < count; ++i) {
            int value = stream.readInt(3, target, format("addend[%d][%d]", caseIndex + 1, i + 1).c_str());
            if (i + 1 < count) {
                stream.readSpace();
            } else {
                stream.readEoln();
            }

            if (value % 2 == 0) {
                stream.quitf(verdict, "case %d addend %d is even", caseIndex + 1, value);
            }
            if (value <= previous) {
                stream.quitf(verdict,
                             "case %d addends are not strictly ascending at position %d: %d after %d",
                             caseIndex + 1,
                             i + 1,
                             value,
                             previous);
            }
            if (!isPrime(value)) {
                stream.quitf(verdict, "case %d addend %d is not prime", caseIndex + 1, value);
            }

            previous = value;
            sum += value;
            if (sum > target) {
                stream.quitf(verdict,
                             "case %d addends sum to more than target %d",
                             caseIndex + 1,
                             target);
            }
        }

        if (sum != target) {
            stream.quitf(verdict,
                         "case %d addends sum to %lld instead of %d",
                         caseIndex + 1,
                         sum,
                         target);
        }
    }

    stream.readEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = inf.readInt();
    }

    readAnswer(ans, values, _fail);
    readAnswer(ouf, values, _wa);

    quitf(_ok, "valid decompositions for %d case(s)", n);
}
