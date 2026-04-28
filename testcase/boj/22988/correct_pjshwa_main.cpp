#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

int main() {
  fast_io();

  int n, oans = 0;
  ll x;
  cin >> n >> x;

  vector<ll> a;
  for (int i = 0; i < n; i++) {
    ll s;
    cin >> s;
    if (s == x) oans++;
    else a.push_back(s);
  }
  sort(a.begin(), a.end());

  int lp = 0, rp = a.size() - 1, pans = 0;
  while (lp < rp) {
    ll csum = a[lp] + a[rp];
    if (csum * 2 >= x) {
      pans++;
      lp++;
      rp--;
    }
    else lp++;
  }

  cout << oans + pans + (a.size() - 2 * pans) / 3;
}
