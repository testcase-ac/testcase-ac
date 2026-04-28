#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll a[1000];
ll b[1000];
int main() {
  fast_io();

  int n, an, bn;
  cin >> n;

  cin >> an;
  cin >> a[0];
  for (int i = 1; i < an; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
  }

  cin >> bn;
  cin >> b[0];
  for (int i = 1; i < bn; i++) {
    cin >> b[i];
    b[i] += b[i - 1];
  }

  vector<ll> vpa, vpb;
  for (int i = 0; i < an; i++) vpa.push_back(a[i]);
  for (int i = 0; i < an; i++) {
    for (int j = i + 1; j < an; j++) vpa.push_back(a[j] - a[i]);
  }
  for (int i = 0; i < bn; i++) vpb.push_back(b[i]);
  for (int i = 0; i < bn; i++) {
    for (int j = i + 1; j < bn; j++) vpb.push_back(b[j] - b[i]);
  }
  sort(vpb.begin(), vpb.end());

  ll ans = 0;
  for (auto el : vpa) ans += upper_bound(vpb.begin(), vpb.end(), n - el) - lower_bound(vpb.begin(), vpb.end(), n - el);
  cout << ans << '\n';
}
