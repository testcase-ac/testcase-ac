#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, INF = 0x3f3f3f3f;
tuple<char, int, int> Ku[MAXN];
int Amin[26];
vector<int> O;
string SS;

void solve() {
  int N, M, K; cin >> N >> M >> K;

  fill(Amin, Amin + 26, INF);
  for (int i = 0; i < M; ++i) {
    string s; int d, a; cin >> s >> d >> a;

    char c = s[0];
    Ku[i] = {c, d, a};
    Amin[c - 'a'] = min(Amin[c - 'a'], a);
  }

  O.resize(N);
  for (int i = 0; i < N; ++i) cin >> O[i], --O[i];
  cin >> SS;

  // check if SS is substring of O starting from i
  // K = SS.size()
  int ans = INF;
  for (int i = 0; i <= N - K; ++i) {
    int cur = 0, ok = 1;

    vector<int> prices[26];
    for (int j = 0; j < K; ++j) {
      auto [c, d, a] = Ku[O[i + j]];
      if (c == SS[j]) continue;

      cur += d;
      prices[c - 'a'].push_back(0);
    }

    // check for other positions
    for (int j = 0; j < N; ++j) {
      if (j >= i && j < i + K) continue;

      auto [c, d, a] = Ku[O[j]];
      prices[c - 'a'].push_back(d);
    }

    for (int ci = 0; ci < 26; ++ci) {
      if (Amin[ci] == INF) continue;
      prices[ci].push_back(Amin[ci]);
      sort(prices[ci].begin(), prices[ci].end(), greater<int>());
    }

    for (int j = 0; j < K; ++j) {
      auto [c, d, a] = Ku[O[i + j]];
      if (c == SS[j]) continue;

      int t = SS[j] - 'a';
      if (prices[t].empty()) {
        ok = 0;
        break;
      }

      int cost = prices[t].back();
      cur += cost;
      if (cost == Amin[t]) continue;
      prices[t].pop_back();
    }

    if (ok) ans = min(ans, cur);
  }

  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
