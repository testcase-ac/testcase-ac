#include <bits/stdc++.h>
typedef long long ll;
#define tll tuple<ll, ll, ll>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll n;
tll ps[MAX + 1];

ll f(ll prio) {
  ll o = 0;
  for (int i = 0; i < n; i++) {
    ll rem = get<1>(ps[i]);
    ll dprio = min(rem, max(0LL, get<2>(ps[i]) - prio + 1));
    o += dprio;
  }
  return o;
}

int main() {
  fast_io();

  ll Q, ai, bi, ci, tc;
  cin >> Q >> n;

  for (int i = 0; i < n; i++) {
    cin >> ai >> bi >> ci;
    ps[i] = {ai, bi, ci + 1e12};
  }

  for (int i = 0; i < Q; i++) {
    cin >> tc;

    ll left = 1;
    ll right = 1e18;
    ll mid = (left + right) / 2;

    while (left < right) {
      if (f(mid) < tc) right = mid;
      else left = mid + 1;

      mid = (left + right) / 2;
    }

    vector<ll> candidates;
    for (int i = 0; i < n; i++) {
      ll cprio = get<2>(ps[i]);
      if (mid - 1 <= cprio && mid - 1 > cprio - get<1>(ps[i])) candidates.push_back(get<0>(ps[i]));
    }
    sort(candidates.begin(), candidates.end());
    cout << candidates[tc - f(mid) - 1] << '\n';
  }
}
