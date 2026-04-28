#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> ops(N + 1, 1); int plus = 0;
  for (int j = 2; j <= N; ++j) {
    cout << "? 1 * " << j << endl;
    string ret; cin >> ret;
    if (ret == "-") ops[j] = -1;
    else plus = j;
  }

  if (plus) {
    cout << "? 1 + " << plus << endl;
    string ret; cin >> ret;
    if (ret == "-") {
      for (int i = 1; i <= N; ++i) ops[i] *= -1;
    }
  } else {
    cout << "? 2 + 3" << endl;
    string ret; cin >> ret;
    if (ret == "+") {
      for (int i = 1; i <= N; ++i) ops[i] *= -1;
    }
  }

  cout << "!";
  for (int i = 1; i <= N; ++i) {
    if (ops[i] == 1) cout << " +";
    else cout << " -";
  }
  cout << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
