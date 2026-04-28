#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(false);
}

int numInCoordinate(int r, int c) {
  int cc = max(abs(r), abs(c));
  int base = (2 * cc + 1) * (2 * cc + 1);
  if (r == cc) return base - cc + c;
  else if (c == -cc) return base - 3 * cc + r;
  else if (r == -cc) return base - 5 * cc - c;
  else return base - 7 * cc - r;
}

int main() {
  int r1, r2, c1, c2;
  cin >> r1 >> c1 >> r2 >> c2;

  vector<string> ans;
  string s;
  int mx = 0, sz;

  for (int i = r1; i <= r2; i++) {
    for (int j = c1; j <= c2; j++) {
      s = to_string(numInCoordinate(i, j));
      sz = s.size();
      mx = max(mx, sz);
      ans.push_back(s);
    }
  }

  for (int i = 0; i <= r2 - r1; i++) {
    for (int j = 0; j <= c2 - c1; j++) {
      s = ans[j + (c2 - c1 + 1) * i];
      sz = s.size();
      for (int k = 0; k < mx - sz; k++) cout << ' ';
      cout << s << ' ';
    }
    cout << '\n';
  }
}
