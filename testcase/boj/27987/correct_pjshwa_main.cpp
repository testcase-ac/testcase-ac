#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll A[MAXN];

void solve() {
  int N; cin >> N;

  ll sumv = 0; priority_queue<pair<ll, int>> pq;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    sumv += A[i];
    pq.push({A[i], i + 1});
  }

  queue<int> wait;
  while (!pq.empty()) {
    auto [v, x] = pq.top(); pq.pop();
    for (int i = 0; i < v; ++i) wait.push(x);
  }

  int l = 1, r = sumv + 1;
  while (l < r) {
    int m = (l + r) / 2;
    int cnt = sumv % m, t = ((sumv - 1) / m + 1) * m;
    if (cnt == 0) cnt = m;

    for (int i = 0; i < N; ++i) {
      if (A[i] * m > t) cnt = -1;
      else if (A[i] * m == t) --cnt;
    }

    if (cnt >= 0) l = m + 1;
    else r = m;
  }

  int gap = l - 1;
  vector<int> ans(sumv, -1);
  for (int i = 0; i < sumv; ++i) {
    if (ans[i] != -1) break;
    for (int j = i; j < sumv; j += gap) {
      ans[j] = wait.front(); wait.pop();
    }
  }
  for (int i = 0; i < sumv; ++i) cout << ans[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
