#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

using ll = long long;

static ll clampAi(ll value) {
    if (value < 1) return 1;
    if (value > 1000000000LL) return 1000000000LL;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 14));

    vector<int> parent(n + 1, 1);
    vector<ll> cost(n + 1, 0), dist(n + 1, 0);

    for (int v = 2; v <= n; ++v) {
        if (mode == 1) {
            parent[v] = 1;
        } else if (mode == 2) {
            parent[v] = v - 1;
        } else if (mode == 3) {
            parent[v] = v / 2;
        } else {
            parent[v] = rnd.next(1, v - 1);
        }

        if (rnd.next(0, 9) == 0) {
            cost[v] = rnd.any(vector<ll>{-1000000000LL, 1000000000LL});
        } else {
            cost[v] = rnd.next(-30, 60);
        }
        dist[v] = dist[parent[v]] + cost[v];
    }

    vector<ll> a(n + 1);
    for (int v = 1; v <= n; ++v) {
        if (v == 1 && rnd.next(0, 3) == 0) {
            a[v] = 1;
            continue;
        }

        int pattern = rnd.next(0, 4);
        if (pattern == 0) {
            a[v] = rnd.next(1, 120);
        } else if (pattern == 1) {
            a[v] = clampAi(llabs(dist[v]) + rnd.next(0, 8));
        } else if (pattern == 2) {
            a[v] = clampAi(dist[v] + rnd.next(-5, 5));
        } else {
            a[v] = rnd.any(vector<ll>{1LL, 1000000000LL});
        }
    }

    vector<int> label(n + 1);
    label[1] = 1;
    vector<int> nonRoot;
    for (int v = 2; v <= n; ++v) {
        nonRoot.push_back(v);
    }
    shuffle(nonRoot.begin(), nonRoot.end());
    for (int i = 0; i < int(nonRoot.size()); ++i) {
        label[nonRoot[i]] = i + 2;
    }

    vector<ll> labeledA(n + 1);
    vector<int> labeledParent(n + 1);
    vector<ll> labeledCost(n + 1);
    for (int v = 1; v <= n; ++v) {
        labeledA[label[v]] = a[v];
        if (v != 1) {
            labeledParent[label[v]] = label[parent[v]];
            labeledCost[label[v]] = cost[v];
        }
    }

    println(n);
    vector<ll> outputA;
    for (int i = 1; i <= n; ++i) {
        outputA.push_back(labeledA[i]);
    }
    println(outputA);
    for (int i = 2; i <= n; ++i) {
        println(labeledParent[i], labeledCost[i]);
    }

    return 0;
}
