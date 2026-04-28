#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;

  string s;
  cin >> s;

  int dt = 0;
  for (int i = 0; i < n / 2; i++) {
    if (s[i] == 's') dt++;
    else dt--;
  }
  if (dt == 0) return cout << "1\n" << n / 2, 0;

  for (int i = n / 2; i < n; i++) {
    if (s[i] == 's') dt++;
    else dt--;
    if (s[i - n / 2] == 's') dt--;
    else dt++;

    if (dt == 0) return cout << "2\n" << i - n / 2 + 1 << ' ' << i + 1, 0;
  }
}
