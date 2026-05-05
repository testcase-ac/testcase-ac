#include <bits/stdc++.h>

using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n, k, x;
  cin >> n >> k >> x;

  vector<int> arr(n);
  for (auto& e : arr) cin >> e >> e;

  bitset<16001> memo[81];
  memo[0].set(0);
  for (int i = 0; i < n; i++) {
    for (int j = min<int>(i, k - 1); j >= 0; j--) {
      memo[j + 1] |= (memo[j] << arr[i]);
    }
  }

  int kx = k * x;
  int l = kx >> 1, r = kx - l;
  while (!memo[k].test(l) && !memo[k].test(r)) --l, ++r;
  cout << l * r;

  return 0;
}
