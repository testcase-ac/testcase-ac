#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

int randomWeight(int mode) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.any(vector<int>{1, 2, 3, 10, 1000000});
    return rnd.next(1, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 18 : 10);
    int s = rnd.next(1, n);
    int t = rnd.next(1, n - 1);
    if (t >= s) ++t;

    vector<Edge> edges;
    int weightMode = rnd.next(0, 2);

    if (mode == 0) {
        edges.clear();
    } else if (mode == 1) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());
        for (int i = 0; i + 1 < n; ++i) {
            edges.push_back({order[i], order[i + 1], randomWeight(weightMode)});
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                edges.push_back({order[i], order[i], randomWeight(weightMode)});
            }
        }
    } else {
        int targetM = rnd.next(1, min(90, n * n + 15));
        for (int i = 0; i < targetM; ++i) {
            int from = rnd.next(1, n);
            int to = rnd.next(1, n);
            if (mode == 2 && from == to) {
                to = to % n + 1;
            }
            edges.push_back({from, to, randomWeight(weightMode)});
        }
    }

    if (mode >= 3 && rnd.next(0, 1) == 1) {
        int repeatedFrom = rnd.next(1, n);
        int repeatedTo = rnd.next(1, n);
        int repeats = rnd.next(2, 5);
        for (int i = 0; i < repeats; ++i) {
            edges.push_back({repeatedFrom, repeatedTo, randomWeight(weightMode)});
        }
    }

    if ((int)edges.size() > 3000) edges.resize(3000);

    int q = rnd.next(1, mode == 5 ? 45 : 20);
    vector<tuple<int, int, int, int, int, int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int queryMode = rnd.next(0, 5);
        int a1 = rnd.next(1, n), b1 = rnd.next(1, n);
        int a2 = rnd.next(1, n), b2 = rnd.next(1, n);

        if (queryMode == 0) {
            a1 = s;
            b2 = t;
            a2 = b1;
        } else if (queryMode == 1) {
            a1 = s;
            b1 = t;
        } else if (queryMode == 2) {
            a2 = s;
            b2 = t;
        } else if (queryMode == 3) {
            a1 = b1;
        } else if (queryMode == 4) {
            a1 = a2;
            b1 = b2;
        }

        int c1 = randomWeight(weightMode);
        int c2 = randomWeight(weightMode);
        queries.emplace_back(a1, b1, c1, a2, b2, c2);
    }

    println(n, (int)edges.size(), s, t);
    for (const Edge& edge : edges) {
        println(edge.from, edge.to, edge.weight);
    }
    println(q);
    for (const auto& query : queries) {
        println(get<0>(query), get<1>(query), get<2>(query), get<3>(query), get<4>(query), get<5>(query));
    }

    return 0;
}
