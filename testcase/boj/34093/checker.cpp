#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct Fenwick {
    int n;
    vector<int> tree;

    explicit Fenwick(int n_) : n(n_), tree(n_ + 1, 0) {}

    void add(int index, int delta) {
        for (int i = index; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }

    int kth(int k) const {
        int index = 0;
        int bit = 1;
        while ((bit << 1) <= n) {
            bit <<= 1;
        }
        for (; bit > 0; bit >>= 1) {
            int next = index + bit;
            if (next <= n && tree[next] < k) {
                index = next;
                k -= tree[next];
            }
        }
        return index + 1;
    }
};

struct TestCase {
    int n;
    int target;
    int minLimit;
    int maxLimit;
    vector<int> values;
};

struct Claim {
    bool possible;
};

string lowerToken(string token) {
    for (char& ch : token) {
        ch = char(tolower(static_cast<unsigned char>(ch)));
    }
    return token;
}

Claim readClaim(InStream& stream, const TestCase& tc, int caseIndex) {
    string verdict = lowerToken(stream.readToken("[A-Za-z]+", format("case %d verdict", caseIndex).c_str()));
    if (verdict == "no") {
        return {false};
    }
    if (verdict != "yes") {
        stream.quitf(_wa, "case %d verdict must be yes or no, found '%s'", caseIndex, verdict.c_str());
    }

    string operations = stream.readToken(format("[mM]{%d}", tc.n - 1),
                                         format("case %d operation string", caseIndex).c_str());

    int usedMin = 0;
    int usedMax = 0;
    Fenwick alive(tc.n);
    vector<int> current = tc.values;
    for (int i = 1; i <= tc.n; ++i) {
        alive.add(i, 1);
    }

    int remaining = tc.n;
    for (int step = 0; step < tc.n - 1; ++step) {
        char op = operations[step];
        if (op == 'm') {
            ++usedMin;
        } else {
            ++usedMax;
        }

        int position = stream.readInt(1, remaining - 1,
                                      format("case %d merge index %d", caseIndex, step + 1).c_str());
        int left = alive.kth(position);
        int right = alive.kth(position + 1);

        if (op == 'm') {
            current[left - 1] = min(current[left - 1], current[right - 1]);
        } else {
            current[left - 1] = max(current[left - 1], current[right - 1]);
        }
        alive.add(right, -1);
        --remaining;
    }

    if (usedMin > tc.minLimit) {
        stream.quitf(_wa,
                     "case %d uses %d minimum merges, exceeding limit %d",
                     caseIndex,
                     usedMin,
                     tc.minLimit);
    }
    if (usedMax > tc.maxLimit) {
        stream.quitf(_wa,
                     "case %d uses %d maximum merges, exceeding limit %d",
                     caseIndex,
                     usedMax,
                     tc.maxLimit);
    }

    int finalPosition = alive.kth(1);
    if (current[finalPosition - 1] != tc.target) {
        stream.quitf(_wa,
                     "case %d final time is %d, expected %d",
                     caseIndex,
                     current[finalPosition - 1],
                     tc.target);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    vector<TestCase> tests(testCount);
    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        TestCase& tc = tests[caseIndex - 1];
        tc.n = inf.readInt();
        tc.target = inf.readInt();
        tc.minLimit = inf.readInt();
        tc.maxLimit = inf.readInt();
        tc.values.resize(tc.n);
        for (int i = 0; i < tc.n; ++i) {
            tc.values[i] = inf.readInt();
        }
    }

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        Claim jury = readClaim(ans, tests[caseIndex - 1], caseIndex);
        Claim participant = readClaim(ouf, tests[caseIndex - 1], caseIndex);

        if (!jury.possible) {
            if (!participant.possible) {
                continue;
            }
            quitf(_fail, "case %d: participant supplied a valid merge sequence but jury says no", caseIndex);
        }
        if (!participant.possible) {
            quitf(_wa, "case %d: jury has a valid merge sequence but participant says no", caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "all %d test cases are valid", testCount);
}
