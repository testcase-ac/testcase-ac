#include "testlib.h"

#include <vector>

using namespace std;

constexpr int kMaxX = (1 << 30) - 1;

int mexAfterAnd(const vector<int>& values, int x) {
    vector<char> seen(values.size() + 1, 0);
    for (int value : values) {
        int transformed = value & x;
        if (transformed <= static_cast<int>(values.size())) {
            seen[transformed] = 1;
        }
    }

    int mex = 0;
    while (mex < static_cast<int>(seen.size()) && seen[mex]) {
        ++mex;
    }
    return mex;
}

struct Claim {
    int x;
    int mex;
};

Claim readClaim(InStream& stream, const vector<int>& values, int test_case) {
    int x = stream.readInt(0, kMaxX, format("x[%d]", test_case).c_str());
    return {x, mexAfterAnd(values, x)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt();
        vector<int> values(n);
        for (int i = 0; i < n; ++i) {
            values[i] = inf.readInt();
        }

        Claim jury = readClaim(ans, values, tc);
        Claim part = readClaim(ouf, values, tc);

        if (part.mex < jury.mex) {
            quitf(_wa,
                  "test case %d: participant x=%d gives MEX %d, jury x=%d gives MEX %d",
                  tc,
                  part.x,
                  part.mex,
                  jury.x,
                  jury.mex);
        }
        if (part.mex > jury.mex) {
            quitf(_fail,
                  "test case %d: participant x=%d gives better MEX %d than jury x=%d with MEX %d",
                  tc,
                  part.x,
                  part.mex,
                  jury.x,
                  jury.mex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d test case(s) match the jury optimum value", t);
}
