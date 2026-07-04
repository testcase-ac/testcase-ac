#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addPath(vector<Edge>& edges, int first, int last) {
    for (int v = first; v < last; ++v) {
        edges.push_back({v, v + 1});
    }
}

vector<int> relabelNodes(int n, vector<Edge>& edges, vector<int> teams) {
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    for (auto& [a, b] : edges) {
        a = label[a];
        b = label[b];
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
    }
    for (int& city : teams) {
        city = label[city];
    }

    shuffle(edges.begin(), edges.end());
    shuffle(teams.begin(), teams.end());
    return teams;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<Edge> edges;
    vector<int> teams;

    if (mode == 0) {
        n = 1;
        teams = {1};
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        addPath(edges, 1, n);
        int m = rnd.next(1, min(n, 6));
        vector<int> cities(n);
        iota(cities.begin(), cities.end(), 1);
        shuffle(cities.begin(), cities.end());
        teams.assign(cities.begin(), cities.begin() + m);
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        for (int city = 2; city <= n; ++city) {
            edges.push_back({1, city});
        }
        int m = rnd.next(2, min(n - 1, 6));
        vector<int> leaves;
        for (int city = 2; city <= n; ++city) {
            leaves.push_back(city);
        }
        shuffle(leaves.begin(), leaves.end());
        teams.assign(leaves.begin(), leaves.begin() + m);
    } else if (mode == 3) {
        int branches = rnd.next(2, 5);
        int depth = rnd.next(1, 3);
        n = 1 + branches * depth;
        for (int branch = 0; branch < branches; ++branch) {
            int prev = 1;
            for (int d = 1; d <= depth; ++d) {
                int city = 2 + branch * depth + (d - 1);
                edges.push_back({prev, city});
                prev = city;
            }
            teams.push_back(prev);
        }
    } else if (mode == 4) {
        int left = rnd.next(1, 4);
        int right = rnd.next(1, 4);
        int tail = rnd.next(1, 3);
        n = 1 + left + right + tail;
        addPath(edges, 1, 1 + left);
        edges.push_back({1, 2 + left});
        addPath(edges, 2 + left, 1 + left + right);
        edges.push_back({1, 2 + left + right});
        addPath(edges, 2 + left + right, n);
        teams = {1 + left, 1 + left + right, n};
    } else {
        n = rnd.next(6, 15);
        for (int city = 2; city <= n; ++city) {
            int parent = rnd.next(1, city - 1);
            edges.push_back({parent, city});
        }
        int m = rnd.next(2, min(n, 7));
        vector<int> cities(n);
        iota(cities.begin(), cities.end(), 1);
        shuffle(cities.begin(), cities.end());
        teams.assign(cities.begin(), cities.begin() + m);
    }

    teams = relabelNodes(n, edges, teams);

    println(n, static_cast<int>(teams.size()));
    for (auto [a, b] : edges) {
        println(a, b);
    }
    println(teams);

    return 0;
}
