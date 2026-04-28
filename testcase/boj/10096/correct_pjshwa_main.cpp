#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

template<ll P, ll M> struct Hashing {
  vector<ll> H, B;
  void build(const string &S){
    H.resize(S.size()+1);
    B.resize(S.size()+1);
    B[0] = 1;
    for(int i=1; i<=S.size(); i++) H[i] = (H[i-1] * P + S[i-1]) % M;
    for(int i=1; i<=S.size(); i++) B[i] = B[i-1] * P % M;
  }
  ll sub(int s, int e){
    ll res = (H[e] - H[s-1] * B[e-s+1]) % M;
    return res < 0 ? res + M : res;
  }
};

constexpr int P1 = 1299709, M1 = 1'000'000'007;
constexpr int P2 = 1301021, M2 = 1'000'000'009;

Hashing<P1, M1> H1;
Hashing<P2, M2> H2;

pii sub(int s, int e) {
  if (s > e) return {-1, -1};
  return {H1.sub(s, e), H2.sub(s, e)};
}

int main() {
  fast_io();

  int n;
  string t;
  cin >> n >> t;
  if (n % 2 == 0) return cout << "NOT POSSIBLE\n", 0;

  H1.build(t); H2.build(t);
  set<pii> hashes;

  for (int ex = 1; ex <= n / 2; ex++) {
    if (
      sub(1, ex - 1) == sub(n / 2 + 2, n / 2 + ex) &&
      sub(ex + 1, n / 2 + 1) == sub(n / 2 + ex + 1, n)
    ) hashes.insert(sub(n / 2 + 2, n));
  }

  if (sub(1, n / 2) == sub(n / 2 + 2, n)) hashes.insert(sub(n / 2 + 2, n));

  for (int ex = n / 2 + 2; ex <= n; ex++) {
    if (
      sub(n / 2 + 1, ex - 1) == sub(1, ex - n / 2 - 1) &&
      sub(ex + 1, n) == sub(ex - n / 2, n / 2)
    ) hashes.insert(sub(1, n / 2));
  }

  if (hashes.size() == 0) return cout << "NOT POSSIBLE\n", 0;
  if (hashes.size() >= 2) return cout << "NOT UNIQUE\n", 0;

  if (*hashes.begin() == sub(1, n / 2)) for (int i = 1; i <= n / 2; i++) cout << t[i - 1];
  else for (int i = n / 2 + 2; i <= n; i++) cout << t[i - 1];
  cout << '\n';
}
