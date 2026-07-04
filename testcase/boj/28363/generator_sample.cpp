#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class ProposalState {
public:
    explicit ProposalState(int n) : parent_(n + 1), size_(n + 1, 1), enemies_(n + 1) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    void addDistrust(int a, int b) {
        enemies_[a].insert(b);
        enemies_[b].insert(a);
    }

    bool canMerge(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) {
            return false;
        }
        if (enemies_[ra].size() > enemies_[rb].size()) {
            swap(ra, rb);
        }
        for (int enemy : enemies_[ra]) {
            if (find(enemy) == rb) {
                return false;
            }
        }
        return true;
    }

    void merge(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) {
            return;
        }
        if (size_[ra] < size_[rb]) {
            swap(ra, rb);
        }

        parent_[rb] = ra;
        size_[ra] += size_[rb];

        vector<int> oldEnemies(enemies_[rb].begin(), enemies_[rb].end());
        for (int enemy : oldEnemies) {
            int re = find(enemy);
            enemies_[re].erase(rb);
            if (re != ra) {
                enemies_[re].insert(ra);
                enemies_[ra].insert(re);
            }
        }
        enemies_[rb].clear();
    }

private:
    vector<int> parent_;
    vector<int> size_;
    vector<set<int>> enemies_;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 18 : 12);

    vector<pair<int, int>> allPairs;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            allPairs.emplace_back(i, j);
        }
    }
    shuffle(allPairs.begin(), allPairs.end());

    int maxPairs = min<int>(allPairs.size(), mode <= 1 ? n : 2 * n);
    int m = rnd.next(1, maxPairs);
    vector<pair<int, int>> distrust(allPairs.begin(), allPairs.begin() + m);

    ProposalState state(n);
    for (auto [u, v] : distrust) {
        state.addDistrust(u, v);
    }

    int qLimit = min(35, n * (n - 1));
    int qTarget = rnd.next(1, qLimit);
    vector<pair<int, int>> proposals;
    for (int step = 0; step < qTarget; ++step) {
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (state.find(a) != state.find(b)) {
                    candidates.emplace_back(a, b);
                }
            }
        }
        if (candidates.empty()) {
            break;
        }

        vector<pair<int, int>> chosenPool;
        bool preferRefuse = (mode == 1 || mode == 3 || (mode == 4 && step % 3 == 0));
        for (auto [a, b] : candidates) {
            if (state.canMerge(a, b) != preferRefuse) {
                chosenPool.emplace_back(a, b);
            }
        }
        if (chosenPool.empty()) {
            chosenPool = candidates;
        }

        auto proposal = rnd.any(chosenPool);
        if (rnd.next(0, 1)) {
            swap(proposal.first, proposal.second);
        }
        proposals.push_back(proposal);

        if (state.canMerge(proposal.first, proposal.second)) {
            state.merge(proposal.first, proposal.second);
        }
    }

    println(n, m, static_cast<int>(proposals.size()));
    for (auto [u, v] : distrust) {
        println(u, v);
    }
    for (auto [a, b] : proposals) {
        println(a, b);
    }

    return 0;
}
