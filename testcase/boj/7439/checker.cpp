#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <set>
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

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

struct Point {
    int x;
    int y;
};

struct InputData {
    int n;
    vector<Point> towns;
    set<pair<int, int>> existing;
};

struct Answer {
    double length;
    int edges;
};

InputData readInput() {
    InputData data;
    data.n = inf.readInt();
    data.towns.assign(data.n + 1, {});
    for (int i = 1; i <= data.n; ++i) {
        data.towns[i].x = inf.readInt();
        data.towns[i].y = inf.readInt();
    }

    int m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        data.existing.insert(minmax(a, b));
    }
    return data;
}

double distanceBetween(const Point& a, const Point& b) {
    long long dx = (long long)a.x - b.x;
    long long dy = (long long)a.y - b.y;
    return sqrt((double)(dx * dx + dy * dy));
}

Answer readAnswer(InStream& stream, const InputData& data) {
    DSU dsu(data.n);
    for (const auto& edge : data.existing) {
        dsu.unite(edge.first, edge.second);
    }

    set<pair<int, int>> built;
    double total = 0.0;
    int edgeCount = 0;

    while (!stream.seekEof()) {
        int a = stream.readInt(1, data.n, "new highway endpoint");
        int b = stream.readInt(1, data.n, "new highway endpoint");
        if (a == b) {
            stream.quitf(_wa, "new highway connects town %d to itself", a);
        }

        pair<int, int> edge = minmax(a, b);
        if (data.existing.count(edge)) {
            stream.quitf(_wa, "highway %d %d already exists", edge.first, edge.second);
        }
        if (!built.insert(edge).second) {
            stream.quitf(_wa, "duplicate new highway %d %d", edge.first, edge.second);
        }

        total += distanceBetween(data.towns[a], data.towns[b]);
        dsu.unite(a, b);
        ++edgeCount;
    }

    int root = dsu.find(1);
    for (int i = 2; i <= data.n; ++i) {
        if (dsu.find(i) != root) {
            stream.quitf(_wa, "output highways do not connect town %d to town 1", i);
        }
    }

    return {total, edgeCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    InputData data = readInput();
    Answer jury = readAnswer(ans, data);
    Answer participant = readAnswer(ouf, data);

    const double EPS = 1e-7;
    if (participant.length > jury.length + EPS) {
        quitf(_wa,
              "participant highways are longer than jury: participant=%.12f jury=%.12f",
              participant.length,
              jury.length);
    }
    if (participant.length + EPS < jury.length) {
        quitf(_fail,
              "participant found shorter highways: participant=%.12f jury=%.12f",
              participant.length,
              jury.length);
    }

    quitf(_ok, "answer length %.12f with %d new highways", participant.length, participant.edges);
}
