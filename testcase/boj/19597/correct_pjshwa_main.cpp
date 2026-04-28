#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 150;
string A[MAX];
int d[MAX][2];
int N;

bool r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];
  if (i == N - 1) return d[i][j] = true;

  bool ret = false;
  string S = A[i], T = A[i + 1];
  if (j) reverse(S.begin(), S.end());

  if (S < T) ret |= r(i + 1, 0);
  reverse(T.begin(), T.end());
  if (S < T) ret |= r(i + 1, 1);

  return d[i][j] = ret;
}

void trace(int i, int j) {
  cout << j;
  if (i == N - 1) return;

  string S = A[i], T = A[i + 1];
  if (j) reverse(S.begin(), S.end());

  if (S < T && r(i + 1, 0)) trace(i + 1, 0);
  else trace(i + 1, 1);
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  memset(d, -1, sizeof(d));

  if (r(0, 0)) trace(0, 0);
  else if (r(0, 1)) trace(0, 1);
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
