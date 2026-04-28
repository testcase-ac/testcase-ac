#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string a[2000];

bool is_trio(string& i, string& j, string& k) {
  bool b1 = (i[0] == j[0] && j[0] == k[0]) || (i[0] != j[0] && j[0] != k[0] && i[0] != k[0]);
  bool b2 = (i[1] == j[1] && j[1] == k[1]) || (i[1] != j[1] && j[1] != k[1] && i[1] != k[1]);
  bool b3 = (i[2] == j[2] && j[2] == k[2]) || (i[2] != j[2] && j[2] != k[2] && i[2] != k[2]);
  bool b4 = (i[3] == j[3] && j[3] == k[3]) || (i[3] != j[3] && j[3] != k[3] && i[3] != k[3]);
  return b1 && b2 && b3 && b4;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  long long ans = 0;
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) for (int k = j + 1; k < n; k++) {
    ans += is_trio(a[i], a[j], a[k]);
  }
  cout << ans << '\n';
}
