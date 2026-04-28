#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

pii res(int a0, int a1) {
  if (a0 == 1 && a1 == 2) return {3, 0};
  if (a0 == 2 && a1 == 1) return {3, 0};

  if (a0 == a1) return {2, a0};

  if (a0 < a1) swap(a0, a1);
  return {1, a0 * 10 + a1};
}

int s0, s1, r0, r1;
void solve() {
  pii S = res(s0, s1), R = res(r0, r1);
  if (S > R) cout << "Player 1 wins.\n";
  else if (S < R) cout << "Player 2 wins.\n";
  else cout << "Tie.\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> s0 >> s1 >> r0 >> r1;
    if (s0 == 0 && s1 == 0 && r0 == 0 && r1 == 0) break;
    solve();
  }
}
