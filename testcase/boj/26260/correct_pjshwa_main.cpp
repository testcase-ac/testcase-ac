#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<int> B;
void f(int s, int e) {
  if (s == e) {
    cout << B[s] << ' ';
    return;
  }

  int m = (s + e) / 2;
  f(s, m - 1);
  f(m + 1, e);
  cout << B[m] << ' ';
}

void solve() {
  int N;
  cin >> N;
  
  int x;
  for (int i = 0; i < N; i++) {
    cin >> x;
    if (x == -1) continue;
    B.push_back(x);
  }
  cin >> x;
  B.push_back(x);
  sort(B.begin(), B.end());

  f(0, B.size() - 1);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
