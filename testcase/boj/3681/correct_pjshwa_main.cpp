#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  string S;
  cin >> S;

  vector<int> d[20];
  int i = 0, l = 0, ml = 0, tot = 0;
  while (i < S.size()) {
    if (isdigit(S[i])) {
      int j = i;
      while (j < S.size() && isdigit(S[j])) j++;

      d[l].push_back(stoi(S.substr(i, j - i)));
      ml = max(ml, l);
      tot++;
      i = j;
    }
    if (S[i] == '[') l++, i++;
    if (S[i] == ',') i++;
    if (S[i] == ']') l--, i++;
  }

  for (int l = 0; l <= ml; l++) sort(d[l].begin(), d[l].end());

  int ans = tot;
  for (int l = ml; l >= 0; l--) for (int c : d[l]) {
    ll gr = c, gl = l, cur = tot;
    while (gl > ml) {
      if (gr & 1) break;
      gr /= 2;
      gl--;
    }

    for (int pl = gl; pl >= 0; pl--) {
      cur -= upper_bound(d[pl].begin(), d[pl].end(), gr) - lower_bound(d[pl].begin(), d[pl].end(), gr);
      gr *= 2;
    }
    ans = min((ll)ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
