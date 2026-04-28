#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
vector<string> ans;
string cur = "1";

int eval() {
  int e1 = 0, e2 = 0, op = -1;
  for (int i = 0; i < cur.size(); i++) {
    if (cur[i] == ' ') continue;
    if (cur[i] == '+' || cur[i] == '-') {
      if (op == 0) e1 += e2, e2 = 0;
      if (op == 1) e1 -= e2, e2 = 0;
      op = cur[i] == '-';
    }
    else {
      if (op == -1) e1 = e1 * 10 + cur[i] - '0';
      else e2 = e2 * 10 + cur[i] - '0';
    }
  }
  if (op == 0) e1 += e2, e2 = 0;
  if (op == 1) e1 -= e2, e2 = 0;
  return e1;
}

void dfs(int i) {
  if (i == n) {
    if (eval() == 0) ans.push_back(cur);
    return;
  }

  cur.push_back(' '); cur.push_back(i + 1 + '0');
  dfs(i + 1);
  cur.pop_back(); cur.pop_back();

  cur.push_back('+'); cur.push_back(i + 1 + '0');
  dfs(i + 1);
  cur.pop_back(); cur.pop_back();

  cur.push_back('-'); cur.push_back(i + 1 + '0');
  dfs(i + 1);
  cur.pop_back(); cur.pop_back();
}

void solve() {
  ans.clear();

  cin >> n;
  dfs(1);
  for (auto& e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    solve();
    if (i != t) cout << '\n';
  }
}
