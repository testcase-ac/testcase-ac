#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int inclusion(int sub, ll a, ll b) {
  if (3 * a > b && 3 * a < 2 * b) return sub;
  else {
    if (sub == 10) return -1;
    else {
      if (2 * a > b) a = b - a;
      return inclusion(sub + 1, a * 3, b);
    }
  }
}

int main() {
  fast_io();

  ll tt, a, b;
  cin >> tt;

  while (tt--) {
    cin >> a >> b;
    if (a > b) cout << "0\n";
    else cout << inclusion(1, a, b) << '\n';
  }
}
