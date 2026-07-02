#include "testlib.h"

#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Request {
    int a;
    int b;
};

struct TestCase {
    int n;
    int m;
    vector<Request> requests;
};

vector<TestCase> tests;

void readClaim(InStream& stream) {
    for (int tc = 0; tc < (int)tests.size(); ++tc) {
        const TestCase& test = tests[tc];
        const int limit = 1 << test.n;

        set<tuple<int, int, int> > usedInputs;
        set<tuple<int, int, int> > usedOutputs;

        for (int i = 0; i < test.m; ++i) {
            int s = stream.readInt(0, limit - 1, format("s[%d][%d]", tc + 1, i + 1).c_str());

            for (int depth = 0; depth <= test.n; ++depth) {
                int prefix = s >> (test.n - depth);
                int inputPort = test.requests[i].a >> depth;
                int outputPort = test.requests[i].b >> depth;

                tuple<int, int, int> inputUse(depth, prefix, inputPort);
                if (!usedInputs.insert(inputUse).second) {
                    stream.quitf(_wa,
                                 "test case %d: input port conflict at depth %d, switch prefix %d, port %d",
                                 tc + 1,
                                 depth,
                                 prefix,
                                 inputPort);
                }

                tuple<int, int, int> outputUse(depth, prefix, outputPort);
                if (!usedOutputs.insert(outputUse).second) {
                    stream.quitf(_wa,
                                 "test case %d: output port conflict at depth %d, switch prefix %d, port %d",
                                 tc + 1,
                                 depth,
                                 prefix,
                                 outputPort);
                }
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after all test cases");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt(1, 100, "number of test cases");
    tests.resize(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt(1, 16, "n");
        int limit = 1 << n;
        int m = inf.readInt(1, limit, "m");

        tests[tc].n = n;
        tests[tc].m = m;
        tests[tc].requests.resize(m);

        for (int i = 0; i < m; ++i) {
            tests[tc].requests[i].a = inf.readInt(0, limit - 1, "a");
            tests[tc].requests[i].b = inf.readInt(0, limit - 1, "b");
        }
    }

    readClaim(ans);
    readClaim(ouf);

    quitf(_ok, "all connection paths are disjoint");
}
