#include "testlib.h"

#include <vector>

using namespace std;

struct TestCase {
    int n;
    long long m;
};

struct Fenwick {
    vector<int> tree;

    explicit Fenwick(int n) : tree(n + 1, 0) {}

    void add(int pos, int value) {
        for (int i = pos; i < (int)tree.size(); i += i & -i) {
            tree[i] += value;
        }
    }

    int sum(int pos) const {
        int result = 0;
        for (int i = pos; i > 0; i -= i & -i) {
            result += tree[i];
        }
        return result;
    }
};

long long readAndScorePermutation(InStream& stream,
                                  const TestCase& tc,
                                  int caseIndex,
                                  TResult verdictOnInvalid) {
    vector<int> used(tc.n + 1, 0);
    Fenwick fenwick(tc.n);
    long long inversions = 0;

    for (int i = 1; i <= tc.n; ++i) {
        int value = stream.readInt(1, tc.n, format("case %d value %d", caseIndex, i).c_str());
        if (used[value]) {
            stream.quitf(verdictOnInvalid, "case %d value %d is repeated", caseIndex, value);
        }
        used[value] = 1;

        int notGreaterBefore = fenwick.sum(value);
        inversions += (i - 1) - notGreaterBefore;
        fenwick.add(value, 1);

        if (i < tc.n) {
            stream.readSpace();
        } else {
            stream.readEoln();
        }
    }

    return inversions;
}

void validateOutput(InStream& stream, const vector<TestCase>& tests, TResult verdictOnInvalid) {
    for (int caseIndex = 1; caseIndex <= (int)tests.size(); ++caseIndex) {
        long long inversions =
            readAndScorePermutation(stream, tests[caseIndex - 1], caseIndex, verdictOnInvalid);
        if (inversions != tests[caseIndex - 1].m) {
            stream.quitf(verdictOnInvalid,
                         "case %d has inversion count %lld instead of %lld",
                         caseIndex,
                         inversions,
                         tests[caseIndex - 1].m);
        }
    }
    stream.readEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> tests(t);
    for (int i = 0; i < t; ++i) {
        tests[i].n = inf.readInt();
        tests[i].m = inf.readLong();
    }

    validateOutput(ans, tests, _fail);
    validateOutput(ouf, tests, _wa);

    quitf(_ok, "all %d permutation(s) have the requested inversion count", t);
}
