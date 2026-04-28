#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
vector<int> pr;
ll lp[MAX + 1];

int atop(char c) {
  return pr[c - 'a'];
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

template<ll M> struct Hashing {
  vector<ll> H, V;
  void build(const string &S) {
    int n = S.size();
    H.resize(n + 1);
    V.resize(n + 1);
    H[0] = 1;
    for (int i = 1; i <= n; i++) H[i] = (H[i-1] * atop(S[i - 1])) % M;

    V[n] = lpow(H[n], M - 2, M);
    for (int i = n - 1; i >= 0; i--) V[i] = (V[i + 1] * atop(S[i])) % M;
    assert(V[0] == 1);
  }
  ll sub(int s, int e) {
    return (H[e] * V[s - 1]) % M;
  }
};

constexpr int M1 = 601873, M2 = 1'000'000'009;
Hashing<M1> H1;
Hashing<M2> H2;
vector<pii> S[M1];

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  string s, t;
  int n;
  cin >> s >> t;

  H1.build(s); H2.build(s);
  n = s.size();

  for (int i = 1; i <= n; i++) for (int d = 0; i + d <= n; d++) {
    int h1 = H1.sub(i, i + d), h2 = H2.sub(i, i + d);
    S[h1].push_back({h2, d});
  }

  H1.build(t); H2.build(t);
  n = t.size();

  int ans = 0;
  for (int i = 1; i <= n; i++) for (int d = 0; i + d <= n; d++) {
    int h1 = H1.sub(i, i + d), h2 = H2.sub(i, i + d);
    for (auto &[hi, di] : S[h1]) {
      if (hi == h2 && di == d) {
        ans = max(ans, d + 1);
        break;
      }
    }
  }

  cout << ans << '\n';
}
