#include "testlib.h"
using namespace std;

vector<int> buildTieSample() {
    // Sample from the statement (teams 1=A, 2=B, 3=C, 4=D)
    return {1, 2, 3, 3, 1, 3, 2, 4, 1, 1, 3, 1, 3, 3, 1};
}

vector<int> buildAllQualifiedCase() {
    int kQ = rnd.next(2, 4); // number of qualified teams
    vector<int> runners;
    for (int id = 1; id <= kQ; ++id) {
        for (int c = 0; c < 6; ++c)
            runners.push_back(id);
    }
    shuffle(runners.begin(), runners.end());
    return runners;
}

vector<int> buildQualifiedWithNonQualified(int kQualified, bool forceNonQualified) {
    // Each qualified team has exactly 6 runners
    // Non-qualified teams have 1..5 runners
    int maxExtraSlots = 40 - 6 * kQualified; // total remaining runner slots
    int maxNQTeams = min(4, maxExtraSlots);  // each NQ has at least 1 runner
    int minNQTeams = forceNonQualified ? 1 : 0;
    if (maxNQTeams < minNQTeams) minNQTeams = maxNQTeams;
    int kNQ = (maxNQTeams > 0 ? rnd.next(minNQTeams, maxNQTeams) : 0);

    vector<int> runners;
    int nextId = 1;

    // Qualified teams
    for (int q = 0; q < kQualified; ++q) {
        for (int c = 0; c < 6; ++c)
            runners.push_back(nextId);
        ++nextId;
    }

    // Non-qualified teams
    int remainingSlots = maxExtraSlots;
    for (int i = 0; i < kNQ; ++i) {
        int teamsLeft = kNQ - i;
        int maxCnt = min(5, remainingSlots - (teamsLeft - 1)); // leave at least 1 for each remaining
        int cnt = rnd.next(1, maxCnt);
        remainingSlots -= cnt;
        for (int c = 0; c < cnt; ++c)
            runners.push_back(nextId);
        ++nextId;
    }

    shuffle(runners.begin(), runners.end());
    return runners;
}

vector<int> buildMixedCase() {
    int kQ = rnd.next(2, 3); // 2-3 qualified teams
    return buildQualifiedWithNonQualified(kQ, true); // ensure some non-qualified teams exist
}

vector<int> buildSingleQualifiedCase() {
    int kQ = 1; // exactly one qualified team
    return buildQualifiedWithNonQualified(kQ, true); // force at least one non-qualified team, if possible
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 4);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        vector<int> runners;
        if (tc == 0) {
            runners = buildTieSample();
        } else if (tc == 1) {
            runners = buildAllQualifiedCase();
        } else if (tc == 2) {
            runners = buildMixedCase();
        } else {
            runners = buildSingleQualifiedCase();
        }
        int N = (int)runners.size();
        println(N);
        println(runners);
    }

    return 0;
}
