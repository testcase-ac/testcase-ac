#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;

struct PrefixState {
  ll mn;
  ll mx;
};

vector<ll> b;

ll norm(ll value) {
  value %= MOD;
  if (value < 0) value += MOD;
  return value;
}

ll range_sum(const vector<ll>& pref, int l, int r) {
  if (l >= r) return 0;
  return norm(pref[r] - pref[l]);
}

int count_min_at_least(const vector<ll>& right_min, ll value) {
  int lo = 0, hi = (int)right_min.size();
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (right_min[mid] >= value) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  return lo;
}

// Returns the sum of min(subarray) * max(subarray) over all subarrays in [l, r].
ll solve_range(int l, int r) {
  if (l == r) return b[l] % MOD * (b[l] % MOD) % MOD;

  int mid = (l + r) / 2;
  ll ret = (solve_range(l, mid) + solve_range(mid + 1, r)) % MOD;

  vector<PrefixState> left, right;
  ll mn = LLONG_MAX, mx = LLONG_MIN;
  for (int i = mid; i >= l; --i) {
    mn = min(mn, b[i]);
    mx = max(mx, b[i]);
    left.push_back({mn, mx});
  }

  mn = LLONG_MAX;
  mx = LLONG_MIN;
  for (int i = mid + 1; i <= r; ++i) {
    mn = min(mn, b[i]);
    mx = max(mx, b[i]);
    right.push_back({mn, mx});
  }

  int right_count = (int)right.size();
  vector<ll> right_min(right_count), right_max(right_count);
  vector<ll> pref_min(right_count + 1), pref_max(right_count + 1), pref_product(right_count + 1);
  for (int i = 0; i < right_count; ++i) {
    right_min[i] = right[i].mn;
    right_max[i] = right[i].mx;
    pref_min[i + 1] = (pref_min[i] + right[i].mn % MOD) % MOD;
    pref_max[i + 1] = (pref_max[i] + right[i].mx % MOD) % MOD;
    pref_product[i + 1] = (pref_product[i] + (right[i].mn % MOD) * (right[i].mx % MOD)) % MOD;
  }

  for (const auto& cur : left) {
    int max_le = upper_bound(right_max.begin(), right_max.end(), cur.mx) - right_max.begin();
    int min_ge = count_min_at_least(right_min, cur.mn);

    ll cur_min = cur.mn % MOD;
    ll cur_max = cur.mx % MOD;
    int both_left = min(max_le, min_ge);
    int split = max(max_le, min_ge);

    ret = (ret + cur_min * cur_max % MOD * both_left) % MOD;
    if (max_le > min_ge) {
      ret = (ret + cur_max * range_sum(pref_min, min_ge, max_le)) % MOD;
    } else if (min_ge > max_le) {
      ret = (ret + cur_min * range_sum(pref_max, max_le, min_ge)) % MOD;
    }
    ret = (ret + range_sum(pref_product, split, right_count)) % MOD;
  }

  return ret;
}

void solve() {
  int n;
  cin >> n;

  b.resize(n);
  for (int i = 0; i < n; ++i) cin >> b[i];

  cout << solve_range(0, n - 1) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  solve();
  return 0;
}
