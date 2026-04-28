#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e6;
string A[MAX];

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve_odd(int n) {
  int dt = 0;
  for (int i = 0; i < 2 * n; i += 2) {
    if (A[i] == "O") dt++;
    if (A[i + 1] == "O") dt--;
  }
  cout << (dt <= 0) << '\n';
}

void solve_even(int n) {
  bool allx = true;
  for (int i = 0; i < n; i++) allx &= (A[i] == "X");
  if (allx) return cout << "3\n", void();

  int dt = 0;
  for (int i = 0; i < 2 * n; i += 2) {
    if (A[i] == "O") dt++;
    if (A[i + 1] == "O") dt--;
  }
  if (dt > 0) return cout << "0\n", void();

  vector<int> po(2 * n + 1), pe(2 * n + 1);
  for (int i = 0; i < 2 * n; i += 2) {
    pe[i + 1] = i > 0 ? pe[i - 1] : 0;
    if (A[i] == "O" && A[i + 1] == "X") pe[i + 1]++;
    if (A[i] == "X" && A[i + 1] == "O") pe[i + 1]--;
  }
  for (int i = 1; i < 2 * n; i += 2) {
    po[i + 1] = po[i - 1];
    if (A[i] == "O" && A[i + 1] == "X") po[i + 1]++;
    if (A[i] == "X" && A[i + 1] == "O") po[i + 1]--;
  }

  for (int i = 1; i < 2 * n; i++) {
    int cur;
    if (i & 1) {
      cur = pe[2 * n - 1] - pe[i];
      cur += po[i - 1];
    }
    else {
      cur = pe[2 * n - 1] - pe[i + 1];
      cur += po[i - 2];

      if (A[i - 1] == "O" && A[i + 1] == "X") cur++;
      if (A[i - 1] == "X" && A[i + 1] == "O") cur--;
    }

    if (A[i] == "O" && A[0] == "X") cur++;
    if (A[i] == "X" && A[0] == "O") cur--;
    if (cur > 0) return cout << "1\n", void();
  }

  cout << "2\n";
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < 2 * n; i++) cin >> A[i];

  if (n & 1) solve_odd(n);
  else solve_even(n);
}
