#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int A[MAX], B[MAX], N;

int f() {
  int d[3][3];
  memset(d, 0, sizeof(d));

  for (int i = 0; i < N; i++) d[A[i] - 1][B[i] - 1]++;
  int res = 0;

  int m01 = min(d[0][1], d[1][0]);
  d[0][1] -= m01, d[1][0] -= m01, res += m01;

  int m02 = min(d[0][2], d[2][0]);
  d[0][2] -= m02, d[2][0] -= m02, res += m02;

  int m12 = min(d[1][2], d[2][1]);
  d[1][2] -= m12, d[2][1] -= m12, res += m12;

  int m012 = min({d[0][1], d[1][2], d[2][0]});
  d[0][1] -= m012, d[1][2] -= m012, d[2][0] -= m012, res += 2 * m012;

  int m021 = min({d[0][2], d[2][1], d[1][0]});
  d[0][2] -= m021, d[2][1] -= m021, d[1][0] -= m021, res += 2 * m021;

  return res;
}

void solve() {
  cin >> N;

  map<int, int> t;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    t[A[i]]++;
  }

  vector<tii> p = {
    {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}
  };

  int ans = INF;
  for (auto [a, b, c] : p) {
    int i = 0;
    for (int j = 0; j < t[a]; j++) B[i++] = a;
    for (int j = 0; j < t[b]; j++) B[i++] = b;
    for (int j = 0; j < t[c]; j++) B[i++] = c;

    ans = min(ans, f());
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
