#include <bits/stdc++.h>
using namespace std;

bool broken[10];
int main() {
  int n, m, k;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    cin >> k;
    broken[k] = true;
  }

  int mmoves = abs(n - 100);
  for (int i = 0; i <= 1e6 + 1; i++) {
    string s = to_string(i);
    int sz = s.size();
    bool able = true;
    for (int j = 0; j < sz; j++) {
      if (broken[s[j] - '0']) able = false;
    }
    if (!able) continue;
    mmoves = min(mmoves, sz + abs(n - i));
  }
  cout << mmoves << '\n';
  return 0;
}
