#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void swap(ll& a, ll& b) {
  ll temp = a;
  a = b;
  b = temp;
}

int main() {
  fast_io();

  ll D, P, Q;
  cin >> D >> P >> Q;

  if (P < Q) swap(P, Q);

  ll R = min(D / P + 1, Q), CP, CQ;

  ll mv = 1e18;
  for (int i = 0; i <= R; i++) {
    CP = P * i;
    if (CP >= D) CQ = 0;
    else CQ = ((D - CP - 1) / Q + 1) * Q;
    mv = min(mv, CP + CQ);
  }

  cout << mv;
}
