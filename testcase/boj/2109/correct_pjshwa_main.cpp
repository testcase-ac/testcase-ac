#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

pii sch[10'000];
int main() {
  int n, d, p;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> p >> d;
    sch[i] = {d, p};
  }
  sort(sch, sch + n);

  priority_queue<int> pq;
  int days = sch[n - 1].first, k = n - 1, ans = 0;

  while (days) {
    while (k >= 0 && sch[k].first >= days) pq.push(sch[k--].second);

    if (!pq.empty()) {
      ans += pq.top();
      pq.pop();
    }
    days--;
  }

  cout << ans;
}
