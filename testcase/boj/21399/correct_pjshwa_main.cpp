#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e4;
ll v[MAX + 1], sl[MAX + 1], sr[MAX + 1];
bool lvis[MAX + 1], rvis[MAX + 1];
ll dl[MAX + 1], dr[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> v[i];

  sl[0] = v[0];
  for (int i = 1; i < n; i++) sl[i] = sl[i - 1] + v[i];
  sr[n - 1] = v[n - 1];
  for (int i = n - 2; i >= 0; i--) sr[i] = sr[i + 1] + v[i];

  memset(lvis, 0, sizeof lvis);
  memset(rvis, 0, sizeof rvis);
  memset(dl, 0, sizeof dl);
  memset(dr, 0, sizeof dr);

  priority_queue<pii> pqL, pqR;
  priority_queue<pii, vector<pii>, greater<pii>> uL, uR;
  for (int i = n - 2; i >= 0; i--) pqL.push({v[i], i});
  for (int i = 1; i < n; i++) pqR.push({v[i], i});

  ll lsum = 0, rsum = 0;
  for (int i = 0; i < n / 3; i++) {
    auto [v, j] = pqL.top(); pqL.pop();
    lvis[j] = 1;
    lsum += v;
    uL.push({v, j});
  }
  for (int i = 0; i < n / 3; i++) {
    auto [v, j] = pqR.top(); pqR.pop();
    rvis[j] = 1;
    rsum += v;
    uR.push({v, j});
  }

  for (int i = n - 2; i >= 0; i -= 3) {
    dl[i] = sl[i] - lsum;

    int ej = 0;
    for (int j = i; j > i - 3; j--) {
      if (lvis[j]) lsum -= v[j], ej++;
    }
    
    if (ej == 0) {
      while (uL.top().second > i - 3) uL.pop();
      assert(uL.size());

      auto [v, j] = uL.top(); uL.pop();
      lvis[j] = false;
      lsum -= v;
      pqL.push({v, j});
    }
    else {
      for (int j = 0; j < ej - 1; j++) {
        while (pqL.top().second > i - 3) pqL.pop();
        assert(pqL.size());

        auto [v, l] = pqL.top(); pqL.pop();
        lvis[l] = true;
        lsum += v;
        uL.push({v, l});
      }
    }
  }

  for (int i = 1; i < n; i += 3) {
    dr[i] = sr[i] - rsum;

    int ej = 0;
    for (int j = i; j < i + 3; j++) {
      if (rvis[j]) rsum -= v[j], ej++;
    }
    
    if (ej == 0) {
      while (uR.top().second < i + 3) uR.pop();
      assert(uR.size());

      auto [v, j] = uR.top(); uR.pop();
      rvis[j] = false;
      rsum -= v;
      pqR.push({v, j});
    }
    else {
      for (int j = 0; j < ej - 1; j++) {
        while (pqR.top().second < i + 3) pqR.pop();
        assert(pqR.size());

        auto [v, l] = pqR.top(); pqR.pop();
        rvis[l] = true;
        rsum += v;
        uR.push({v, l});
      }
    }
  }

  // for (int i = 0; i < n; i++) {
  //   cout << "dl[" << i << "] = " << dl[i] << endl;
  //   cout << "dr[" << i << "] = " << dr[i] << endl;
  // }

  ll ans = 0, ai = -1;
  for (int i = 0; i < n; i += 3) {
    ll cur = v[i];
    if (i > 0) cur += dl[i - 1];
    if (i < n - 1) cur += dr[i + 1];

    if (cur > ans) {
      ans = cur;
      ai = i;
    }
  }
  cout << ai << ' ' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
