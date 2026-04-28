#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

// 관찰 1) 첫번째 연산은 array 전체에 적용될 수 없다. => array 의 첫번째 원소와 마지막 원소 모두가 첫번째 연산에 의해 사라질 수는 없다. => 답으로 나올 수 있는 GCD 는 array 의 {첫번째 원소 + 1, 첫번째 원소, 첫번째 원소 - 1, 마지막 원소 + 1, 마지막 원소, 마지막 원소 - 1} 6개 중 하나의 약수이다.

// 관찰 2) GCD 후보 x 에 대해, array 의 모든 원소를 두번째 연산만 사용하여 x 의 배수로 만들 수 있을 경우 kadane's algorithm 을 사용하여 첫번째 연산이 적용될 수 있는 가장 큰 범위를 찾는다. 두번째 연산만 사용하여 x 의 배수로 만들 수 없을 경우 첫번째 연산이 적용되어야만 하는 가장 작은 범위를 찾은 후, two pointer 사용하여 더 최적의 값이 존재하는지 확인한다.

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
const ll INF = 1e18;
int v[MAX];
ll n, a, b;
bool d[MAX], s[MAX];

vector<int> factors(int k) {
  vector<int> res;
  for (int i = 1; i * i <= k; i++) {
    if (k % i == 0) {
      res.push_back(i);
      if (i * i != k) res.push_back(k / i);
    }
  }
  return res;
}

ull lpow(ull x, ull y, ull m){
  ull r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

inline bool miller_rabin(ull n, ull a) {
  ull d = n - 1;
  while (d % 2 == 0) {
    if (lpow(a, d, n) == n - 1) return true;
    d /= 2;
  }
  ull r = lpow(a, d, n);
  return r == n - 1 || r == 1;
}

bool is_prime(ull n) {
  if (n == 1) return false;
  for (ull a : {2, 7, 61}) {
    if (n == a) return true;
    if (!miller_rabin(n, a)) return false;
  }
  return true;
}

bool forms(int a, int b) {
  return (a - 1) % b == 0 || (a + 1) % b == 0;
}

tuple<int, int, ll> max_subarray() {
  ll max_so_far = -INF, max_ending_here = 0;
  int ei;
  for (int i = 0; i < n; i++) {
    max_ending_here = max_ending_here + (d[i] ? b - a : -a);
    if (max_so_far < max_ending_here) ei = i + 1, max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;
  }
  ll s = 0;
  for (int si = ei - 1; si >= 0; si--) {
    s += (d[si] ? b - a : -a);
    if (s == max_so_far) return make_tuple(si, ei, max_so_far);
  }
}

ll min_cost(int target) {
  int lp = 0, rp = n - 1;
  for (int i = 0; i < n; i++) d[i] = forms(v[i], target), s[i] = v[i] % target == 0;
  while (lp < n && (d[lp] || s[lp])) lp++;
  if (lp == n) {
    auto [si, ei, mx] = max_subarray();
    ll mval = 0;
    if (mx > 0) {
      for (int i = 0; i < si; i++) if (d[i]) mval += b;
      for (int i = ei; i < n; i++) if (d[i]) mval += b;
      mval += a * (ei - si);
    }
    else for (int i = 0; i < n; i++) if (d[i]) mval += b;
    return mval;
  }
  else {
    while (d[rp] || s[rp]) rp--;
    rp++;

    ll mval = 0;
    for (int i = 0; i < lp; i++) if (d[i]) mval += b;
    for (int i = rp; i < n; i++) if (d[i]) mval += b;
    mval += a * (rp - lp);

    ll cval = mval;
    for (int i = rp; i < n; i++) {
      if (d[i]) cval += (a - b);
      else cval += a;
      if (cval < mval) mval = cval;
    }
    cval = mval;
    for (int i = lp - 1; i >= 0; i--) {
      if (d[i]) cval += (a - b);
      else cval += a;
      if (cval < mval) mval = cval;
    }

    return mval;
  }
}

int main() {
  fast_io();

  cin >> n >> a >> b;
  for (int i = 0; i < n; i++) cin >> v[i];

  ll mcost = INF;
  for (int lc : {v[0] - 1, v[0], v[0] + 1}) {
    auto fs = factors(lc);
    for (int f : fs) {
      if (is_prime(f)) mcost = min(mcost, min_cost(f));
    }
  }

  for (int rc : {v[n - 1] - 1, v[n - 1], v[n - 1] + 1}) {
    auto fs = factors(rc);
    for (int f : fs) {
      if (is_prime(f)) mcost = min(mcost, min_cost(f));
    }
  }

  cout << mcost;
}
