

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50'000;
const char c1[] = {'h', 'b', 'c', 'n', 'o', 'f', 'p', 's', 'k', 'v', 'y', 'i', 'w', 'u'};
const char c2[][3] = {
  "ba", "ca", "ga", "la", "na", "pa", "ra", "ta", "db", "nb", "pb", "rb", "sb", "tb", "yb", "ac",
  "sc", "tc", "cd", "gd", "md", "nd", "pd", "be", "ce", "fe", "ge", "he", "ne", "re", "se", "te",
  "xe", "cf", "hf", "rf", "ag", "hg", "mg", "rg", "sg", "bh", "rh", "th", "bi", "li", "ni", "si",
  "ti", "bk", "al", "cl", "fl", "tl", "am", "cm", "fm", "pm", "sm", "tm", "cn", "in", "mn", "rn",
  "sn", "zn", "co", "ho", "mo", "no", "po", "np", "ar", "br", "cr", "er", "fr", "ir", "kr", "lr",
  "pr", "sr", "zr", "as", "cs", "ds", "es", "hs", "os", "at", "mt", "pt", "au", "cu", "eu", "lu",
  "pu", "ru", "lv", "dy"
};

bool d[MAX + 1];

void solve() {
  string s; cin >> s;
  int n = s.size();

  fill(d, d + n + 1, false);
  d[0] = true;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 14; j++) {
      if (i >= 1 && s[i - 1] == c1[j]) d[i] |= d[i - 1];
    }
    for (int j = 0; j < 118; j++) {
      if (i >= 2 && s[i - 2] == c2[j][0] && s[i - 1] == c2[j][1]) d[i] |= d[i - 2];
    }
  }

  if (d[n]) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
