#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Fraction {
    long long num = 0;
    long long den = 1;
};

struct Edge {
    int a;
    int b;
    int va;
    int vb;
};

Fraction normalize(long long num, long long den) {
    long long g = gcd(num, den);
    return {num / g, den / g};
}

bool sameValue(long long lhsNum, long long lhsDen, long long rhsNum, long long rhsDen) {
    return (__int128)lhsNum * rhsDen == (__int128)rhsNum * lhsDen;
}

bool lessValue(long long lhsNum, long long lhsDen, long long rhsNum, long long rhsDen) {
    return (__int128)lhsNum * rhsDen < (__int128)rhsNum * lhsDen;
}

bool hasUniqueBest(const vector<Edge>& edges, int currencyCount, int requestedId, int requestedValue) {
    vector<vector<pair<int, Fraction>>> graph(currencyCount);
    for (const Edge& edge : edges) {
        graph[edge.a].push_back({edge.b, normalize(edge.vb, edge.va)});
        graph[edge.b].push_back({edge.a, normalize(edge.va, edge.vb)});
    }

    vector<int> seen(currencyCount, false);
    vector<Fraction> rate(currencyCount);
    vector<int> queue;
    seen[requestedId] = true;
    rate[requestedId] = {1, 1};
    queue.push_back(requestedId);

    for (int head = 0; head < (int)queue.size(); ++head) {
        int cur = queue[head];
        for (const auto& [next, edgeRate] : graph[cur]) {
            if (seen[next]) continue;
            seen[next] = true;
            rate[next] = normalize(rate[cur].num * edgeRate.num, rate[cur].den * edgeRate.den);
            queue.push_back(next);
        }
    }

    bool hasBest = false;
    bool tiedBest = false;
    long long bestNum = 0;
    long long bestDen = 1;
    for (int id = 0; id < currencyCount; ++id) {
        if (id == requestedId || !seen[id]) continue;
        long long needed = (requestedValue * rate[id].num + rate[id].den - 1) / rate[id].den;
        if (needed > 100000) continue;

        long long excessNum = needed * rate[id].den - requestedValue * rate[id].num;
        long long excessDen = rate[id].num;
        if (!hasBest || lessValue(excessNum, excessDen, bestNum, bestDen)) {
            hasBest = true;
            tiedBest = false;
            bestNum = excessNum;
            bestDen = excessDen;
        } else if (sameValue(excessNum, excessDen, bestNum, bestDen)) {
            tiedBest = true;
        }
    }

    return hasBest && !tiedBest;
}

vector<Edge> makeCase(int currencyCount, int connectedCount) {
    vector<int> connected;
    for (int i = 0; i < connectedCount; ++i) connected.push_back(i);
    shuffle(connected.begin() + 1, connected.end());

    vector<Edge> edges;
    for (int i = 1; i < connectedCount; ++i) {
        int parent = connected[rnd.next(0, i - 1)];
        int child = connected[i];
        edges.push_back({parent, child, rnd.next(1, 30), rnd.next(1, 30)});
    }

    if (connectedCount < currencyCount) {
        vector<int> extra;
        for (int i = connectedCount; i < currencyCount; ++i) extra.push_back(i);
        shuffle(extra.begin(), extra.end());
        int extraEdges = rnd.next(0, (int)extra.size() - 1);
        for (int i = 1; i <= extraEdges; ++i) {
            int parent = extra[rnd.next(0, i - 1)];
            int child = extra[i];
            edges.push_back({parent, child, rnd.next(1, 30), rnd.next(1, 30)});
        }
    }

    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> names = {"A", "B", "C", "D", "E", "F", "USD", "Yen"};
    int testCount = rnd.next(2, 4);
    for (int tc = 0; tc < testCount; ++tc) {
        int currencyCount = rnd.next(2, 8);
        int connectedCount = rnd.next(2, currencyCount);
        int requestedId = 0;
        int requestedValue = rnd.next(1, 100000);

        vector<Edge> edges;
        for (int attempt = 0; attempt < 10000; ++attempt) {
            requestedValue = rnd.next(1, 100000);
            edges = makeCase(currencyCount, connectedCount);
            if (hasUniqueBest(edges, currencyCount, requestedId, requestedValue)) break;
        }

        println((int)edges.size());
        for (const Edge& edge : edges) {
            println(edge.va, names[edge.a], "=", edge.vb, names[edge.b]);
        }
        println(requestedValue, names[requestedId]);
    }
    println(0);
}
