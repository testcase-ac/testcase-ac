#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAX_VALUE = (1 << 20) - 1;

int testCount;
vector<set<int>> targetSets;

struct Claim {
    bool impossible;
};

bool producesTargetSet(const vector<int>& values, const set<int>& target) {
    set<int> produced;
    vector<int> previous;

    for (int value : values) {
        vector<int> current;
        current.push_back(value);
        for (int oldValue : previous) {
            current.push_back(oldValue & value);
        }

        sort(current.begin(), current.end());
        current.erase(unique(current.begin(), current.end()), current.end());
        for (int andValue : current) {
            produced.insert(andValue);
        }
        previous.swap(current);
    }

    return produced == target;
}

Claim readClaim(InStream& stream, int caseIndex) {
    int n = (int)targetSets[caseIndex].size();
    int first = stream.readInt(-1, 5 * n, format("case %d answer size", caseIndex + 1).c_str());
    if (first == -1) {
        return {true};
    }
    if (first == 0) {
        stream.quitf(_wa, "case %d has zero-length array", caseIndex + 1);
    }

    vector<int> values(first);
    for (int i = 0; i < first; ++i) {
        values[i] = stream.readInt(0, MAX_VALUE, format("case %d a[%d]", caseIndex + 1, i + 1).c_str());
    }

    if (!producesTargetSet(values, targetSets[caseIndex])) {
        stream.quitf(_wa, "case %d array does not produce the required AND set", caseIndex + 1);
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    testCount = inf.readInt(1, 100000, "t");
    targetSets.resize(testCount);
    for (int caseIndex = 0; caseIndex < testCount; ++caseIndex) {
        int n = inf.readInt(1, 100000, format("case %d n", caseIndex + 1).c_str());
        for (int i = 0; i < n; ++i) {
            int value = inf.readInt(0, MAX_VALUE, format("case %d b[%d]", caseIndex + 1, i + 1).c_str());
            targetSets[caseIndex].insert(value);
        }
    }

    for (int caseIndex = 0; caseIndex < testCount; ++caseIndex) {
        Claim jury = readClaim(ans, caseIndex);
        Claim participant = readClaim(ouf, caseIndex);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d has valid participant witness while jury says impossible", caseIndex + 1);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d participant says impossible but jury has a witness", caseIndex + 1);
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
