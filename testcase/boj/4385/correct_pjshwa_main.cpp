#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MOD = 1000;
int M[MAXN], R[10];

// 100 means halt
// 2dn means set register d to n (between 0 and 9)
// 3dn means add n to register d
// 4dn means multiply register d by n
// 5ds means set register d to the value of register s
// 6ds means add the value of register s to register d
// 7ds means multiply register d by the value of register s
// 8da means set register d to the value in RAM whose address is in register a
// 9sa means set the value in RAM whose address is in register a to the value of register s
// 0ds means goto the location in register d unless register s contains 0

void print_registers() {
  cout << "R = {";
  for (int i = 0; i < 10; ++i) {
    cout << R[i];
    if (i < 9) cout << ", ";
  }
  cout << "}\n";
}

void solve() {
  int N = 0, r;
  while (cin >> r) M[N++] = r;

  int i = 0, ans = 0;
  while (1) {
    int op = M[i] / 100, f1 = (M[i] / 10) % 10, f2 = M[i] % 10;

    ++i; ++ans;
    if (op == 0) {
      if (R[f2] != 0) i = R[f1];
    } else if (op == 1) {
      break;
    } else if (op == 2) {
      R[f1] = f2;
    } else if (op == 3) {
      R[f1] = (R[f1] + f2) % MOD;
    } else if (op == 4) {
      R[f1] = (R[f1] * f2) % MOD;
    } else if (op == 5) {
      R[f1] = R[f2];
    } else if (op == 6) {
      R[f1] = (R[f1] + R[f2]) % MOD;
    } else if (op == 7) {
      R[f1] = (R[f1] * R[f2]) % MOD;
    } else if (op == 8) {
      R[f1] = M[R[f2]];
    } else if (op == 9) {
      M[R[f2]] = R[f1];
    }

    // print_registers();
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
