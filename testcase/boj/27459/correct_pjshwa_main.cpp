#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  map<int, int> t1, t2;
  for (int i = 0; i < N; i++) {
    if (i & 1) t1[A[i]]++;
    else t2[A[i]]++;
  }

  priority_queue<pii> q1, q2;
  for (auto [k, v] : t1) q1.push({v, k});
  for (auto [k, v] : t2) q2.push({v, k});

  if (q1.top().second == q2.top().second) {
    int q11 = q1.top().first, q21 = q2.top().first;
    q1.pop(); q2.pop();

    int q12 = q1.empty() ? 0 : q1.top().first;
    int q22 = q2.empty() ? 0 : q2.top().first;

    cout << N - max(q11 + q22, q12 + q21) << '\n';
  }
  else {
    cout << N - q1.top().first - q2.top().first << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
