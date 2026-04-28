#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void print(int x) {
  cout << x << '\n';
}

void solve() {
  int N; cin >> N;

  vector<int> A(N);
  int C[4]{}, tot = 0;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    ++C[A[i]]; tot ^= A[i];
  }

  // only impossible case
  if (N == 1 && C[3] == 1) return print(-1);

  // no 3 so don't need to do anything
  if (C[3] == 0) return print(0);

  // xor sum is not 3 so 1 op on whole array is enough
  if (tot != 3) return print(1);

  // pop out zeros at side to reduce cases
  while (A.back() == 0) A.pop_back();
  reverse(A.begin(), A.end());
  while (A.back() == 0) A.pop_back();

  // just need to flip whole array excluding 1 or 2 in this case
  if (A[0] == 1 || A.back() == 1) return print(1);
  if (A[0] == 2 || A.back() == 2) return print(1);

  // xor sum is 3, and both sides of array is 3
  // which means at least 2 steps are needed
  // 2 step is always achievable if the whole array is not all 3

  // if you meet 0, flip with adj 3 and xor sum is not 3 anymore
  // if you meet 1 or 2, you can split the array into 2 parts

  if (C[3] == N) print(3);
  else print(2);
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
