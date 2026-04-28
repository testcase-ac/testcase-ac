#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string C(int n) {
  if (n == 1) return "1";

  string ret = C(n / 2);
  if (n & 1) return ret + "d+1+";
  else return ret + "d+";
}

void solve() {
  int N; cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  stack<string> ops; int acc = 0;
  for (int i = N - 1; i >= 0; --i) {
    A[i] += acc;
    string op = C(A[i]);
    ops.push(op);

    for (char& x : op) {
      if (x == '+') ++acc;
    }
  }

  while (!ops.empty()) {
    cout << ops.top();
    ops.pop();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
