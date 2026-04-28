#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 5e6, LIM = 2e18;
int lp[MAXN + 1];
bool U[MAXN + 1];
vector<int> pr;

void solve() {
  ll N, K; cin >> N >> K;

  vector<ll> C;
  for (int p : pr) for (int pw : pr) {
    if (pw == 2) continue;
    __int128_t w = 1; int ok = 1;
    for (int j = 0; j < pw; ++j) {
      w *= p;
      if (w > LIM) {
        ok = 0;
        break;
      }
    }
    if (!ok) break;
    C.push_back((ll)w);
  }

  // calculate primes in range [Q, Q + MAXN]
  ll Q = sqrt(N) - 1;
  fill(U, U + MAXN + 1, 1);
  for (int p : pr) {
    ll start = Q / p * p;
    if (start < Q) start += p;
    for (ll j = start; j <= Q + MAXN; j += p) {
      if (j != p && j >= Q) U[j - Q] = 0;
    }
  }

  for (int i = 0; i <= MAXN; ++i) {
    ll val = Q + i;
    if (U[i]) C.push_back(val * val);
  }

  sort(C.begin(), C.end()); int cnt = 0;
  for (ll c : C) {
    if (c <= N) continue;
    if (++cnt == K) {
      cout << c << '\n';
      return;
    }
  }

  // for (int i = 0; i < 100; ++i) {
  //   ll val = Q + i;
  //   if (U[i]) cout << (val * val) << " is prime square\n";
  // }

  // cout << C.size() << '\n';
  // cout << "C = { ";
  // for (int j = 0; j < 10; ++j) cout << C[j] << ' ';
  // cout << "... }\n";

}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXN; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
