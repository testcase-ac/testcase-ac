#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makeRandomEdges(int n, int m, int k) {
  vector<pair<int, int>> edges;
  edges.reserve(k);
  for (int i = 0; i < k; ++i) {
    edges.emplace_back(rnd.next(1, n), rnd.next(1, m));
  }
  return edges;
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int t = rnd.next(1, 5);
  vector<vector<pair<int, int>>> cases;
  vector<pair<int, int>> sizes;
  cases.reserve(t);
  sizes.reserve(t);

  int totalK = 0;
  for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    vector<pair<int, int>> edges;

    if (mode == 0) {
      n = rnd.next(1, 4);
      m = rnd.next(1, 4);
    } else if (mode == 1) {
      int len = rnd.next(1, min(n, m));
      for (int i = 1; i <= len; ++i) {
        edges.emplace_back(i, i);
      }
    } else if (mode == 2) {
      int len = rnd.next(1, min(n, m));
      for (int i = 1; i <= len; ++i) {
        edges.emplace_back(i, m - i + 1);
      }
    } else if (mode == 3) {
      n = rnd.next(1, 5);
      m = rnd.next(1, 5);
      pair<int, int> repeated = {rnd.next(1, n), rnd.next(1, m)};
      int k = rnd.next(2, 18);
      for (int i = 0; i < k; ++i) {
        if (rnd.next(0, 2) == 0) {
          edges.push_back(repeated);
        } else {
          edges.emplace_back(rnd.next(1, n), rnd.next(1, m));
        }
      }
    } else if (mode == 4) {
      n = rnd.next(2, 7);
      m = rnd.next(2, 7);
      for (int east = 1; east <= n; ++east) {
        for (int west = 1; west <= m; ++west) {
          edges.emplace_back(east, west);
        }
      }
      shuffle(edges.begin(), edges.end());
      edges.resize(rnd.next(1, static_cast<int>(edges.size())));
    } else if (mode == 5) {
      n = rnd.next(990, 1000);
      m = rnd.next(990, 1000);
      int k = rnd.next(1, 24);
      edges = makeRandomEdges(n, m, k);
      edges.emplace_back(1, m);
      edges.emplace_back(n, 1);
    } else {
      int k = rnd.next(1, 36);
      edges = makeRandomEdges(n, m, k);
    }

    shuffle(edges.begin(), edges.end());
    totalK += static_cast<int>(edges.size());
    sizes.emplace_back(n, m);
    cases.push_back(edges);
  }

  println(t);
  for (int i = 0; i < t; ++i) {
    println(sizes[i].first, sizes[i].second, static_cast<int>(cases[i].size()));
    for (const auto& edge : cases[i]) {
      println(edge.first, edge.second);
    }
  }

  ensure(totalK <= 400000);
  return 0;
}
