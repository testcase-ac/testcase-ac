#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<uint64_t> edges;
};

struct Claim {
    bool hasCycle;
};

uint64_t edgeKey(int from, int to) {
    return (uint64_t(from) << 32) | uint32_t(to);
}

bool hasEdge(const TestCase& tc, int from, int to) {
    return binary_search(tc.edges.begin(), tc.edges.end(), edgeKey(from, to));
}

Claim readClaim(InStream& stream, const TestCase& tc, int caseIndex) {
    int marker = stream.readInt(-1, 1, format("case %d marker", caseIndex).c_str());
    if (marker == 0) {
        stream.quitf(_wa, "case %d marker must be -1 or 1", caseIndex);
    }

    if (marker == -1) {
        return {false};
    }

    int length = stream.readInt(1, tc.n, format("case %d cycle length", caseIndex).c_str());
    if (length < 3) {
        stream.quitf(_wa, "case %d cycle length must be at least 3, found %d", caseIndex, length);
    }
    if (length % 2 == 0) {
        stream.quitf(_wa, "case %d cycle length must be odd, found %d", caseIndex, length);
    }

    vector<int> cycle(length);
    vector<char> used(tc.n + 1, 0);
    for (int i = 0; i < length; ++i) {
        cycle[i] = stream.readInt(1, tc.n, format("case %d cycle vertex %d", caseIndex, i + 1).c_str());
        if (used[cycle[i]]) {
            stream.quitf(_wa, "case %d repeats vertex %d", caseIndex, cycle[i]);
        }
        used[cycle[i]] = 1;
    }

    for (int i = 0; i < length; ++i) {
        int from = cycle[i];
        int to = cycle[(i + 1) % length];
        if (!hasEdge(tc, from, to)) {
            stream.quitf(_wa, "case %d edge %d -> %d is not in the graph", caseIndex, from, to);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int testCount = inf.readInt();
    vector<TestCase> tests(testCount);
    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        int n = inf.readInt();
        int m = inf.readInt();
        tests[caseIndex - 1].n = n;
        tests[caseIndex - 1].edges.reserve(m);
        for (int i = 0; i < m; ++i) {
            int from = inf.readInt();
            int to = inf.readInt();
            tests[caseIndex - 1].edges.push_back(edgeKey(from, to));
        }
        sort(tests[caseIndex - 1].edges.begin(), tests[caseIndex - 1].edges.end());
    }

    for (int caseIndex = 1; caseIndex <= testCount; ++caseIndex) {
        const TestCase& tc = tests[caseIndex - 1];
        Claim jury = readClaim(ans, tc, caseIndex);
        Claim participant = readClaim(ouf, tc, caseIndex);

        if (!jury.hasCycle) {
            if (participant.hasCycle) {
                quitf(_fail, "case %d: participant found a valid odd cycle while jury says -1", caseIndex);
            }
            continue;
        }

        if (!participant.hasCycle) {
            quitf(_wa, "case %d: jury provides an odd cycle but participant says -1", caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "all %d case(s) match the jury feasibility claim", testCount);
}
