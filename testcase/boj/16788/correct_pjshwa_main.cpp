#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pii a[MAX];
bool sank[MAX];

int main() {
  fast_io();

  int n, x;
  cin >> n;
  set<int> heights;
  for (int i = 0; i < n; i++) cin >> x, heights.insert(x), a[i] = {x, i};
  sort(a, a + n);

  if (heights.size() == 1 && heights.count(0)) return cout << "0\n", 0;

  int ans = 1;
  int cursor = 0, cnt = 1;
  for (int height : heights) {
    while (cursor < n && a[cursor].first <= height) {
      int idx = a[cursor].second;
      sank[idx] = true;
      cnt--;
      if (idx > 0 && !sank[idx - 1]) cnt++;
      if (idx < n - 1 && !sank[idx + 1]) cnt++;
      cursor++;
    }
    ans = max(ans, cnt);
  }
  cout << ans << '\n';
}
