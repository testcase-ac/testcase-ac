#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, s;
  cin >> n;
  priority_queue<int, vector<int>, greater<int>> pq;

  while (n--) {
    cin >> s;
    pq.push(s);
  }

  int ans = 0, c1, c2;
  while (pq.size() > 1) {
    c1 = pq.top();
    pq.pop();
    c2 = pq.top();
    pq.pop();
    ans = ans + c1 + c2;
    pq.push(c1 + c2);
  }

  cout << ans << '\n';
}
