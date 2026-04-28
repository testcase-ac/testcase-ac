#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1500;
int A[MAX + 10][MAX + 10], B[MAX + 10][MAX + 10];
int d[MAX + 10][MAX + 10];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    string s;
    cin >> s;
    if (s[0] == 'A') A[i][j] = stoi(s.substr(1));
    else B[i][j] = stoi(s.substr(1));
  }

  for (int j = 1; j <= M; j++) {
    for (int i = 1; i <= N; i++) B[i][j] += B[i - 1][j];
    for (int i = N; i >= 1; i--) A[i][j] += A[i + 1][j];
  }

  for (int i = 1; i <= N; i++) d[i][1] = A[i + 1][1];
  for (int j = 2; j <= M; j++) {
    d[1][j] = d[1][j - 1] + A[2][j];
    for (int i = 2; i <= N; i++) {
      d[i][j] = max({
        d[i - 1][j] - (A[i][j] - A[i + 1][j]),
        d[i][j - 1] + B[i - 1][j] + A[i + 1][j],
        d[i - 1][j - 1] + B[i - 1][j] + A[i + 1][j]
      });
    }
  }

  cout << d[N][M] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
