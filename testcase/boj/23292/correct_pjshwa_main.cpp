#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int br(string a, string b) {
  int a1 = 0, a2 = 0, a3 = 0;
  for (int i = 0; i < 4; i++) {
    a1 += (a[i] - b[i]) * (a[i] - b[i]);
  }
  for (int i = 4; i < 6; i++) {
    a2 += (a[i] - b[i]) * (a[i] - b[i]);
  }
  for (int i = 6; i < 8; i++) {
    a3 += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return a1 * a2 * a3;
}

int main() {
  fast_io();

  string bday;
  int n;
  cin >> bday >> n;

  int my = 0;
  string mday;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    int cy = br(bday, s);
    if (my < cy) {
      my = cy;
      mday = s;
    }
    else if (my == cy) mday = min(mday, s);
  }

  cout << mday << '\n';
}
