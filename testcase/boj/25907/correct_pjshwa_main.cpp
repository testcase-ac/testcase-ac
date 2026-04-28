#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(int n) {
  cout << "? " << n << endl;
  int x;
  cin >> x;
  return x;
}

void solve() {
  int N;
  cin >> N;

  int left = 1, right = N + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    int ret = ask(mid);

    if (mid == ret * 2) return cout << "! " << mid << endl, void();

    if (mid > ret * 2) right = mid;
    else left = mid + 1;
  }
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
