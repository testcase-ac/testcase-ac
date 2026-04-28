#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
  return true;
}

vector<int> primes;

const int MAXZ = 21, MAXN = 150;
const int PLIM = MAXN / 2;
int Z, N, dp[1 << MAXZ][2];
vector<int> V;

bool rec(int state, int o) {
  if (dp[state][o] != -1) return dp[state][o];

  bool ret = false;
  if (o) ret |= !rec(state, o - 1);
  for (int estate : V) {
    if (state & estate) continue;
    ret |= !rec(state | estate, o);
  }

  return dp[state][o] = ret;
}

void solve() {
  int M; cin >> N >> M;

  int ones = 0; set<int> U;
  while (M--) {
    int x; cin >> x;
    if (x == 1) ++ones;
    else U.insert(x);
  }

  vector<int> over_plim;
  for (int e : U) {
    if (is_prime(e) && e > PLIM) over_plim.push_back(e);
  }

  int p = 0;
  for (int e : over_plim) U.erase(e), ++p;

  V.clear();
  for (int e : U) {
    int estate = 0;
    for (int i = 0; i < Z; ++i) {
      int prime = primes[i];
      if (e % prime == 0) estate |= 1 << i;
    }
    V.push_back(estate);
  }

  memset(dp, -1, sizeof(dp));
  cout << (rec(0, (p + ones) & 1) ? "amsminn" : "bnb2011") << '\n';
}

int main() {
  fast_io();

  for (int i = 2; i <= PLIM; ++i) if (is_prime(i)) primes.push_back(i);
  Z = primes.size();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
