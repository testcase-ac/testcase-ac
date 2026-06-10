#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

namespace {

void AddEdge(vector<pair<int, int>>& edges, int a, int b) {
  edges.emplace_back(a, b);
}

vector<pair<int, int>> BuildTree(int n, int mode) {
  vector<pair<int, int>> edges;

  if (mode == 0) {
    for (int i = 1; i < n; ++i) {
      AddEdge(edges, i - 1, i);
    }
  } else if (mode == 1) {
    int center = rnd.next(0, n - 1);
    for (int i = 0; i < n; ++i) {
      if (i != center) {
        AddEdge(edges, center, i);
      }
    }
  } else if (mode == 2) {
    int spine = rnd.next(2, n);
    for (int i = 1; i < spine; ++i) {
      AddEdge(edges, i - 1, i);
    }
    for (int i = spine; i < n; ++i) {
      AddEdge(edges, rnd.next(0, spine - 1), i);
    }
  } else if (mode == 3) {
    for (int i = 1; i < n; ++i) {
      AddEdge(edges, rnd.next(0, i - 1), i);
    }
  } else if (mode == 4) {
    for (int i = 1; i < n; ++i) {
      AddEdge(edges, (i - 1) / 2, i);
    }
  } else {
    int right = rnd.next(1, n - 1);
    AddEdge(edges, 0, right);
    for (int i = 1; i < n; ++i) {
      if (i == right) {
        continue;
      }
      AddEdge(edges, rnd.next(0, 1) == 0 ? 0 : right, i);
    }
  }

  return edges;
}

}  // namespace

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int mode = rnd.next(0, 5);
  int n = rnd.next(2, 35);
  if (mode == 0 && rnd.next(0, 4) == 0) {
    n = rnd.next(2, 8);
  }

  vector<pair<int, int>> edges = BuildTree(n, mode);

  vector<int> label(n);
  for (int i = 0; i < n; ++i) {
    label[i] = i;
  }
  shuffle(label.begin(), label.end());
  shuffle(edges.begin(), edges.end());

  println(n);
  for (auto [a, b] : edges) {
    if (rnd.next(0, 1) == 0) {
      swap(a, b);
    }
    println(label[a], label[b]);
  }

  return 0;
}
