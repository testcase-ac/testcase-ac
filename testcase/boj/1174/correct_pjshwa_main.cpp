#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<ll> decr;

void dfs(string num, int cnt) {
  if (cnt == 0) {
    decr.push_back(stoll(num));
    return;
  }

  if (num.empty()) for (int i = 0; i <= 9; i++) dfs(num + to_string(i), cnt - 1);
  else for (int i = 0; i < num[num.size() - 1] - '0'; i++) dfs(num + to_string(i), cnt - 1);
}

void solve() {
  int n;
  cin >> n;

  for (int i = 1; i <= 10; i++) dfs("", i);
  sort(decr.begin(), decr.end());

  if (n > decr.size()) cout << "-1\n";
  else cout << decr[n - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
