#include "testlib.h"

#include <vector>

using namespace std;

struct Term {
    int two;
    int three;
};

long long termValue(InStream& stream, const Term& term, int caseIndex, int termIndex, TResult verdict) {
    __int128 value = 1;
    for (int i = 0; i < term.two; ++i) {
        value *= 2;
        if (value > 2147483647LL) {
            stream.quitf(verdict, "case %d term %d exceeds input bound", caseIndex, termIndex);
        }
    }
    for (int i = 0; i < term.three; ++i) {
        value *= 3;
        if (value > 2147483647LL) {
            stream.quitf(verdict, "case %d term %d exceeds input bound", caseIndex, termIndex);
        }
    }
    return static_cast<long long>(value);
}

bool termDivides(const Term& lhs, const Term& rhs) {
    return lhs.two <= rhs.two && lhs.three <= rhs.three;
}

void readRepresentation(InStream& stream, int caseIndex, int target, TResult verdict) {
    int m = stream.readInt(1, 20, format("M[%d]", caseIndex).c_str());
    stream.readEoln();

    vector<Term> terms(m);
    long long sum = 0;
    for (int i = 0; i < m; ++i) {
        terms[i].two = stream.readInt(0, 30, format("a[%d][%d]", caseIndex, i + 1).c_str());
        terms[i].three = stream.readInt(0, 19, format("b[%d][%d]", caseIndex, i + 1).c_str());
        stream.readEoln();

        long long value = termValue(stream, terms[i], caseIndex, i + 1, verdict);
        if (sum > target - value) {
            stream.quitf(verdict, "case %d sum exceeds N", caseIndex);
        }
        sum += value;
    }

    if (sum != target) {
        stream.quitf(verdict, "case %d sum is %lld instead of %d", caseIndex, sum, target);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (termDivides(terms[i], terms[j]) || termDivides(terms[j], terms[i])) {
                stream.quitf(verdict,
                             "case %d terms %d and %d are in a divisor relation",
                             caseIndex,
                             i + 1,
                             j + 1);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<int> targets(t);
    for (int i = 0; i < t; ++i) {
        targets[i] = inf.readInt();
    }

    for (int i = 0; i < t; ++i) {
        readRepresentation(ans, i + 1, targets[i], _fail);
    }
    ans.readEof();

    for (int i = 0; i < t; ++i) {
        readRepresentation(ouf, i + 1, targets[i], _wa);
    }
    ouf.readEof();

    quitf(_ok, "all %d representations are valid", t);
}
