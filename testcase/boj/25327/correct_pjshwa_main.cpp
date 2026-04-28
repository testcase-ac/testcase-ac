#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e4;

void solve() {
  int n, m;
  cin >> n >> m;

  int C[3][3][3] = {0};
  for (int i = 0; i < n; i++) {
    string s, f, c;
    cin >> s >> f >> c;

    int si = s == "kor" ? 0 : s == "eng" ? 1 : 2;
    int fi = f == "apple" ? 0 : f == "pear" ? 1 : 2;
    int ci = c == "red" ? 0 : c == "blue" ? 1 : 2;
    C[si][fi][ci]++;
  }

  while (m--) {
    string s, f, c;
    cin >> s >> f >> c;

    int ss, se, fs, fe, cs, ce;
    
    if (s == "-") ss = 0, se = 2;
    else if (s == "kor") ss = 0, se = 0;
    else if (s == "eng") ss = 1, se = 1;
    else ss = 2, se = 2;

    if (f == "-") fs = 0, fe = 2;
    else if (f == "apple") fs = 0, fe = 0;
    else if (f == "pear") fs = 1, fe = 1;
    else fs = 2, fe = 2;

    if (c == "-") cs = 0, ce = 2;
    else if (c == "red") cs = 0, ce = 0;
    else if (c == "blue") cs = 1, ce = 1;
    else cs = 2, ce = 2;

    int cnt = 0;
    for (int si = ss; si <= se; si++)
      for (int fi = fs; fi <= fe; fi++)
        for (int ci = cs; ci <= ce; ci++)
          cnt += C[si][fi][ci];

    cout << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
