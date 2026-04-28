#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

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

int ts2ep(string s) {
  auto su = split(s, ":");
  return stoi(su[0]) * 60 + stoi(su[1]);
}

void solve() {
  string st_str;
  cin >> st_str;
  int st = ts2ep(st_str);

  int a[6];
  for (int i = 0; i < 6; i++) cin >> a[i];

  int q;
  cin >> q;
  vector<pair<double, int>> queries(q);
  for (int i = 0; i < q; i++) {
    double t; string op;
    cin >> t >> op;

    int event;
    if (op == "^") event = -1;
    if (op == "10MIN") event = 10;
    if (op == "30MIN") event = 30;
    if (op == "50MIN") event = 50;
    if (op == "2HOUR") event = 120;
    if (op == "4HOUR") event = 240;
    if (op == "9HOUR") event = 540;

    queries[i] = {t, event};
  }
  sort(queries.begin(), queries.end());

  for (auto [t, event] : queries) {
    int area = st / 120;
    if (event == -1) a[area] = 0;
    else st = (st + event) % 720;
  }

  int ans = 0;
  for (int i = 0; i < 6; i++) ans += a[i];
  cout << min(100, ans) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
