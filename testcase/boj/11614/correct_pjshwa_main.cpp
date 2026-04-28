#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

void solve() {
  vector<int> sv;
  string s;
  getline(cin, s);
  for (auto& w : split(s, " ")) sv.push_back(w.size());
  for (int i = 1; i < sv.size(); i++) sv[i] += sv[i - 1] + 1;

  int a, b;
  cin >> a >> b;
  for (int i = a; i <= b; i++) {
    int w = 0, cur = sv[0];
    while (1) {
      int idx = w == 0 ? i : sv[w - 1] + i + 1;
      auto it = upper_bound(sv.begin(), sv.end(), idx);
      w = it - sv.begin();
      // cout << "idx: " << idx << ", w: " << w << ", cur: " << cur << '\n';
      if (it == sv.end()) break;
      // cout << sv[w] - sv[w - 1] - 1 << endl;
      cur += sv[w] - sv[w - 1];
    }
    cout << cur << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
