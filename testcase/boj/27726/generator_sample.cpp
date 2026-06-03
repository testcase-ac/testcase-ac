#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.push_back({a, b});
}

void addChain(vector<Edge>& edges, const vector<int>& nodes) {
    for (int i = 1; i < (int)nodes.size(); ++i) {
        addEdge(edges, nodes[i - 1], nodes[i]);
    }
}

void addRandomExtras(vector<Edge>& edges, int n, int count) {
    for (int i = 0; i < count; ++i) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        addEdge(edges, a, b);
    }
}

void ensureNonEmpty(vector<Edge>& edges, int n) {
    if (edges.empty()) {
        addEdge(edges, 1, n == 1 ? 1 : 2);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 3 ? rnd.next(3, 14) : rnd.next(2, 14);
    vector<Edge> studies[3];

    if (mode == 0) {
        int groupSize = rnd.next(2, min(n, 6));
        vector<int> group;
        for (int i = 1; i <= groupSize; ++i) group.push_back(i);
        shuffle(group.begin(), group.end());

        for (int study = 0; study < 3; ++study) {
            addChain(studies[study], group);
            addRandomExtras(studies[study], n, rnd.next(0, 3));
        }
    } else if (mode == 1) {
        for (int study = 0; study < 3; ++study) {
            vector<int> perm;
            for (int i = 1; i <= n; ++i) perm.push_back(i);
            shuffle(perm.begin(), perm.end());

            int pos = 0;
            while (pos < n) {
                int remaining = n - pos;
                int take = min(remaining, rnd.next(2, 4));
                if (remaining == 1) {
                    addEdge(studies[study], perm[pos], perm[rnd.next(0, pos - 1)]);
                    ++pos;
                } else {
                    vector<int> block(perm.begin() + pos, perm.begin() + pos + take);
                    addChain(studies[study], block);
                    pos += take;
                }
            }
        }
    } else if (mode == 2) {
        for (int study = 0; study < 3; ++study) {
            int center = rnd.next(1, n);
            int spokes = rnd.next(1, n - 1);
            vector<int> nodes;
            for (int i = 1; i <= n; ++i) {
                if (i != center) nodes.push_back(i);
            }
            shuffle(nodes.begin(), nodes.end());
            for (int i = 0; i < spokes; ++i) addEdge(studies[study], center, nodes[i]);
            addRandomExtras(studies[study], n, rnd.next(0, 2));
        }
    } else if (mode == 3) {
        int bridge = rnd.next(2, n - 1);
        for (int i = 1; i < bridge; ++i) addEdge(studies[0], i, i + 1);
        for (int i = bridge; i < n; ++i) addEdge(studies[1], i, i + 1);
        for (int i = 1; i <= n; i += 2) {
            if (i + 1 <= n) addEdge(studies[2], i, i + 1);
        }
        addRandomExtras(studies[0], n, rnd.next(1, 3));
        addRandomExtras(studies[1], n, rnd.next(1, 3));
        addRandomExtras(studies[2], n, rnd.next(1, 3));
    } else {
        int baseA = rnd.next(1, n);
        int baseB = rnd.next(1, n - 1);
        if (baseB >= baseA) ++baseB;
        for (int study = 0; study < 3; ++study) {
            int duplicates = rnd.next(1, 4);
            for (int i = 0; i < duplicates; ++i) addEdge(studies[study], baseA, baseB);
            addRandomExtras(studies[study], n, rnd.next(0, 4));
        }
    }

    for (int study = 0; study < 3; ++study) {
        ensureNonEmpty(studies[study], n);
        shuffle(studies[study].begin(), studies[study].end());
    }

    println(n);
    println((int)studies[0].size(), (int)studies[1].size(), (int)studies[2].size());
    for (int study = 0; study < 3; ++study) {
        for (const auto& [a, b] : studies[study]) {
            println(a, b);
        }
    }

    return 0;
}
