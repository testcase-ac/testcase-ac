#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int x, a[50];
  for (int i = 0; i < 50; i++) cin >> a[i];
  cin >> x;

  int rank;
  for (int i = 1; i <= 50; i++) {
    if (x == a[i - 1]) rank = i;
  }

  if (1 <= rank && rank <= 5) cout << "A+";
  if (6 <= rank && rank <= 15) cout << "A0";
  if (16 <= rank && rank <= 30) cout << "B+";
  if (31 <= rank && rank <= 35) cout << "B0";
  if (36 <= rank && rank <= 45) cout << "C+";
  if (46 <= rank && rank <= 48) cout << "C0";
  if (49 <= rank && rank <= 50) cout << "F";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
