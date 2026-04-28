#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;

void solve() {
  int N;
  cin >> N;

  set<string> title, spoken;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    title.insert(s);
  }

  int M;
  cin >> M;
  for (int i = 1; i <= M; i++) {
    string s;
    cin >> s;
    if (title.count(s)) spoken.insert(s);

    if (2 * spoken.size() >= N) return cout << i << '\n', void();
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
