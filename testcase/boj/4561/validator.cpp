#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

namespace {

const long double kPi = acosl(-1.0L);
const long double kRadius = 4000.0L;
const long double kInf = 1e100L;
const long double kTieEps = 1e-10L;

long double toRadians(int degrees) {
    return degrees * kPi / 180.0L;
}

long double distanceBetween(int latA, char nsA, int lonA, char ewA,
                           int latB, char nsB, int lonB, char ewB) {
    long double phiA = toRadians(latA) * (nsA == 'N' ? 1.0L : -1.0L);
    long double phiB = toRadians(latB) * (nsB == 'N' ? 1.0L : -1.0L);
    long double lambdaA = toRadians(lonA) * (ewA == 'E' ? 1.0L : -1.0L);
    long double lambdaB = toRadians(lonB) * (ewB == 'E' ? 1.0L : -1.0L);

    long double central = sinl(phiA) * sinl(phiB) +
                          cosl(phiA) * cosl(phiB) * cosl(lambdaA - lambdaB);
    central = max(-1.0L, min(1.0L, central));
    return kRadius * acosl(central);
}

void dfs(int v, const vector<vector<int>>& graph, vector<int>& seen) {
    seen[v] = 1;
    for (int next : graph[v]) {
        if (!seen[next]) {
            dfs(next, graph, seen);
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int x = inf.readInt(1, 99, "X");
        inf.readSpace();
        int y = inf.readInt(1, 99, "Y");
        inf.readEoln();

        map<string, int> cityIndex;
        vector<int> lat(x), lon(x);
        vector<char> ns(x), ew(x);

        for (int i = 0; i < x; ++i) {
            // CHECK: the statement gives no city-name length bound; cap at 100.
            string name = inf.readToken("[A-Z][a-z]{0,99}", "C");
            ensuref(cityIndex.emplace(name, i).second,
                    "duplicate city name at index %d: %s", i + 1, name.c_str());
            inf.readSpace();
            lat[i] = inf.readInt(0, 90, "LA");
            inf.readSpace();
            string nsToken = inf.readToken("N|S", "NS");
            ns[i] = nsToken[0];
            inf.readSpace();
            lon[i] = inf.readInt(0, 180, "LO");
            inf.readSpace();
            string ewToken = inf.readToken("E|W", "EW");
            ew[i] = ewToken[0];
            inf.readEoln();
        }

        vector<vector<int>> graph(x);
        vector<vector<long double>> dist(x, vector<long double>(x, kInf));
        for (int i = 0; i < x; ++i) {
            dist[i][i] = 0.0L;
        }

        set<pair<int, int>> edges;
        for (int i = 0; i < y; ++i) {
            string a = inf.readToken("[A-Z][a-z]{0,99}", "B");
            inf.readSpace();
            string b = inf.readToken("[A-Z][a-z]{0,99}", "C");
            inf.readEoln();

            auto itA = cityIndex.find(a);
            auto itB = cityIndex.find(b);
            ensuref(itA != cityIndex.end(), "unknown city in flight leg %d: %s",
                    i + 1, a.c_str());
            ensuref(itB != cityIndex.end(), "unknown city in flight leg %d: %s",
                    i + 1, b.c_str());
            int u = itA->second;
            int v = itB->second;
            ensuref(u != v, "flight leg %d connects a city to itself: %s",
                    i + 1, a.c_str());

            pair<int, int> edge = minmax(u, v);
            ensuref(edges.insert(edge).second,
                    "duplicate undirected flight leg at index %d: %s %s",
                    i + 1, a.c_str(), b.c_str());

            graph[u].push_back(v);
            graph[v].push_back(u);
            long double d = distanceBetween(lat[u], ns[u], lon[u], ew[u],
                                            lat[v], ns[v], lon[v], ew[v]);
            dist[u][v] = dist[v][u] = d;
        }

        vector<int> seen(x);
        dfs(0, graph, seen);
        for (int i = 0; i < x; ++i) {
            ensuref(seen[i], "airline network is not connected; city index %d is unreachable",
                    i + 1);
        }

        for (int k = 0; k < x; ++k) {
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < x; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        int maxCount = 0;
        long double best = -1.0L;
        for (int i = 0; i < x; ++i) {
            for (int j = i + 1; j < x; ++j) {
                if (dist[i][j] > best + kTieEps) {
                    best = dist[i][j];
                    maxCount = 1;
                } else if (fabsl(dist[i][j] - best) <= kTieEps) {
                    ++maxCount;
                }
            }
        }
        ensuref(maxCount == 1, "farthest city pair is not unique");
    }

    inf.readEof();
}
