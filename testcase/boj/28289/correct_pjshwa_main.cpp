#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int P; cin >> P;

  int A = 0, B = 0, C = 0, D = 0;
  while (P--) {
    int Gp, Cp, Np; cin >> Gp >> Cp >> Np;
    if (Gp == 1) D++;
    else {
      if (Cp <= 2) A++;
      else if (Cp == 3) B++;
      else C++;
    }
  }
  cout << A << '\n' << B << '\n' << C << '\n' << D << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
