#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int S2[10'000], S3[100];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    int n = stoi(S);
    ++S2[n % 10'000]; ++S3[n % 100];
  }

  vector<pii> V;
  for (int i = 0; i < 100; ++i) V.emplace_back(S3[i], i);
  sort(V.begin(), V.end(), greater<>());
  while (V.size() > 5) V.pop_back();

  int ans = 0;
  for (int s = 0; s < 10'000; ++s) for (int f = 0; f < 100; ++f) {
    int sr = s % 100;
    if (sr == f) continue;

    int cur = (S3[f] > 0) * 300'000 + S2[s] * 4'000;
    int csum = 0, ccnt = 0;
    for (int i = 0; i < 5 && ccnt < 3; ++i) {
      auto [cnt, idx] = V[i];
      if (idx == f || idx == sr) continue;
      csum += cnt;
      ++ccnt;
    }

    cur += csum * 500;
    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
