#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 15);
    int k = rnd.next(1, n);
    int root = rnd.next(1, n);

    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    nodes.erase(find(nodes.begin(), nodes.end(), root));
    shuffle(nodes.begin(), nodes.end());

    vector<int> infected;
    infected.push_back(root);
    for (int i = 0; i < k - 1; ++i) {
        infected.push_back(nodes[i]);
    }

    vector<int> isInfected(n + 1, 0);
    for (int x : infected) {
        isInfected[x] = 1;
    }

    vector<int> outside;
    for (int x = 1; x <= n; ++x) {
        if (!isInfected[x]) {
            outside.push_back(x);
        }
    }

    vector<tuple<int, int, int>> logs;
    int nextTime = 1;

    vector<int> reached;
    reached.push_back(root);
    vector<int> pending = infected;
    pending.erase(pending.begin());
    shuffle(pending.begin(), pending.end());

    for (int x : pending) {
        int parent = rnd.any(reached);
        logs.emplace_back(nextTime++, parent, x);
        reached.push_back(x);
    }

    int extraLimit = min(35, n * 3);
    int extraLogs = rnd.next(logs.empty() ? 1 : 0, extraLimit);
    for (int i = 0; i < extraLogs; ++i) {
        int a, b;
        if (!outside.empty() && rnd.next(0, 2) == 0) {
            a = rnd.any(outside);
            b = rnd.next(1, n);
            while (b == a) {
                b = rnd.next(1, n);
            }
        } else if (infected.size() >= 2) {
            vector<int> nonRootInfected;
            for (int x : infected) {
                if (x != root) {
                    nonRootInfected.push_back(x);
                }
            }
            b = rnd.any(nonRootInfected);
            a = rnd.any(infected);
            while (a == b) {
                a = rnd.any(infected);
            }
        } else {
            a = rnd.any(outside);
            b = root;
        }
        logs.emplace_back(nextTime++, a, b);
    }

    shuffle(infected.begin(), infected.end());
    shuffle(logs.begin(), logs.end());

    println(n, int(logs.size()), k);
    println(infected);
    for (const auto& [t, a, b] : logs) {
        println(t, a, b);
    }

    return 0;
}
