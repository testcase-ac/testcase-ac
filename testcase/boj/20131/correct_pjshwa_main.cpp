#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
int A[MAX + 1], C[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N - 2; i++) cin >> A[i], C[A[i]]++;

  priority_queue<int> pq;
  for (int i = 1; i <= N; i++) {
    if (C[i] == 0) pq.push(i);
  }

  vector<pii> ans;
  for (int i = 1; i <= N - 2; i++) {
    int u = pq.top(); pq.pop();

    if (u < A[i]) ans.push_back({u, A[i]});
    else ans.push_back({A[i], u});

    if (!--C[A[i]]) pq.push(A[i]);
  }

  if (A[N - 2] == 1) ans.push_back({1, 2});
  else ans.push_back({1, A[N - 2]});

  sort(ans.begin(), ans.end());
  for (auto [u, v] : ans) cout << u << ' ' << v << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
