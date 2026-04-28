#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1 << 22;
int p[3][MAX + 1];

string S, T = "";
int count_diff(int N, int s) {
  if (N == 0) return 0;

  int ret = 0;
  ret += N / 4 - (p[0][s + 1 * N / 4] - p[0][s]);
  ret += N / 4 - (p[1][s + 2 * N / 4] - p[1][s + 1 * N / 4]);
  ret += N / 4 - (p[2][s + 3 * N / 4] - p[2][s + 2 * N / 4]);

  return ret + count_diff(N / 4, s + 3 * N / 4);
}

void solve() {
  int K;
  cin >> K >> S;
  S += S;

  int N = 1;
  for (int i = 0; i < K; i++) N *= 4;

  for (int i = 1; i <= 2 * N; i++) {
    for (int j = 0; j < 3; j++) p[j][i] = p[j][i - 1];
    if (S[i - 1] == 'J') p[0][i]++;
    if (S[i - 1] == 'O') p[1][i]++;
    if (S[i - 1] == 'I') p[2][i]++;
  }

  int ans = count_diff(N, 0);
  for (int s = 1; s < N; s++) {
    // int cur = count_diff(N, s);
    // cout << "cur = " << cur << endl;
    ans = min(ans, count_diff(N, s));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
