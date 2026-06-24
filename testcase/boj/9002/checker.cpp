#include "testlib.h"

#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<vector<int>> manRank;
    vector<vector<int>> womanRank;
};

vector<TestCase> tests;

void readMatching(InStream& stream, const TestCase& tc, int caseIndex) {
    vector<int> wifeOfMan(tc.n + 1);
    vector<int> usedWoman(tc.n + 1, 0);

    for (int man = 1; man <= tc.n; ++man) {
        if (man > 1) {
            stream.readSpace();
        }
        int woman = stream.readInt(1, tc.n, format("case %d man %d partner", caseIndex, man).c_str());
        if (usedWoman[woman]) {
            stream.quitf(_wa, "case %d: woman %d is matched more than once", caseIndex, woman);
        }
        usedWoman[woman] = 1;
        wifeOfMan[man] = woman;
    }
    stream.readEoln();

    vector<int> husbandOfWoman(tc.n + 1, 0);
    for (int man = 1; man <= tc.n; ++man) {
        husbandOfWoman[wifeOfMan[man]] = man;
    }

    for (int man = 1; man <= tc.n; ++man) {
        int currentWoman = wifeOfMan[man];
        for (int woman = 1; woman <= tc.n; ++woman) {
            if (woman == currentWoman) {
                continue;
            }

            int currentMan = husbandOfWoman[woman];
            if (tc.manRank[man][woman] < tc.manRank[man][currentWoman] &&
                tc.womanRank[woman][man] < tc.womanRank[woman][currentMan]) {
                stream.quitf(_wa,
                             "case %d: unstable pair man %d and woman %d prefer each other",
                             caseIndex,
                             man,
                             woman);
            }
        }
    }

}

vector<vector<int>> readRanks(int n) {
    vector<vector<int>> rank(n + 1, vector<int>(n + 1));
    for (int person = 1; person <= n; ++person) {
        for (int order = 1; order <= n; ++order) {
            int id = inf.readInt();
            rank[person][id] = order;
        }
    }
    return rank;
}

void readAnswer(InStream& stream) {
    for (int caseIndex = 1; caseIndex <= (int)tests.size(); ++caseIndex) {
        readMatching(stream, tests[caseIndex - 1], caseIndex);
    }
    stream.readEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    tests.resize(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int n = inf.readInt();
        tests[caseIndex].n = n;
        tests[caseIndex].manRank = readRanks(n);
        tests[caseIndex].womanRank = readRanks(n);
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "stable matching for %d test case(s)", t);
}
