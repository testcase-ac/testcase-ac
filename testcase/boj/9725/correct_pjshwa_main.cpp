#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 501;
int A[MAX];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  int P[3][3]{};
  for (int i = 0; i < N; i++) P[i % 3][A[i] % 3]++;

  int ans = 0;
  while (P[0][1] && P[1][0]) P[0][1]--, P[1][0]--, ans++;
  while (P[1][2] && P[2][1]) P[1][2]--, P[2][1]--, ans++;
  while (P[2][0] && P[0][2]) P[2][0]--, P[0][2]--, ans++;
  while (P[0][1] && P[1][2] && P[2][0]) P[0][1]--, P[1][2]--, P[2][0]--, ans += 2;
  while (P[0][2] && P[1][0] && P[2][1]) P[0][2]--, P[1][0]--, P[2][1]--, ans += 2;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
