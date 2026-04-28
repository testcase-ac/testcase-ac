#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

typedef vector<int> seq_t;
void calculate_pi(vector<int>& pi, const seq_t& str) {
  pi[0] = -1;
  for (int i = 1, j = -1; i < str.size(); i++) {
    while (j >= 0 && str[i] != str[j + 1]) j = pi[j];
    if (str[i] == str[j + 1])
      pi[i] = ++j;
    else
      pi[i] = -1;
  }
}

int modint(int x, int m) {
  return (x % m + m) % m;
}

void solve() {
  int N; cin >> N;
  vector<int> A(N), pi(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  int a, b; cin >> a >> b;

  calculate_pi(pi, A); int V;
  for (V = N / 2; V >= 0; --V) if (pi[V] == 0) break;

  ll rep = (b - a) / V, repv = 0;
  for (int i = 0; i < V; ++i) repv += A[i];

  ll ans = rep * repv;
  int t = modint(b, V);
  while (1) {
    int s = modint(a, V);
    if (s == t) break;
    ans += A[s]; ++a;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
