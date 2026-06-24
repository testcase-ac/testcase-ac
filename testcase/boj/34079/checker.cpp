#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

struct Claim {
    int vertex;
};

int n, m;
vector<vector<int>> graph;
vector<int> distFromStart;
vector<int> distFromEnd;
vector<int> shortestLayerSize;

vector<int> bfs(int start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int next : graph[cur]) {
            if (dist[next] != -1) {
                continue;
            }
            dist[next] = dist[cur] + 1;
            q.push(next);
        }
    }

    return dist;
}

Claim readClaim(InStream& stream) {
    int vertex = stream.readInt(1, n, "V");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after V");
    }
    return {vertex};
}

bool isValidMeetingVertex(int vertex) {
    if (vertex <= 1 || vertex >= n) {
        return false;
    }

    int shortestDistance = distFromStart[n];
    if (distFromStart[vertex] + distFromEnd[vertex] != shortestDistance) {
        return false;
    }

    return shortestLayerSize[distFromStart[vertex]] == 1;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    graph.assign(n + 1, {});

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    distFromStart = bfs(1);
    distFromEnd = bfs(n);

    int shortestDistance = distFromStart[n];
    shortestLayerSize.assign(shortestDistance + 1, 0);
    for (int vertex = 1; vertex <= n; ++vertex) {
        if (distFromStart[vertex] + distFromEnd[vertex] == shortestDistance) {
            ++shortestLayerSize[distFromStart[vertex]];
        }
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    bool juryHasWitness = jury.vertex != 1;
    bool participantHasWitness = participant.vertex != 1;

    if (juryHasWitness && !isValidMeetingVertex(jury.vertex)) {
        quitf(_fail, "jury output %d is not a valid meeting vertex", jury.vertex);
    }

    if (participantHasWitness && !isValidMeetingVertex(participant.vertex)) {
        quitf(_wa, "participant output %d is not a valid meeting vertex", participant.vertex);
    }

    if (!juryHasWitness) {
        if (participantHasWitness) {
            quitf(_fail, "participant found valid meeting vertex %d while jury output is 1", participant.vertex);
        }
        quitf(_ok, "both outputs claim no non-endpoint meeting vertex");
    }

    if (!participantHasWitness) {
        quitf(_wa, "jury has valid meeting vertex %d but participant output is 1", jury.vertex);
    }

    quitf(_ok, "valid meeting vertex %d", participant.vertex);
}
