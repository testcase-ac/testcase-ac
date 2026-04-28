#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int r[MAX], da[MAX], db[MAX];
int n, a, b;

void solve() {
  priority_queue<pii> pq;
  for (int i = 0; i < n; i++) {
    cin >> r[i] >> da[i] >> db[i];
    pq.push({abs(da[i] - db[i]), i});
  }

  ll ans = 0;
  while (!pq.empty()) {
    int i = pq.top().second;
    pq.pop();

    if (da[i] > db[i]) {
      ll diff = min(b, r[i]);
      ans += diff * db[i];
      b -= diff;
      r[i] -= diff;
    }
    else {
      ll diff = min(a, r[i]);
      ans += diff * da[i];
      a -= diff;
      r[i] -= diff;
    }

    if (r[i]) ans += max(da[i], db[i]) * r[i];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> a >> b;
    if (n == 0 && a == 0 && b == 0) break;
    solve();
  }
}
