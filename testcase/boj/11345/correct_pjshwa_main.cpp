#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

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

const int MAX = 1e6;
int t1[MAX + 1], t2[MAX + 1];

void solve() {
  int N;
  cin >> N;

  memset(t1, 0, sizeof(t1));
  memset(t2, 0, sizeof(t2));

  int x;
  for (int i = 0; i < N; i++) {
    cin >> x;
    t1[x]++;
  }
  for (int i = 0; i < N; i++) {
    cin >> x;
    t2[x]++;
  }

  map<int, int> t;
  for (int i = 1; i <= MAX; i++) {
    if (t1[i]) t[t1[i]]++;
    if (t2[i]) t[t2[i]]--;
  }

  for (auto& [k, v] : t) {
    if (v != 0) return cout << "you've messed up, Cornell\n", void();
  }

  cout << "what a lovely party\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
