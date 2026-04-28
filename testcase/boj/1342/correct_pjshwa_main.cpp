#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int ccnt[26], n, ans;

void dfs(int cpos, int pre) {
  if (cpos == n) {
    ans++;
    return;
  }

  for (int i = 0; i < 26; i++) {
    if (i != pre && ccnt[i]) {
      ccnt[i]--;
      dfs(cpos + 1, i);
      ccnt[i]++;
    }
  }
}

int main() {
  fast_io();

  string s;
  cin >> s;
  n = s.size();
  for (char c : s) ccnt[c - 'a']++;

  dfs(0, -1);
  cout << ans;
}
