#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string tmp; getline(cin, tmp);
  int N; cin >> N;
  set<string> W;
  for (int i = 0; i < N; ++i) {
    string s; cin >> s;
    if (s == "dongho") return cout << "dongho\n", void();
    W.insert(s);
  }

  int M; cin >> M;
  while (M--) {
    string s; cin >> s;
    if (W.count(s)) W.erase(s);
  }

  if (W.empty()) cout << "swi\n";
  else if (W.count("bumin")) cout << "bumin\n";
  else if (W.count("cake")) cout << "cake\n";
  else if (W.count("lawyer")) cout << "lawyer\n";
  else cout << *W.begin() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
