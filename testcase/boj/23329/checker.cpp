#include "testlib.h"

#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
    long long c;
    int dir;
};

struct Answer {
    bool impossible;
    long long claimedCost;
    long long actualCost;
};

int n, s, e;
vector<Point> points;
vector<map<int, int>> nextLauncher;

int directionId(const string& d) {
    if (d == "N") return 0;
    if (d == "NE") return 1;
    if (d == "E") return 2;
    if (d == "SE") return 3;
    if (d == "S") return 4;
    if (d == "SW") return 5;
    if (d == "W") return 6;
    if (d == "NW") return 7;
    quitf(_fail, "invalid direction in input: %s", d.c_str());
}

int clockwiseTurns(int from, int to) {
    return (to - from + 8) % 8;
}

void addEdge(int from, int to, int dir) {
    nextLauncher[from][dir] = to;
}

void buildEdges() {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;

    sort(order.begin(), order.end(), [](int a, int b) {
        if (points[a].x != points[b].x) return points[a].x < points[b].x;
        return points[a].y < points[b].y;
    });
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (i > 0 && points[order[i - 1]].x == points[u].x) addEdge(u, order[i - 1], directionId("S"));
        if (i + 1 < n && points[order[i + 1]].x == points[u].x) addEdge(u, order[i + 1], directionId("N"));
    }

    sort(order.begin(), order.end(), [](int a, int b) {
        if (points[a].y != points[b].y) return points[a].y < points[b].y;
        return points[a].x < points[b].x;
    });
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (i > 0 && points[order[i - 1]].y == points[u].y) addEdge(u, order[i - 1], directionId("W"));
        if (i + 1 < n && points[order[i + 1]].y == points[u].y) addEdge(u, order[i + 1], directionId("E"));
    }

    sort(order.begin(), order.end(), [](int a, int b) {
        long long da = points[a].y - points[a].x;
        long long db = points[b].y - points[b].x;
        if (da != db) return da < db;
        return points[a].x < points[b].x;
    });
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (i > 0 && points[order[i - 1]].y - points[order[i - 1]].x == points[u].y - points[u].x) {
            addEdge(u, order[i - 1], directionId("SW"));
        }
        if (i + 1 < n && points[order[i + 1]].y - points[order[i + 1]].x == points[u].y - points[u].x) {
            addEdge(u, order[i + 1], directionId("NE"));
        }
    }

    sort(order.begin(), order.end(), [](int a, int b) {
        long long da = points[a].y + points[a].x;
        long long db = points[b].y + points[b].x;
        if (da != db) return da < db;
        return points[a].x < points[b].x;
    });
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        if (i > 0 && points[order[i - 1]].y + points[order[i - 1]].x == points[u].y + points[u].x) {
            addEdge(u, order[i - 1], directionId("NW"));
        }
        if (i + 1 < n && points[order[i + 1]].y + points[order[i + 1]].x == points[u].y + points[u].x) {
            addEdge(u, order[i + 1], directionId("SE"));
        }
    }
}

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(-1, 1000000000000000000LL, "minimum cost");
    stream.readEoln();

    if (claimed == -1) {
        stream.readEof();
        return {true, -1, -1};
    }

    vector<int> path;
    while (!stream.seekEof()) {
        path.push_back(stream.readInt(1, n, format("path[%d]", int(path.size()) + 1).c_str()) - 1);
    }

    if (path.size() < 2) {
        stream.quitf(_wa, "path must contain at least s and e");
    }
    if (path.front() != s) {
        stream.quitf(_wa, "path starts at %d instead of %d", path.front() + 1, s + 1);
    }
    if (path.back() != e) {
        stream.quitf(_wa, "path ends at %d instead of %d", path.back() + 1, e + 1);
    }

    vector<int> used(n, 0);
    long long actual = 0;
    for (int i = 0; i < int(path.size()); ++i) {
        int u = path[i];
        if (used[u]) {
            stream.quitf(_wa, "launcher %d is repeated in the path", u + 1);
        }
        used[u] = 1;

        if (i + 1 == int(path.size())) break;

        int v = path[i + 1];
        int dir = -1;
        for (const auto& [candidateDir, candidate] : nextLauncher[u]) {
            if (candidate == v) {
                dir = candidateDir;
                break;
            }
        }
        if (dir == -1) {
            stream.quitf(_wa, "launcher %d cannot directly send a marble to launcher %d", u + 1, v + 1);
        }
        actual += points[u].c * clockwiseTurns(points[u].dir, dir);
    }

    if (actual != claimed) {
        stream.quitf(_wa, "claimed cost %lld does not match path cost %lld", claimed, actual);
    }
    return {false, claimed, actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    s = inf.readInt() - 1;
    e = inf.readInt() - 1;
    points.resize(n);
    nextLauncher.assign(n, {});

    for (int i = 0; i < n; ++i) {
        string dir;
        points[i].x = inf.readLong();
        points[i].y = inf.readLong();
        points[i].c = inf.readLong();
        dir = inf.readToken();
        points[i].dir = directionId(dir);
    }
    buildEdges();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers are impossible");
        }
        quitf(_fail, "participant provided a valid path with cost %lld while jury says impossible", participant.actualCost);
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible, but jury has cost %lld", jury.actualCost);
    }
    if (participant.actualCost < jury.actualCost) {
        quitf(_fail, "participant found a better path: participant=%lld jury=%lld", participant.actualCost, jury.actualCost);
    }
    if (participant.actualCost > jury.actualCost) {
        quitf(_wa, "participant path cost %lld is greater than jury cost %lld", participant.actualCost, jury.actualCost);
    }

    quitf(_ok, "answer cost %lld", participant.actualCost);
}
