#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
ll o[MAX + 1], d[MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> o[i] >> d[i];

  ll md = 0, cd = 0, co = 0;
  for (int i = 1; i <= n; i++) {
    co += o[i];
    cd += d[i];
    md = max(md, cd - co);
  }

  ll cs = 0;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    cs += (d[i] - o[i]);
    if (md == cs) cout << i << endl;
  }

  cout << ans;
}
