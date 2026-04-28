#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc; string note, tonality;
vector<pair<string, int>> table = {
  {"A", 0}, {"A#", 1}, {"Bb", 1}, {"B", 2}, {"C", 3}, {"C#", 4}, {"Db", 4},
  {"D", 5}, {"D#", 6}, {"Eb", 6}, {"E", 7}, {"F", 8},
  {"F#", 9}, {"Gb", 9}, {"G", 10}, {"G#", 11}, {"Ab", 11}
};

void solve() {
  cout << "Case " << ++tc << ": ";

  int idx;
  for (auto& [s, i] : table) {
    if (s == note) idx = i;
  }
  int cnt = 0; string alt_note;
  for (auto& [s, i] : table) {
    if (i != idx) continue;
    ++cnt;
    if (s != note) alt_note = s;
  }

  if (cnt == 1) cout << "UNIQUE\n";
  else cout << alt_note << ' ' << tonality << '\n';
}

int main() {
  fast_io();

  while (cin >> note) {
    cin >> tonality;
    solve();
  }
}
