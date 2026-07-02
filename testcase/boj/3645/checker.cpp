#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<string> wins;
};

void validateSchedule(InStream& stream, const TestCase& tc, int caseIndex) {
    vector<int> alive(tc.n);
    for (int i = 0; i < tc.n; ++i) {
        alive[i] = i + 1;
    }

    int matchIndex = 0;
    while ((int)alive.size() > 1) {
        vector<int> present(tc.n + 1, 0);
        for (int team : alive) {
            present[team] = 1;
        }

        vector<int> used(tc.n + 1, 0);
        vector<int> next;
        int matches = (int)alive.size() / 2;
        for (int i = 0; i < matches; ++i) {
            ++matchIndex;
            string xName = format("case %d match %d first team", caseIndex, matchIndex);
            string yName = format("case %d match %d second team", caseIndex, matchIndex);
            int x = stream.readInt(1, tc.n, xName);
            int y = stream.readInt(1, tc.n, yName);

            if (x == y) {
                stream.quitf(_wa, "case %d match %d uses team %d twice", caseIndex, matchIndex, x);
            }
            if (!present[x]) {
                stream.quitf(_wa, "case %d match %d uses team %d that is not alive in this round", caseIndex, matchIndex, x);
            }
            if (!present[y]) {
                stream.quitf(_wa, "case %d match %d uses team %d that is not alive in this round", caseIndex, matchIndex, y);
            }
            if (used[x]) {
                stream.quitf(_wa, "case %d match %d repeats team %d in the same round", caseIndex, matchIndex, x);
            }
            if (used[y]) {
                stream.quitf(_wa, "case %d match %d repeats team %d in the same round", caseIndex, matchIndex, y);
            }
            used[x] = used[y] = 1;

            int winner = tc.wins[x - 1][y - 1] == '1' ? x : y;
            next.push_back(winner);
        }

        alive = next;
    }

    if (alive[0] != 1) {
        stream.quitf(_wa, "case %d champion is team %d instead of team 1", caseIndex, alive[0]);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    vector<TestCase> tests;
    while (!inf.seekEof()) {
        TestCase tc;
        tc.n = inf.readInt();
        tc.wins.resize(tc.n);
        for (int i = 0; i < tc.n; ++i) {
            tc.wins[i] = inf.readToken();
        }
        tests.push_back(tc);
    }

    for (int i = 0; i < (int)tests.size(); ++i) {
        validateSchedule(ans, tests[i], i + 1);
    }
    if (!ans.seekEof()) {
        ans.quitf(_wa, "extra output after jury schedule");
    }

    for (int i = 0; i < (int)tests.size(); ++i) {
        validateSchedule(ouf, tests[i], i + 1);
    }
    if (!ouf.seekEof()) {
        ouf.quitf(_wa, "extra output after participant schedule");
    }

    quitf(_ok, "%d valid schedule(s)", (int)tests.size());
}
