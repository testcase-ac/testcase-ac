#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int to_int_100(string& s) {
  int pivot = s.find('.');
  return stoi(s.substr(0, pivot)) * 100 + stoi(s.substr(pivot + 1));
}

void solve() {
  int A[4], T;
  for (int i = 0; i < 4; ++i) {
    string x; cin >> x;
    A[i] = to_int_100(x);
  }
  sort(A, A + 4);

  string x; cin >> x;
  T = to_int_100(x) * 3;

  if (A[1] + A[2] + A[3] <= T) cout << "infinite\n";
  else if (A[0] + A[1] + A[2] > T) cout << "impossible\n";
  else {
    int ans = T - A[1] - A[2];
    cout << (ans / 100) << '.' << setw(2) << setfill('0') << (ans % 100) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
