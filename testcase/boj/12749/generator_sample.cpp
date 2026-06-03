#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<vector<int>> bosses(n + 1);
    int root = rnd.next(1, n);

    vector<int> order;
    for (int i = 1; i <= n; ++i) {
        if (i != root) {
            order.push_back(i);
        }
    }
    shuffle(order.begin(), order.end());

    auto addBoss = [&](int employee, int boss) {
        if (employee == boss) {
            return;
        }
        if (find(bosses[employee].begin(), bosses[employee].end(), boss) == bosses[employee].end()) {
            bosses[employee].push_back(boss);
        }
    };

    vector<int> available = {root};
    for (int idx = 0; idx < (int)order.size(); ++idx) {
        int employee = order[idx];
        int parent = root;

        if (mode == 0) {
            parent = idx == 0 ? root : order[idx - 1];
        } else if (mode == 1) {
            parent = root;
        } else if (mode == 2) {
            parent = available[idx / 2];
        } else if (mode == 3) {
            parent = available[rnd.wnext((int)available.size(), -2)];
        } else {
            parent = rnd.any(available);
        }

        addBoss(employee, parent);
        available.push_back(employee);
    }

    int extraBudget = rnd.next(0, min(60, n * (n - 1) / 3));
    if (mode == 4) {
        extraBudget = rnd.next(n, min(120, n * (n - 1)));
    }

    vector<pair<int, int>> candidates;
    for (int employee = 1; employee <= n; ++employee) {
        for (int boss = 1; boss <= n; ++boss) {
            if (employee != boss) {
                candidates.push_back({employee, boss});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto [employee, boss] : candidates) {
        if (extraBudget == 0) {
            break;
        }
        int before = (int)bosses[employee].size();
        addBoss(employee, boss);
        if ((int)bosses[employee].size() != before) {
            --extraBudget;
        }
    }

    if (rnd.next(0, 1)) {
        for (int employee = 1; employee <= n; ++employee) {
            shuffle(bosses[employee].begin(), bosses[employee].end());
        }
    }

    println(n);
    for (int employee = 1; employee <= n; ++employee) {
        printf("%d", (int)bosses[employee].size());
        for (int boss : bosses[employee]) {
            printf(" %d", boss);
        }
        printf("\n");
    }

    return 0;
}
