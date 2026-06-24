#include "testlib.h"
#include <vector>
using namespace std;

struct TestCase {
    int n;
};

void readPartition(InStream& stream, const vector<TestCase>& cases, TResult invalidVerdict) {
    for (int tc = 0; tc < (int)cases.size(); ++tc) {
        int n = cases[tc].n;
        int pointCount = 3 * n;
        vector<int> used(pointCount + 1, 0);

        for (int triangle = 0; triangle < n; ++triangle) {
            for (int pos = 0; pos < 3; ++pos) {
                int index = stream.readInt(1, pointCount,
                                           format("case %d triangle %d index %d",
                                                  tc + 1, triangle + 1, pos + 1)
                                               .c_str());
                if (used[index]) {
                    stream.quitf(invalidVerdict,
                                 "case %d repeats point index %d",
                                 tc + 1, index);
                }
                used[index] = 1;
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after all triangle partitions");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        for (int i = 0; i < 3 * n; ++i) {
            inf.readLong();
            inf.readLong();
        }
        cases.push_back({n});
    }

    readPartition(ans, cases, _fail);
    readPartition(ouf, cases, _wa);

    quitf(_ok, "valid triangle partition");
}
