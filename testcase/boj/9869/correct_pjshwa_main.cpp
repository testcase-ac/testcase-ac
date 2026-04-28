#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, g, d;
  cin >> n;
  vector<pii> wait;
  priority_queue<int> pq;
  for (int i = 0; i < n; i++) {
    cin >> g >> d;
    wait.push_back({-d, g});
  }
  sort(wait.begin(), wait.end());

  ll ans = 0;
  int cursor = 0;
  for (int t = 10000; t > 0; t--) {
    while (cursor < n && -wait[cursor].first >= t) {
      pq.push(wait[cursor].second);
      cursor++;
    }
    if (!pq.empty()) {
      ans += pq.top();
      pq.pop();
    }
  }

  cout << ans << endl;
}
