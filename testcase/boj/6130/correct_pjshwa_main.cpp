#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX], B[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i], A[i]--, B[i] = A[i];
  sort(B, B + N);

  int t[3][3]{};
  for (int i = 0; i < N; i++) t[A[i]][B[i]]++;

  int ans = 0;
  while (t[0][1] && t[1][0]) t[0][1]--, t[1][0]--, ans++;
  while (t[1][2] && t[2][1]) t[1][2]--, t[2][1]--, ans++;
  while (t[2][0] && t[0][2]) t[2][0]--, t[0][2]--, ans++;
  while (t[0][1] && t[1][2] && t[2][0]) t[0][1]--, t[1][2]--, t[2][0]--, ans += 2;
  while (t[0][2] && t[1][0] && t[2][1]) t[0][2]--, t[1][0]--, t[2][1]--, ans += 2;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
