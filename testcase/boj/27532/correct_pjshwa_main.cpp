#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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
  int N; cin >> N;
  vector<int> A(N);

  function<int(string)> stoi_p = [](string s) {
    int ret = 0;
    for (char c : s) ret = ret * 10 + c - '0';
    return ret;
  };

  for (int i = 0; i < N; i++) {
    string T; cin >> T;
    vector<string> tokens = split(T, ":");
    A[i] = (stoi_p(tokens[0]) - 1) * 60 + stoi_p(tokens[1]);
  }

  int ans = N;
  for (int R = 1; R <= 720; R++) {
    set<int> u;
    for (int i = 0; i < N; i++) {
      int t = A[i] - (i * R % 720);
      if (t < 0) t += 720;
      u.insert(t);
    }
    ans = min(ans, (int)u.size());
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
