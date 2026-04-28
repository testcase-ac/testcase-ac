#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int X[MAX], L[MAX], C[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> X[i];
  for (int i = 0; i < N; i++) cin >> L[i];
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    if (S == "R") C[i] = 0;
    if (S == "Y") C[i] = 1;
    if (S == "B") C[i] = 2;
  }

  vector<tuple<int, int, int, int>> A(N);
  for (int i = 0; i < N; i++) A[i] = {X[i], L[i], C[i], i};
  sort(A.begin(), A.end(), [](const auto& a, const auto& b) {
    auto [x1, l1, c1, i1] = a;
    auto [x2, l2, c2, i2] = b;
    return x1 - l1 < x2 - l2;
  });

  priority_queue<pii, vector<pii>, greater<pii>> W[3];
  for (auto& [x, l, c, i] : A) {
    for (int cc = 0; cc < 3; cc++) {
      if (c == cc) continue;

      while (!W[cc].empty() && W[cc].top().first < x - l) W[cc].pop();
      if (!W[cc].empty()) {
        auto& [_, j] = W[cc].top();
        cout << "YES\n" << j + 1 << " " << i + 1 << "\n";
        return;
      }
    }

    W[c].emplace(x + l, i);
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
