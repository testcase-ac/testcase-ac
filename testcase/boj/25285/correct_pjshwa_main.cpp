#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int H, W;
  cin >> H >> W;

  double bmi = 10000.0 * W / H / H;
  int rank;
  if (H < 140.1) rank = 6;
  else if (H < 146) rank = 5;
  else if (H < 159) rank = 4;
  else if (H < 161) {
    if (bmi < 16 || bmi >= 35) rank = 4;
    else rank = 3;
  }
  else if (H < 204) {
    if (bmi < 16 || bmi >= 35) rank = 4;
    else if (bmi < 18.5 || bmi >= 30) rank = 3;
    else if (bmi < 20 || bmi >= 25) rank = 2;
    else rank = 1;
  }
  else rank = 4;

  cout << rank << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
