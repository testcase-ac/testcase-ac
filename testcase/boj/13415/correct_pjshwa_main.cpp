#include <bits/stdc++.h>
#define pic pair<int, char>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[100000];
int nums_tmp[100000];
pic stk_a[100000];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i];

  int k, a, b, mx = 0;
  stack<pic> stk;
  cin >> k;
  while (k--) {
    cin >> a >> b;
    while (!stk.empty() && stk.top().first <= a) stk.pop();
    if (stk.empty() || stk.top().second == '>') {
      mx = max(mx, a);
      stk.push({a, '<'});
    }
    while (!stk.empty() && stk.top().first <= b) stk.pop();
    if (stk.empty() || stk.top().second == '<') {
      mx = max(mx, b);
      stk.push({b, '>'});
    }
  }

  int num, sidx = 0;
  char chr;
  while (!stk.empty()) {
    stk_a[sidx++] = stk.top();
    stk.pop();
  }

  sort(nums, nums + mx);
  int lp = 0, rp = mx - 1, mp = mx - 1;

  int diff;
  while (sidx) {
    tie(num, chr) = stk_a[--sidx];

    diff = sidx == 0 ? num : num - stk_a[sidx - 1].first;
    if (chr == '<') {
      while (diff--) nums_tmp[mp--] = nums[rp--];
    }
    else {
      while (diff--) nums_tmp[mp--] = nums[lp++];
    }
  }

  for (int i = 0; i < mx; i++) cout << nums_tmp[i] << ' ';
  for (int i = mx; i < n; i++) cout << nums[i] << ' ';
  cout << '\n';
}
