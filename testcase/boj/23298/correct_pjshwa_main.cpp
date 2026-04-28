#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

template<ll P, ll M> struct Hashing{
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
  return {H1.sub(s, e), H2.sub(s, e)};
}

int main() {
  fast_io();

  int n;
  cin >> n;
  set<pii> hs;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    H1.build(s); H2.build(s);
    hs.insert({H1.H.back(), H2.H.back()});
  }

  string s;
  cin >> s;
  H1.build(s); H2.build(s);

  vector<int> prefixes, suffixes;
  for (int i = 1; i <= s.size(); i++) {
    auto sp = sub(1, i), ss = sub(i, s.size());
    if (hs.count(sp)) prefixes.push_back(i);
    if (hs.count(ss)) suffixes.push_back(i);
  }

  int cnt = 0;
  for (int pf : prefixes) {
    for (int sf : suffixes) {
      if (pf + 1 > sf - 1) continue;
      auto p = sub(pf + 1, sf - 1);
      if (hs.count(p)) cnt++;
    }
  }

  cout << cnt << '\n';
}
