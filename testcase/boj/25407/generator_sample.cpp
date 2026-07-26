#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(4, 12);
    int treeMode = rnd.next(0, 2);
    int weightMode = rnd.next(0, 3);
    vector<int> degree(n + 1);
    vector<int> ancestors = {1};

    println(n);
    for (int node = 2; node <= n; ++node) {
        int parent;
        if (treeMode == 0)
            parent = 1;
        else if (treeMode == 1)
            parent = node == n ? 1 : node - 1;
        else if (node == 2 || (node == n && degree[1] == 1))
            parent = 1;
        else
            parent = ancestors[rnd.next(0, static_cast<int>(ancestors.size()) - 1)];

        while (ancestors.back() != parent)
            ancestors.pop_back();
        ancestors.push_back(node);
        ++degree[parent];
        ++degree[node];

        long long weight = weightMode == 0 ? 0LL
                         : weightMode == 1 ? 1000000000000LL
                                           : rnd.next(0, 20);
        println(parent, weight);
    }

    vector<long long> ringWeights;
    for (int node = 1; node <= n; ++node) {
        if (degree[node] != 1)
            continue;
        ringWeights.push_back(weightMode == 0 ? 0LL
                              : weightMode == 1 ? 1000000000000LL
                              : weightMode == 2 ? rnd.next(0, 20)
                                                : rnd.next(0, 1)
                                                      ? 0LL
                                                      : 1000000000000LL);
    }
    println(ringWeights);

    int q = rnd.next(1, 20);
    println(q);
    for (int i = 0; i < q; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u)
            ++v;
        println(u, v);
    }
}
