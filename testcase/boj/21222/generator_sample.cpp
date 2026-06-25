#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    long long weight;
};

string wordName(int index) {
    string s;
    do {
        s.push_back(char('a' + index % 26));
        index /= 26;
    } while (index > 0);
    reverse(s.begin(), s.end());
    return s;
}

void addEdge(vector<Edge>& edges, int from, int to, long long weight) {
    if (from != to) edges.push_back({from, to, weight});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 14 : 9);
    vector<string> words;
    for (int i = 0; i < n; ++i) words.push_back(wordName(i));

    vector<Edge> edges;
    if (mode == 0) {
        for (int i = 0; i + 1 < n; ++i) addEdge(edges, i, i + 1, rnd.next(1, 20));
    } else if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) addEdge(edges, i + 1, i, rnd.next(1, 30));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) addEdge(edges, i, (i + 1) % n, rnd.next(1, 25));
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i + 1 < split; ++i) addEdge(edges, i, i + 1, rnd.next(1, 15));
        if (split == 1) addEdge(edges, 0, split, rnd.next(1, 15));
        for (int i = split; i + 1 < n; ++i) addEdge(edges, i, i + 1, rnd.next(1, 15));
        if (split + 1 == n) addEdge(edges, split, 0, rnd.next(1, 15));
    } else if (mode == 4) {
        for (int i = 0; i + 1 < n; ++i) {
            long long heavy = rnd.next(30, 100);
            addEdge(edges, i, i + 1, heavy);
            addEdge(edges, i, i + 1, rnd.next(1, (int)heavy - 1));
        }
    } else {
        for (int i = 0; i + 1 < n; ++i) addEdge(edges, i, i + 1, rnd.next(1, 1000));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next(0, 99) < 28) {
                    long long w = rnd.next(1, 1000000000);
                    addEdge(edges, i, j, w);
                }
            }
        }
    }

    while ((int)edges.size() < n - 1) {
        int from = rnd.next(0, n - 1);
        int to = rnd.next(0, n - 1);
        if (from != to) addEdge(edges, from, to, rnd.next(1, 50));
    }
    shuffle(edges.begin(), edges.end());

    int m = (int)edges.size();
    int maxQueries = min(20, n * (n - 1));
    int q = rnd.next(min(3, maxQueries), maxQueries);
    vector<pair<int, int>> queries;
    queries.push_back({0, n - 1});
    queries.push_back({n - 1, 0});
    while ((int)queries.size() < q) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        if (a != b) queries.push_back({a, b});
    }
    shuffle(queries.begin(), queries.end());

    println(n, m);
    for (const Edge& edge : edges) {
        cout << words[edge.from] << ' ' << words[edge.to] << ' '
             << edge.weight << '\n';
    }
    println((int)queries.size());
    for (const auto& query : queries) {
        cout << words[query.first] << ' ' << words[query.second] << '\n';
    }

    return 0;
}
