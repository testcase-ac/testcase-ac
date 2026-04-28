#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Fs, Cs, Es, Bs, Fn, Cn, En, Bn, Q, acc = 0; cin >> Fs >> Cs >> Es >> Bs >> Fn >> Cn >> En >> Bn >> Q;
  while (Q--) {
    int op, x; cin >> op >> x;
    if (op == 1) {
      if (Fs >= x * Fn && Cs >= x * Cn && Es >= x * En && Bs >= x * Bn) {
        Fs -= x * Fn;
        Cs -= x * Cn;
        Es -= x * En;
        Bs -= x * Bn;
        acc += x;
        cout << acc << '\n';
      } else {
        cout << "NO\n";
      }

    } else if (op == 2) {
      Fs += x; cout << Fs << '\n';
    } else if (op == 3) {
      Cs += x; cout << Cs << '\n';
    } else if (op == 4) {
      Es += x; cout << Es << '\n';
    } else if (op == 5) {
      Bs += x; cout << Bs << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
