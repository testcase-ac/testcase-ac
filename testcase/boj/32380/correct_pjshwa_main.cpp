#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
ll A[MAXN + 1], B[MAXN + 1], PA[MAXN + 1], PB[MAXN + 1];

void solve() {
  int N, U, D; cin >> N >> U >> D;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 1; i <= N; ++i) cin >> B[i];

  priority_queue<pii, vector<pii>, greater<pii>> uwait;
  ll pre = 0, efs = 0;
  for (ll i = 1; i <= N; ++i) {
    if (A[i] < B[i]) {
      ll d = (B[i] - A[i] - 1) / (U + D) + 1;
      uwait.emplace(i + d, i);
      pre += A[i];
    } else {
      pre += B[i];
    }

    while (!uwait.empty() && uwait.top().first == i) {
      auto [_, j] = uwait.top(); uwait.pop();
      efs += (j - i) * (U + D);
      pre += B[j] - A[j];
    }
    cout << pre + efs << '\n';

    ll ucnt = uwait.size(), dcnt = i - ucnt;
    efs += ucnt * U - dcnt * D;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
