#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

pii hs[200000];
int main() {
  fast_io();

  int n;
  cin >> n;

  int d, c;

  for (int i = 0; i < n; i++) {
    cin >> d >> c;
    hs[i] = {d, c};
  }
  sort(hs, hs + n);

  int ctime = n;
  long long ans = 0;

  priority_queue<int> selector;
  int pt = n - 1;
  while (ctime) {
    while (pt >= 0 && hs[pt].first >= ctime) {
      selector.push(hs[pt].second);
      pt--;
    }
    if (!selector.empty()) {
      ans += selector.top();
      selector.pop();
    }
    ctime--;
  }

  cout << ans << '\n';
}
