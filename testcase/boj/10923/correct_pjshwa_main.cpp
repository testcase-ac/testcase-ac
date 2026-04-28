#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
int A[MAX], P[MAX];
bool vis[MAX];
stack<pii> T;

void dfs(int v) {
  vis[v] = 1;
  int nxt = A[v];
  if (!vis[nxt]) {
    T.push({v, nxt});
    dfs(nxt);
  }
}

void solve() {
  int N, M;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i], P[i] = i;

  cin >> M;
  vector<pii> S;
  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    S.push_back({x, y});
    swap(A[x], A[y]);
  }

  vector<pii> B;
  for (int i = 0; i < N; i++) {
    if (!vis[i]) dfs(i);
    while (!T.empty()) {
      B.push_back(T.top());
      T.pop();
    }
  }

  vector<pii> ans;
  while (!S.empty()) {
    if (B.empty()) {
      ans.push_back({0, 0});
    }
    else {
      auto [bx, by] = B.back();
      B.pop_back();

      ans.push_back({P[bx], P[by]});
      swap(A[P[bx]], A[P[by]]);
    }

    auto [sx, sy] = S.back();
    S.pop_back();

    // swap(P[sx], P[sy]);
    int xi, yi;
    for (int i = 0; i < N; i++) {
      if (P[i] == sx) xi = i;
      if (P[i] == sy) yi = i;
    }
    swap(P[xi], P[yi]);
  }

  reverse(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (auto [x, y] : ans) cout << x << ' ' << y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
