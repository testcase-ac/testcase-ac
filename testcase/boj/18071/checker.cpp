#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> teams;

struct Claim {
    bool possible;
    int city;
};

bool isEquidistantCity(int city) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[city] = 0;
    q.push(city);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (dist[to] == -1) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }

    int expected = dist[teams[0]];
    for (int team : teams) {
        if (dist[team] != expected) {
            return false;
        }
    }
    return true;
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("YES|NO", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, -1};
    }

    int city = stream.readInt(1, n, "city");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after city");
    }

    if (!isEquidistantCity(city)) {
        stream.quitf(_wa, "city %d is not equidistant from all team cities", city);
    }

    return {true, city};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    graph.assign(n + 1, {});

    for (int i = 0; i < n - 1; ++i) {
        int v = inf.readInt();
        int u = inf.readInt();
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    teams.resize(m);
    for (int i = 0; i < m; ++i) {
        teams[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found valid city %d while jury reported NO", participant.city);
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury found valid city %d but participant reported NO", jury.city);
    }

    if (jury.possible) {
        quitf(_ok, "valid city %d", participant.city);
    }
    quitf(_ok, "NO");
}
