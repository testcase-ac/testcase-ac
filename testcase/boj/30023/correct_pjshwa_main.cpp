#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 1e9 + 7;

char nxt(char c) {
  if (c == 'R') return 'G';
  if (c == 'G') return 'B';
  return 'R';
}

void solve() {
  int N; string S; cin >> N >> S;

  // how many flips necessary to make S1 all R
  string S1 = S; int ans1 = 0;
  for (int i = 0; i < N - 2; ++i) {
    while (S1[i] != 'R') {
      S1[i] = nxt(S1[i]);
      S1[i + 1] = nxt(S1[i + 1]);
      S1[i + 2] = nxt(S1[i + 2]);
      ++ans1;
    }
  }
  if (S1[N - 2] != 'R' || S1[N - 1] != 'R') ans1 = INF;

  // how many flips necessary to make S2 all G
  string S2 = S; int ans2 = 0;
  for (int i = 0; i < N - 2; ++i) {
    while (S2[i] != 'G') {
      S2[i] = nxt(S2[i]);
      S2[i + 1] = nxt(S2[i + 1]);
      S2[i + 2] = nxt(S2[i + 2]);
      ++ans2;
    }
  }
  if (S2[N - 2] != 'G' || S2[N - 1] != 'G') ans2 = INF;

  // how many flips necessary to make S3 all B
  string S3 = S; int ans3 = 0;
  for (int i = 0; i < N - 2; ++i) {
    while (S3[i] != 'B') {
      S3[i] = nxt(S3[i]);
      S3[i + 1] = nxt(S3[i + 1]);
      S3[i + 2] = nxt(S3[i + 2]);
      ++ans3;
    }
  }
  if (S3[N - 2] != 'B' || S3[N - 1] != 'B') ans3 = INF;

  int ans = min(ans1, min(ans2, ans3));
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
