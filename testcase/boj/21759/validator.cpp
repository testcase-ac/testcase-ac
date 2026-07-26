#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    vector<long long> skill(n + 1);
    vector<vector<int>> children(n + 1);
    for (int i = 1; i <= n; ++i) {
        skill[i] = inf.readLong(-1000000000LL, 1000000000LL, "skill_i");
        inf.readSpace();
        int parent = inf.readInt(i == 1 ? -1 : 1, i == 1 ? -1 : i - 1, "parent_i");
        inf.readEoln();
        if (i > 1) children[parent].push_back(i);
    }
    inf.readEof();

    vector<long long> bestTeam(n + 1);
    vector<char> hasTeamDisjointFromBest(n + 1);
    bool hasTwoTeams = false;
    for (int x = n; x >= 1; --x) {
        bestTeam[x] = skill[x];
        hasTwoTeams = hasTwoTeams || children[x].size() >= 2;
        for (int child : children[x]) {
            if (bestTeam[child] > 0) {
                bestTeam[x] += bestTeam[child];
                hasTeamDisjointFromBest[x] =
                    hasTeamDisjointFromBest[x] || hasTeamDisjointFromBest[child];
            } else {
                hasTeamDisjointFromBest[x] = true;
            }
        }
        hasTwoTeams = hasTwoTeams || hasTeamDisjointFromBest[x];
    }
    ensuref(hasTwoTeams, "the organization must allow two disjoint optimal teams");
}
