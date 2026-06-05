#include "testlib.h"

#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> leader;

    explicit DSU(int n) : parent(n), leader(n) {
        iota(parent.begin(), parent.end(), 0);
        iota(leader.begin(), leader.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int currentLeader(int x) {
        return leader[find(x)];
    }

    void absorb(int winnerSide, int loserSide) {
        int wr = find(winnerSide);
        int lr = find(loserSide);
        if (wr != lr) {
            parent[lr] = wr;
        }
    }

    void replaceLeader(int x) {
        leader[find(x)] = x;
    }
};

vector<vector<int>> components(DSU& dsu, int n) {
    vector<vector<int>> groups(n);
    for (int i = 0; i < n; ++i) {
        groups[dsu.find(i)].push_back(i);
    }

    vector<vector<int>> result;
    for (auto& group : groups) {
        if (!group.empty()) {
            result.push_back(group);
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int m = rnd.next(1, 30);

    vector<string> names;
    for (int i = 0; i < n; ++i) {
        names.push_back("Kingdom of " + string(1, char('A' + i)));
    }

    DSU dsu(n);
    vector<string> wars;
    for (int step = 0; step < m; ++step) {
        vector<vector<int>> groups = components(dsu, n);
        vector<int> mergeable;
        vector<int> rebellious;

        for (int i = 0; i < (int)groups.size(); ++i) {
            if ((int)groups[i].size() >= 2) {
                rebellious.push_back(i);
            }
        }
        if ((int)groups.size() >= 2) {
            mergeable.resize(groups.size());
            iota(mergeable.begin(), mergeable.end(), 0);
        }

        bool doRebellion = !rebellious.empty() && (mergeable.empty() || rnd.next(0, 99) < 35);
        int first;
        int second;
        int winnerField;

        if (doRebellion) {
            int groupIndex = rnd.any(rebellious);
            vector<int> group = groups[groupIndex];
            int leader = dsu.currentLeader(group[0]);
            vector<int> vassals;
            for (int x : group) {
                if (x != leader) {
                    vassals.push_back(x);
                }
            }

            first = leader;
            second = rnd.any(vassals);
            if (rnd.next(0, 1)) {
                swap(first, second);
            }

            winnerField = rnd.next(1, 2);
            int winner = winnerField == 1 ? first : second;
            if (winner != leader) {
                dsu.replaceLeader(winner);
            }
        } else {
            shuffle(mergeable.begin(), mergeable.end());
            int leftGroup = mergeable[0];
            int rightGroup = mergeable[1];

            first = dsu.currentLeader(groups[leftGroup][0]);
            second = dsu.currentLeader(groups[rightGroup][0]);
            if (rnd.next(0, 1)) {
                swap(first, second);
            }

            winnerField = rnd.next(1, 2);
            int winner = winnerField == 1 ? first : second;
            int loser = winnerField == 1 ? second : first;
            dsu.absorb(winner, loser);
        }

        wars.push_back(names[first] + "," + names[second] + "," + to_string(winnerField));
    }

    println(n, m);
    for (const string& name : names) {
        println(name);
    }
    for (const string& war : wars) {
        println(war);
    }

    return 0;
}
