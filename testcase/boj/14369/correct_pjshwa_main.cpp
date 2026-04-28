#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string s;
  cin >> s;

  map<char, int> t;
  for (int i = 0; i < s.size(); i++) t[s[i]]++;

  int ans[10] = {0};

  // Topological sort... sort of
  while (t['Z']) {
    ans[0]++;
    t['Z']--; t['E']--; t['R']--; t['O']--;
  }

  while (t['W']) {
    ans[2]++;
    t['T']--; t['W']--; t['O']--;
  }

  while (t['G']) {
    ans[8]++;
    t['E']--; t['I']--; t['G']--; t['H']--; t['T']--;
  }

  while (t['X']) {
    ans[6]++;
    t['S']--; t['I']--; t['X']--;
  }

  while (t['U']) {
    ans[4]++;
    t['F']--; t['O']--; t['U']--; t['R']--;
  }

  while (t['F']) {
    ans[5]++;
    t['F']--; t['I']--; t['V']--; t['E']--;
  }

  while (t['S']) {
    ans[7]++;
    t['S']--; t['E']--; t['V']--; t['E']--; t['N']--;
  }

  while (t['O']) {
    ans[1]++;
    t['O']--; t['N']--; t['E']--;
  }

  while (t['N']) {
    ans[9]++;
    t['N']--; t['I']--; t['N']--; t['E']--;
  }

  while (t['T']) {
    ans[3]++;
    t['T']--; t['H']--; t['R']--; t['E']--; t['E']--;
  }

  for (int i = 0; i < 10; i++) for (int j = 0; j < ans[i]; j++) cout << i;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
