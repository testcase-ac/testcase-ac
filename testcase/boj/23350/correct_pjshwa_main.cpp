#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int prio_cnt[MAX + 1];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  assert(1 <= m && m <= n && n <= 100);

  queue<pii> rail;
  for (int i = 0; i < n; i++) {
    int pi, wi;
    cin >> pi >> wi;
    prio_cnt[pi]++;
    assert(1 <= pi && pi <= m && 1 <= wi && wi <= 100);

    rail.push({pi, wi});
  }

  int ans = 0;
  stack<int> c, temp;
  while (!rail.empty()) {
    auto [pi, wi] = rail.front();
    rail.pop();

    if (pi != m) {
      rail.push({pi, wi});
      ans += wi;
      continue;
    }

    while (!c.empty() && c.top() < wi) {
      ans += c.top();
      temp.push(c.top());
      c.pop();
    }
    c.push(wi);
    ans += wi;
    while (!temp.empty()) {
      ans += temp.top();
      c.push(temp.top());
      temp.pop();
    }

    if (!--prio_cnt[pi]) {
      m--;
      while (!c.empty()) c.pop();
    }
  }

  cout << ans << '\n';
}
