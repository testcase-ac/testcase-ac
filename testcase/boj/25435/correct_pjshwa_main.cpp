#include <iostream>
#include <vector>
#include <algorithm>

const int MAX = 2e5;
int parent[MAX], usz[MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void init(int N, int S, std::vector<int> T,
          std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {

  for (int i = 0; i < N; i++) parent[i] = i, usz[i] = 1;
  std::vector<std::tuple<int, int, int>> E;
  for (int i = 0; i < N; i++) for (int t = 0; t < T[i]; t++) {
    E.push_back({A[i][t], B[i][t], i});
  }
  std::sort(E.begin(), E.end());

  int ed = -1, ci = -1;
  for (auto [a, b, i] : E) {
    if (a <= ed) Union(ci, i);
    ci = i;
    ed = std::max(ed, b);
  }

}

int count_users(int P) {
  return usz[Find(P)];
}

int main() {
  init(5, 10, {2, 1, 1, 1, 1},
    {{2, 7}, {1}, {1}, {9}, {5}},
    {{4, 9}, {3}, {1}, {10}, {6}});

  std::cout << count_users(0) << '\n';
  std::cout << count_users(1) << '\n';
  std::cout << count_users(2) << '\n';
  std::cout << count_users(3) << '\n';
  std::cout << count_users(4) << '\n';
}
