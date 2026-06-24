#include "testlib.h"

#include <algorithm>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int n;
set<pair<int, int>> originalEdges;

struct Answer {
  int k;
  int claimedDiameter;
  int actualDiameter;
};

int computeDiameter(const vector<vector<int>>& graph) {
  int diameter = 0;
  for (int start = 1; start <= n; ++start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : graph[u]) {
        if (dist[v] != -1) continue;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }

    for (int v = 1; v <= n; ++v) {
      if (dist[v] == -1) {
        quitf(_fail, "internal error: graph is disconnected after construction");
      }
      diameter = max(diameter, dist[v]);
    }
  }
  return diameter;
}

Answer readAnswer(InStream& stream) {
  int k = stream.readInt(0, n - 1, "K");
  stream.readEoln();
  int claimedDiameter = stream.readInt(1, n - 1, "R");
  stream.readEoln();

  vector<vector<int>> graph(n + 1);
  for (auto [u, v] : originalEdges) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  set<pair<int, int>> addedEdges;
  for (int i = 0; i < k; ++i) {
    int u = stream.readInt(1, n, format("added_edge[%d].u", i + 1).c_str());
    stream.readSpace();
    int v = stream.readInt(1, n, format("added_edge[%d].v", i + 1).c_str());
    stream.readEoln();

    if (u == v) {
      stream.quitf(_wa, "added edge %d is a self-loop: %d %d", i + 1, u, v);
    }
    auto edge = minmax(u, v);
    if (originalEdges.count(edge)) {
      stream.quitf(_wa, "added edge %d already exists: %d %d", i + 1, u, v);
    }
    if (!addedEdges.insert(edge).second) {
      stream.quitf(_wa, "added edge %d is duplicated: %d %d", i + 1, u, v);
    }

    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  stream.readEof();

  int actualDiameter = computeDiameter(graph);
  if (actualDiameter != claimedDiameter) {
    stream.quitf(_wa, "claimed diameter R=%d, but construction has diameter %d",
                 claimedDiameter, actualDiameter);
  }

  return {k, claimedDiameter, actualDiameter};
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  n = inf.readInt();
  for (int i = 0; i < n - 1; ++i) {
    int u = inf.readInt();
    int v = inf.readInt();
    originalEdges.insert(minmax(u, v));
  }

  Answer jury = readAnswer(ans);
  Answer participant = readAnswer(ouf);

  if (participant.actualDiameter > jury.actualDiameter) {
    quitf(_wa, "jury has better diameter: jury=%d participant=%d",
          jury.actualDiameter, participant.actualDiameter);
  }
  if (participant.actualDiameter < jury.actualDiameter) {
    quitf(_fail, "participant found better diameter: jury=%d participant=%d",
          jury.actualDiameter, participant.actualDiameter);
  }

  quitf(_ok, "diameter=%d, added_edges=%d", participant.actualDiameter, participant.k);
}
