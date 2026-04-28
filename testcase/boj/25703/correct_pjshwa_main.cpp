#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  cout << "int a;\n";
  cout << "int *ptr = &a;\n";
  for (int i = 2; i <= N; i++) {
    if (i == 2) cout << "int **ptr2 = &ptr;\n";
    else {
      cout << "int ";
      for (int j = 0; j < i; j++) cout << "*";
      cout << "ptr" << i << " = &ptr" << i - 1 << ";\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
