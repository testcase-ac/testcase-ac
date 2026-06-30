#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int MAX_NM = 1000000;

int targetA, targetB;

struct Claim {
    bool impossible;
    long long n;
    long long m;
};

void readInput() {
    string fraction = inf.readToken();
    size_t slash = fraction.find('/');
    targetA = stoi(fraction.substr(0, slash));
    targetB = stoi(fraction.substr(slash + 1));
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken();
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true, 0, 0};
    }

    long long n = stringToLongLong(stream, first);
    if (n < 1 || n > MAX_NM) {
        stream.quitf(_wa, "n is out of range [1, %d]: %lld", MAX_NM, n);
    }

    long long m = stream.readLong(1LL, (long long)MAX_NM, "m");
    vector<vector<int>> graph(n + 1);
    graph.reserve(n + 1);

    for (long long i = 0; i < m; ++i) {
        int u = stream.readInt(1, (int)n, format("u[%lld]", i + 1).c_str());
        int v = stream.readInt(1, (int)n, format("v[%lld]", i + 1).c_str());
        if (u != v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after graph");
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    long long sum = 0;
    for (int v = 1; v <= n; ++v) {
        if (dist[v] == -1) {
            stream.quitf(_wa, "graph is disconnected: vertex %d cannot reach vertex 1", v);
        }
        sum += dist[v];
    }

    __int128 lhs = (__int128)sum * targetB;
    __int128 rhs = (__int128)targetA * n;
    if (lhs != rhs) {
        stream.quitf(_wa,
                     "average distance is not target: sum=%lld n=%lld target=%d/%d",
                     sum,
                     n,
                     targetA,
                     targetB);
    }

    return {false, n, m};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    readInput();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant provided a valid graph while jury claimed impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claimed impossible while jury provided a valid graph");
    }

    quitf(_ok,
          "valid graph with n=%lld m=%lld",
          participant.n,
          participant.m);
}
