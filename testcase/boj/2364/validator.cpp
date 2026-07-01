#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 200, "M");
    inf.readEoln();

    // CHECK: The Korean statement allows N from 2, while the English variant
    // says 3. Use the primary Korean bound; polygonal region checks below reject
    // structurally impossible two-town instances.
    int n = inf.readInt(2, 250, "N");
    inf.readEoln();

    int l = inf.readInt(1, min(30, n), "L");
    inf.readEoln();

    int previousMember = 0;
    for (int i = 1; i <= l; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int member = inf.readInt(1, n, "member");
        ensuref(previousMember < member,
                "member towns must be distinct and increasing: previous=%d current=%d",
                previousMember,
                member);
        previousMember = member;
    }
    inf.readEoln();

    DSU dsu(n);
    vector<int> degree(n + 1, 0);
    set<pair<int, int>> walls;
    vector<pair<int, int>> borderEdges;
    long long totalBorderEdges = 0;

    for (int region = 1; region <= m; ++region) {
        int borderSize = inf.readInt(3, n, "I");
        inf.readEoln();

        vector<int> towns(borderSize);
        vector<bool> seenTown(n + 1, false);
        for (int i = 0; i < borderSize; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            towns[i] = inf.readInt(1, n, "town");
            ensuref(!seenTown[towns[i]],
                    "region %d repeats town %d on its border",
                    region,
                    towns[i]);
            seenTown[towns[i]] = true;
        }
        inf.readEoln();

        totalBorderEdges += borderSize;
        for (int i = 0; i < borderSize; ++i) {
            int a = towns[i];
            int b = towns[(i + 1) % borderSize];
            auto edge = minmax(a, b);
            walls.insert(edge);
            borderEdges.push_back(edge);
            dsu.unite(a, b);
        }
    }

    for (const auto& edge : walls) {
        ++degree[edge.first];
        ++degree[edge.second];
    }

    for (int town = 1; town <= n; ++town) {
        ensuref(degree[town] > 0, "town %d is isolated", town);
        ensuref(dsu.find(town) == dsu.find(1), "wall graph is disconnected at town %d", town);
    }

    // CHECK: Without coordinates the validator cannot prove geometric
    // non-crossing or clockwise orientation. It validates the combinatorial
    // region listing implied by all regions being present.
    ensuref((int)walls.size() == m + n - 2,
            "Euler relation failed: regions=%d towns=%d unique walls=%d",
            m,
            n,
            (int)walls.size());
    ensuref(totalBorderEdges == 2LL * (int)walls.size(),
            "total border edge incidences must equal twice the number of walls");

    sort(borderEdges.begin(), borderEdges.end());
    for (int i = 0; i < (int)borderEdges.size();) {
        int j = i + 1;
        while (j < (int)borderEdges.size() && borderEdges[j] == borderEdges[i]) {
            ++j;
        }
        ensuref(j - i == 2,
                "wall (%d, %d) appears on %d region borders, expected 2",
                borderEdges[i].first,
                borderEdges[i].second,
                j - i);
        i = j;
    }

    inf.readEof();
}
