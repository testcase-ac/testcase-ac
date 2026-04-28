#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int N;
  cin >> N;

  ll ans = 0, zc = 0, oc = 0;
  priority_queue<ll> pos;
  priority_queue<ll, vector<ll>, greater<ll>> neg;
  for (int i = 0; i < N; ++i) {
    int x;
    cin >> x;
    if (x == 0) zc++;
    else if (x == 1) oc++;
    else if (x > 0) pos.push(x);
    else neg.push(x);
  }

  while (pos.size() >= 2) {
    ll x = pos.top(); pos.pop();
    ll y = pos.top(); pos.pop();
    ans += x * y;
  }
  if (pos.size() == 1) {
    ll x = pos.top(); pos.pop();
    ans += x;
  }
  ans += oc;

  while (neg.size() >= 2) {
    ll x = neg.top(); neg.pop();
    ll y = neg.top(); neg.pop();
    ans += x * y;
  }
  if (neg.size() == 1 && zc == 0) {
    ll x = neg.top(); neg.pop();
    ans += x;
  }

  cout << ans << '\n';
}
