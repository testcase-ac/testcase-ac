#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

const int INF = 1e9;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<pii> options(n);
  for (int i = 0; i < n; ++i) {
    cin >> options[i].first >> options[i].second;
  }
  sort(options.begin(), options.end());

  set<int> disabled, disabled_total;

  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    if (options[i].second != options[j].second) {
      disabled.insert(options[j].first - options[i].first);
    }
  }

  for (int k : disabled) {
    for (int i = 1; i * i <= k; i++) {
      if (k % i == 0) {
        disabled_total.insert(i);
        disabled_total.insert(k / i);
      }
    }
  }

  for (int v = 2; v <= 50; v++) {
    vector<int> interval(v, -1);
    for (auto [x, c] : options) interval[(x + INF) % v] = c;

    bool fillable = false;
    for (int e : interval) if (e == -1) {
      fillable = true;
      break;
    }
    if (fillable) continue;

    set<int> factors;
    for (int i = 1; i * i <= v; i++) {
      if (v % i == 0) {
        factors.insert(i);
        factors.insert(v / i);
      }
    }

    for (int factor : factors) {
      if (factor == v) continue;

      bool factor_is_not_interval = false;
      for (int bias = 0; bias < factor; bias++) {
        set<int> u;
        for (int i = bias; i < v; i += factor) u.insert(interval[i]);
        if (u.size() > 1) {
          factor_is_not_interval = true;
          break;
        }
      }

      if (!factor_is_not_interval) {
        disabled_total.insert(v);
        break;
      }
    }
  }

  cout << disabled_total.size() << ' ';

  ll sum = 0;
  for (int e : disabled_total) sum += e;
  cout << sum << '\n';
}
