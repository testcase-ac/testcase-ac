#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
  int N, K;

  cin >> N >> K;

  vector<vector<int>> g(N + 1);
  vector<int> on(N + 1, 0);
  vector<int> st(1, 1);
  vector<int> vis(N + 1, 0);
  vector<int> dep(N + 1, 0);

  for (int i = 0; i < N - 1; i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  while (!st.empty()) {
    int x = st.back();

    if (vis[x] == 0) {
      for (int y : g[x]) {
        if (vis[y] == 0) {
          st.push_back(y);
        }
      }
      vis[x] = 1;
    } else {
      int d1 = 0, d2 = 0;

      for (int y : g[x]) {
        if (vis[y] == 2) {
          int k = dep[y] + 1;
          if (k >= d1) {
            d2 = d1;
            d1 = k;
          } else if (k >= d2) {
            d2 = k;
          }
        }
      }

      if (d1 + d2 >= K) {
        on[x] = 1;
        dep[x] = -1;
      } else {
        dep[x] = d1;
      }
      vis[x] = 2;
      st.pop_back();
    }
  }

  cout << accumulate(on.begin(), on.end(), 0) << '\n';
}