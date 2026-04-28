#include <bits/stdc++.h>
#define tii tuple<int, int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, a, c, b;
const ll MAX = 3e9;
tii piles[20000];

ll pilesCnt(ll v) {
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    tie(a, c, b) = piles[i];
    if (v >= a) ans += (min((ll)c, v) - a) / b + 1;
  }
  return ans;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> c >> b;
    piles[i] = {a, c, b};
  }

  ll left = 0;
  ll right = MAX;
  ll mid = (left + right) / 2;
  while (left < right) {
    if (pilesCnt(mid) % 2) right = mid;
    else left = mid + 1;
    mid = (left + right) / 2;
  }

  if (mid == MAX) cout << "NOTHING";
  else cout << mid << ' ' << pilesCnt(mid) - pilesCnt(mid - 1);
}
