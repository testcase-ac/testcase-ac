#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e5;
int lp[MAX+1];
int main() {
  fast_io();
  
  int t, n;
  vector<int> pr;

  for (int i=2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  ll s, f, m;
  cin >> s >> f >> m;

  ll div, pow;
  map<ll, ll> pow_map;
  for (auto prime : pr) {
    if (prime > m) break;

    div = prime;
    pow = 0;
    while (s + f >= div) {
      pow += (s + f) / div;
      pow -= s / div;
      pow -= f / div;
      div *= prime;
    }
    pow_map.insert({prime, pow});
  }

  ll mv = 1, lpc, nump;
  map<ll, ll> cpow_map;
  bool able;
  for (int num = 2; num <= m; num++) {
    cpow_map.clear();
    nump = num;
    able = true;

    while (nump != 1) {
      lpc = lp[nump];
      nump /= lpc;
      auto found = cpow_map.find(lpc);
      if (found != cpow_map.end()) found->second++;
      else cpow_map.insert({lpc, 1});
    }

    ll key, val;
    for (auto iter = cpow_map.begin(); iter != cpow_map.end(); iter++) {
      key = iter->first;
      val = iter->second;
      if (pow_map[key] < val) able = false;
    }

    if (able) mv = num;
  }

  cout << mv << '\n';
}
