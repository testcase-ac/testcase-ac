#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N; string OS, S;

bool emplace(int D) {
  vector<int> nl(N, -1), nr(N, -1);

  int l = -1;
  for (int i = 0; i < N; i++) {
    if (S[i] == '1') l = i;
    nl[i] = l;
  }

  int r = -1;
  for (int i = N - 1; i >= 0; i--) {
    if (S[i] == '1') r = i;
    nr[i] = r;
  }

  for (int i = 0; i < N; i++) {
    bool pl = nl[i] == -1 || nl[i] + D <= i;
    bool pr = nr[i] == -1 || nr[i] - D >= i;
    if (pl && pr) {
      S[i] = '1';
      return true;
    }
  }

  return false;
}

bool emplace_twice(int D) {
  if (!emplace(D)) return false;
  return emplace(D);
}

void solve() {
  cin >> N >> OS;

  int left = 1, right = N + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    S = OS;

    if (emplace_twice(mid)) left = mid + 1;
    else right = mid;
  }

  int l = -1, ans = left - 1;
  for (int i = 0; i < N; i++) {
    if (S[i] == '1') {
      if (l != -1) ans = min(ans, i - l);
      l = i;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
