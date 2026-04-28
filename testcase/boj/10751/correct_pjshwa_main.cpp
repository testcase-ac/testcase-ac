#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e5;
ll dl[MAX], dr[MAX];

int main() {
  int n;
  string s;
  cin >> n >> s;

  dl[0] = s[0] == 'C';
  for (int i = 1; i < n; i++) dl[i] = dl[i - 1] + (s[i] == 'C');

  dr[n - 1] = s[n - 1] == 'W';
  for (int i = n - 2; i >= 0; i--) dr[i] = dr[i + 1] + (s[i] == 'W');

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'O') ans += dl[i] * dr[i];
  }
  cout << ans << '\n';
}
