#include <bits/stdc++.h>
#define ll long long
#define tii tuple<int, int, int> // num, inv, original_order
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void swap(tii& l, tii& r) {
  auto temp = l;
  l = r;
  r = temp;
}

tii nums[500001];
tii nums_tmp[500001];

void enhanced_merge(int l, int r) {
  if (l == r) return;
  else if (l + 1 == r) {
    if (get<0>(nums[l]) > get<0>(nums[r])) {
      get<1>(nums[r])++;
      swap(nums[l], nums[r]);
    }
    return;
  }

  int m = (l + r) / 2;
  enhanced_merge(l, m);
  enhanced_merge(m + 1, r);

  int i = l, j = m + 1;
  int invs = j - i, ptr = l;

  while (j <= r && i <= m) {
    if (get<0>(nums[i]) > get<0>(nums[j])) {
      get<1>(nums[j]) += invs;
      nums_tmp[ptr] = nums[j];
      j++;
    }
    else {
      nums_tmp[ptr] = nums[i];
      invs--;
      i++;
    }
    ptr++;
  }

  while (i <= m) nums_tmp[ptr++] = nums[i++];
  while (j <= r) nums_tmp[ptr++] = nums[j++];
  for (int k = l; k <= r; k++) nums[k] = nums_tmp[k];
}

int main() {
  fast_io();

  int n, k;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> k;
    nums[i] = {k, 0, i};
  }

  enhanced_merge(1, n);
  sort(nums + 1, nums + n + 1, [](tii x, tii y){return get<2>(x) < get<2>(y);});

  for (int i = 1; i <= n; i++) cout << get<1>(nums[i]) + 1 << '\n';
}
