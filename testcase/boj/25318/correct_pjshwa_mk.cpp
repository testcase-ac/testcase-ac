#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int L[MAX + 1], T[MAX + 1];
double P[MAX + 1];

void solve() {
  int N;
  cin >> N;
  if (N == 0) return cout << "0\n", void();

  struct tm t;
  for (int i = 1; i <= N; i++) {
    int li;
    cin >> get_time(&t, "%Y/%m/%d %H:%M:%S") >> li;
    L[i] = li;
    T[i] = mktime(&t);
  }

  for (int i = 1; i <= N; i++) {
    double pp = pow(0.9, N - i);
    double py = pow(0.5, (T[N] - T[i]) / (365.0 * 86400));
    P[i] = max(pp, py);
  }

  double ans = 0, div = 0;
  for (int i = 1; i <= N; i++) ans += P[i] * L[i], div += P[i];
  cout << round(ans / div) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
