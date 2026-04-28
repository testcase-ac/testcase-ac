#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, ai, tcnt = 0;
  cin >> n >> m;

  deque<int> d;
  for (int i = 1; i <= n; i++) d.push_back(i);
  for (int i = 1; i <= m; i++) {
    cin >> ai;
    int cnt = 0;
    while (d.front() != ai) {
      d.push_back(d.front());
      d.pop_front();
      cnt++;
    }
    tcnt += min(cnt, n - cnt);
    d.pop_front();
    n--;
  }
  cout << tcnt;
}
