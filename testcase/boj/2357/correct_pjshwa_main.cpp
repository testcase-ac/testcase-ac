#include <iostream>
#include <vector>
#include <cmath>
#define MAX 1000000007
#define MIN 0

using namespace std;
#define ll long long

struct SegMin {
  int flag;  // array size
  vector<ll> t;

  void build(int N, vector<ll> nums) {
    for (flag = 1; flag < N; flag <<= 1);
    t.resize(2 * flag);

    for (int i = flag; i < flag + N; i++) t[i] = nums[i - flag];
    for (int i = flag - 1; i >= 1; i--) t[i] = min(t[i << 1], t[i << 1 | 1]);
  }
  void modify(int p, int value) {  // set value at position p
    for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
  }
  ll query(int L, int R) {
    return query(L, R, 1, 1, flag);
  }
  ll query(int L, int R, int n, int nL, int nR) {  // min on interval [L, R]
    if (R < nL || nR < L) return MAX;
    if (L <= nL && nR <= R) return t[n];

    int mid = (nL + nR) / 2;
    return min(query(L, R, n << 1, nL, mid), query(L, R, n << 1 | 1, mid + 1, nR));
  }
}seg_min;

struct SegMax {
  int flag;  // array size
  vector<ll> t;

  void build(int N, vector<ll> nums) {
    for (flag = 1; flag < N; flag <<= 1);
    t.resize(2 * flag);

    for (int i = flag; i < flag + N; i++) t[i] = nums[i - flag];
    for (int i = flag - 1; i >= 1; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
  }
  void modify(int p, int value) {  // set value at position p
    for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
  }
  ll query(int L, int R) {
    return query(L, R, 1, 1, flag);
  }
  ll query(int L, int R, int n, int nL, int nR) {  // min on interval [L, R]
    if (R < nL || nR < L) return MIN;
    if (L <= nL && nR <= R) return t[n];

    int mid = (nL + nR) / 2;
    return max(query(L, R, n << 1, nL, mid), query(L, R, n << 1 | 1, mid + 1, nR));
  }
}seg_max;

int main() {
  cin.tie(NULL); cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  int N, M; ll a, b; cin >> N >> M;
  vector<ll> nums;

  for (int i = 0; i < N; i++) {
    cin >> a;
    nums.push_back(a);
  }
  seg_min.build(N, nums);
  seg_max.build(N, nums);

  while (M--) {
    cin >> a >> b;
    cout << seg_min.query(a, b) << ' ' << seg_max.query(a, b) << '\n';
  }

  return 0;
}
