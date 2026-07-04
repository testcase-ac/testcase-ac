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

vector<int> labels(int count) {
    vector<int> values;
    for (int i = 1; i <= 100; ++i) values.push_back(i);
    shuffle(values.begin(), values.end());
    values.resize(count);
    sort(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Edge> edges;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int vertices = rnd.next(2, 18);
        vector<int> v = labels(vertices);
        shuffle(v.begin(), v.end());
        for (int i = 0; i + 1 < vertices; ++i) addEdge(edges, v[i], v[i + 1]);
    } else if (mode == 1) {
        int vertices = rnd.next(3, 14);
        vector<int> v = labels(vertices);
        shuffle(v.begin(), v.end());
        for (int i = 0; i < vertices; ++i) addEdge(edges, v[i], v[(i + 1) % vertices]);
        if (rnd.next(0, 1)) addEdge(edges, v[0], v[vertices / 2]);
    } else if (mode == 2) {
        int vertices = rnd.next(5, 20);
        vector<int> v = labels(vertices);
        int center = v[0];
        for (int i = 1; i < vertices; ++i) addEdge(edges, center, v[i]);
        int extra = rnd.next(1, vertices / 2);
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(1, vertices - 1);
            int b = rnd.next(1, vertices - 1);
            if (a == b) b = (b % (vertices - 1)) + 1;
            addEdge(edges, v[a], v[b]);
        }
    } else if (mode == 3) {
        int vertices = rnd.next(5, 12);
        vector<int> v = labels(vertices);
        for (int i = 0; i < vertices; ++i) {
            for (int j = i + 1; j < vertices; ++j) {
                if (rnd.next(0, 99) < 45) addEdge(edges, v[i], v[j]);
            }
        }
        if (edges.empty()) addEdge(edges, v[0], v[1]);
    } else if (mode == 4) {
        int vertices = rnd.next(8, 24);
        vector<int> v = labels(vertices);
        shuffle(v.begin(), v.end());
        int pos = 0;
        while (pos < vertices - 1) {
            int len = rnd.next(2, min(6, vertices - pos));
            for (int i = 0; i + 1 < len; ++i) addEdge(edges, v[pos + i], v[pos + i + 1]);
            pos += len;
        }
    } else {
        int vertices = rnd.next(2, 10);
        vector<int> v = labels(vertices);
        for (int i = 0; i + 1 < vertices; ++i) addEdge(edges, v[i], v[i + 1]);
        int repeats = rnd.next(1, 100 - (int)edges.size());
        for (int i = 0; i < repeats; ++i) edges.push_back(rnd.any(edges));
    }

    shuffle(edges.begin(), edges.end());
    if ((int)edges.size() > 100) edges.resize(100);

    println((int)edges.size());
    for (auto [a, b] : edges) println(a, b);

    return 0;
}
