#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n;
  cin >> n;

  vector<ll> fcts;
  while (n % 2 == 0) {
    fcts.push_back(2);
    n /= 2;
  }

  for (int i = 3; i <= sqrt(n); i += 2) {
    while (n % i == 0) {
      fcts.push_back(i);
      n /= i;
    }
  }

  if (n > 1) fcts.push_back(n);

  int sz = fcts.size();
  if (sz == 1) cout << -1;
  else {
    int i = 0;
    vector<ll> ansv;

    while (i < sz) {
      if (i + 1 < sz) {
        ansv.push_back(fcts[i] * fcts[i + 1]);
        i += 2;
      }
      else {
        ansv[ansv.size() - 1] *= fcts[i];
        i++;
      }
    }

    for (auto el : ansv) cout << el << ' ';
  }

  cout << '\n';
}
