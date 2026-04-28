#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;

  int add[40];
  fill(add, add + 40, 1);
  int score = 0, i = 0;

  for (int round = 1; round <= 9; round++) {
    int cur = 0;

    if (s[i] == 'S') {
      add[i + 1]++;
      add[i + 2]++;
      cur += 10 * add[i];
      i++;
    }

    else {

      int prev = s[i] == '-' ? 0 : s[i] - '0';
      cur += prev * add[i];
      i++;

      if (s[i] == 'P') {
        add[i + 1]++;
        cur += (10 - prev) * add[i];
      }
      else if (s[i] != '-') cur += (s[i] - '0') * add[i];
      i++;

    }

    score += cur;

  }

  // Round 10
  if (s[i] == 'S') {
    int cur = 10 * add[i], prev;

    if (s[i + 1] == 'S') cur += 10 * add[i + 1];
    else if (s[i + 1] != '-') {
      prev = s[i + 1] - '0';
      cur += prev * add[i + 1];
    }
    
    if (s[i + 2] == 'S') cur += 10 * add[i + 2];
    else if (s[i + 2] == 'P') cur += (10 - prev) * add[i + 2];
    else if (s[i + 2] != '-') cur += (s[i + 2] - '0') * add[i + 2];

    score += cur;
  }
  else {
    int prev = s[i] == '-' ? 0 : s[i] - '0';
    int cur = prev * add[i];

    if (s[i + 1] == 'P') {
      cur += (10 - prev) * add[i + 1];
      if (s[i + 2] == 'S') cur += 10 * add[i + 2];
      else if (s[i + 2] != '-') cur += (s[i + 2] - '0') * add[i + 2];
    }
    else if (s[i + 1] != '-') cur += (s[i + 1] - '0') * add[i + 1];
    score += cur;
  }

  cout << score << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
