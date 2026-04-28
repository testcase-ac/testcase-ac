#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[1000];
int b[1000];
int main() {
  fast_io();

  int k, m, n;
  cin >> k >> m >> n;
  for (int i = 0; i < m; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];

  long long pf;
  vector<long long> apf{0}, bpf{0};
  for (int d = 1; d < m; d++) {
    pf = 0;
    for (int i = 0; i < d; i++) pf += a[i];
    for (int i = 0; i < m; i++) {
      apf.push_back(pf);
      pf = pf + a[(i + d) % m] - a[i];
    }
  }

  pf = 0;
  for (int i = 0; i < m; i++) pf += a[i];
  apf.push_back(pf);

  for (int d = 1; d < n; d++) {
    pf = 0;
    for (int i = 0; i < d; i++) pf += b[i];
    for (int i = 0; i < n; i++) {
      bpf.push_back(pf);
      pf = pf + b[(i + d) % n] - b[i];
    }
  }

  pf = 0;
  for (int i = 0; i < n; i++) pf += b[i];
  bpf.push_back(pf);

  // sort(apf.begin(), apf.end());
  sort(bpf.begin(), bpf.end());

  long long res, ans = 0;
  for (auto& ap : apf) {
    res = upper_bound(bpf.begin(), bpf.end(), k - ap) - lower_bound(bpf.begin(), bpf.end(), k - ap);
    ans += res;
  }
  cout << ans << '\n';
}
