#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[10], s[10];
int ans;

void dfs(int i) {
  if (i == 10) {
    int cnt = 0;
    for (int j = 0; j < 10; j++) if (s[j] == a[j]) cnt++;
    if (cnt >= 5) ans++;
    return;
  }

  for (int w = 1; w <= 5; w++) {
    if (i >= 2 && s[i - 1] == s[i - 2] && s[i - 1] == w) continue;
    s[i] = w;
    dfs(i + 1);
  }
}

int main() {
  fast_io();

  for (int i = 0; i < 10; i++) cin >> a[i];
  dfs(0);
  cout << ans << '\n';
}
