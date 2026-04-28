#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
ll lp[MAXN + 1];
vector<int> pr;

void solve() {
  ll N, cnt; cin >> N;

  cnt = 0;
  for (int i = 3; i <= N; ++i) cnt += (i - 1) / 2;
  cout << cnt << '\n';

  vector<int> fs;
  for (int f = 1; f * f <= N; ++f) {
    if (N % f == 0) {
      fs.push_back(f);
      if (f * f != N) fs.push_back(N / f);
    }
  }
  sort(fs.begin(), fs.end());

  cnt = 0;
  for (int f1 : fs) for (int f2 : fs) for (int f3 : fs) {
    if (f2 < f1) continue;
    if (f1 + f2 == f3) ++cnt;
  }
  cout << cnt << '\n';

  cnt = 0;
  for (int c = 5; c <= N; c += 2) {
    int b = c - 2;
    if (lp[b] == b && lp[c] == c) ++cnt;
  }
  cout << cnt << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXN; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
