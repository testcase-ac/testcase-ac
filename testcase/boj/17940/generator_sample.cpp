#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int destination = rnd.next(1, n - 1);

    vector<int> company(n);
    int companyMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (companyMode == 0) {
            company[i] = i % 2;
        } else if (companyMode == 1) {
            company[i] = (i >= destination);
        } else if (companyMode == 2) {
            company[i] = rnd.next(0, 1);
        } else {
            company[i] = (i == 0 || i == destination) ? 0 : rnd.next(0, 1);
        }
    }

    vector<vector<int>> edge(n, vector<int>(n, 0));

    vector<int> path;
    path.push_back(0);
    vector<int> middle;
    for (int i = 1; i < n; ++i) {
        if (i != destination && rnd.next(0, 2) == 0) {
            middle.push_back(i);
        }
    }
    shuffle(middle.begin(), middle.end());
    int take = middle.empty() ? 0 : rnd.next(0, min<int>(middle.size(), 4));
    for (int i = 0; i < take; ++i) {
        path.push_back(middle[i]);
    }
    path.push_back(destination);

    int maxWeight = rnd.next(2, 30);
    for (int i = 1; i < (int)path.size(); ++i) {
        int u = path[i - 1];
        int v = path[i];
        edge[u][v] = edge[v][u] = rnd.next(1, maxWeight);
    }

    double density = rnd.next(0.0, 1.0);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (edge[i][j] == 0 && rnd.next() < density) {
                edge[i][j] = edge[j][i] = rnd.next(1, maxWeight);
            }
        }
    }

    if (rnd.next(0, 4) == 0) {
        int hub = rnd.next(0, n - 1);
        for (int v = 0; v < n; ++v) {
            if (v != hub && edge[hub][v] == 0 && rnd.next(0, 1)) {
                edge[hub][v] = edge[v][hub] = rnd.next(1, maxWeight);
            }
        }
    }

    println(n, destination);
    for (int c : company) {
        println(c);
    }
    for (int i = 0; i < n; ++i) {
        println(edge[i]);
    }

    return 0;
}
