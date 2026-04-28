#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3660;
bool vis[2][MAX];

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

void solve() {
  string s;
  cin >> s;
  auto ss = split(s, ":");

  int e = stoi(ss[0]) * 60 + stoi(ss[1]);

  queue<tii> q;
  q.push({0, 0, 0});
  vis[0][0] = 1;

  while (!q.empty()) {
    auto [cstat, ctime, cstep] = q.front();
    q.pop();

    if (cstat == 1 && ctime == e) return cout << cstep << '\n', void();

    if (ctime + 10 < MAX && !vis[cstat][ctime + 10]) vis[cstat][ctime + 10] = 1, q.push({cstat, ctime + 10, cstep + 1});
    if (ctime + 60 < MAX && !vis[cstat][ctime + 60]) vis[cstat][ctime + 60] = 1, q.push({cstat, ctime + 60, cstep + 1});
    if (ctime + 600 < MAX && !vis[cstat][ctime + 600]) vis[cstat][ctime + 600] = 1, q.push({cstat, ctime + 600, cstep + 1});

    if (cstat == 0 && ctime == 0) {
      if (!vis[1][ctime + 30]) vis[1][ctime + 30] = 1, q.push({1, ctime + 30, cstep + 1});
    }
    else {
      if (!vis[1][ctime]) vis[1][ctime] = 1, q.push({1, ctime, cstep + 1});
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
