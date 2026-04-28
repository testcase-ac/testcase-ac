#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int q1[MAX], q2[MAX], q3[MAX], q4[MAX];

void solve() {
  int N;
  cin >> N;

  vector<tii> A(N);
  vector<int> lis_vector;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    A[i] = {x, y, i};
  }

  sort(A.begin(), A.end(), [](tii a, tii b) {
    auto [x1, y1, i1] = a;
    auto [x2, y2, i2] = b;
    if (x1 == x2) return y1 > y2;
    return x1 < x2;
  });
  for (int i = 0; i < N; i++) {
    auto [_, next, idx] = A[i];
    if (lis_vector.empty() || lis_vector.back() < next) {
      lis_vector.push_back(next);
      q3[idx] = lis_vector.size();
    }
    else {
      auto it = lower_bound(lis_vector.begin(), lis_vector.end(), next);
      *it = next;
      q3[idx] = it - lis_vector.begin() + 1;
    }
  }

  lis_vector.clear();
  sort(A.begin(), A.end(), [](tii a, tii b) {
    auto [x1, y1, i1] = a;
    auto [x2, y2, i2] = b;
    if (x1 == x2) return y1 < y2;
    return x1 > x2;
  });
  for (int i = 0; i < N; i++) {
    auto [_, next, idx] = A[i];
    next = -next;
    if (lis_vector.empty() || lis_vector.back() < next) {
      lis_vector.push_back(next);
      q1[idx] = lis_vector.size();
    }
    else {
      auto it = lower_bound(lis_vector.begin(), lis_vector.end(), next);
      *it = next;
      q1[idx] = it - lis_vector.begin() + 1;
    }
  }

  lis_vector.clear();
  sort(A.begin(), A.end(), [](tii a, tii b) {
    auto [x1, y1, i1] = a;
    auto [x2, y2, i2] = b;
    if (y1 == y2) return x1 < x2;
    return y1 < y2;
  });
  for (int i = 0; i < N; i++) {
    auto [next, _, idx] = A[i];
    next = -next;
    if (lis_vector.empty() || lis_vector.back() < next) {
      lis_vector.push_back(next);
      q4[idx] = lis_vector.size();
    }
    else {
      auto it = lower_bound(lis_vector.begin(), lis_vector.end(), next);
      *it = next;
      q4[idx] = it - lis_vector.begin() + 1;
    }
  }

  lis_vector.clear();
  sort(A.begin(), A.end(), [](tii a, tii b) {
    auto [x1, y1, i1] = a;
    auto [x2, y2, i2] = b;
    if (y1 == y2) return x1 > x2;
    return y1 > y2;
  });
  for (int i = 0; i < N; i++) {
    auto [next, _, idx] = A[i];
    if (lis_vector.empty() || lis_vector.back() < next) {
      lis_vector.push_back(next);
      q2[idx] = lis_vector.size();
    }
    else {
      auto it = lower_bound(lis_vector.begin(), lis_vector.end(), next);
      *it = next;
      q2[idx] = it - lis_vector.begin() + 1;
    }
  }

  int ans = -1;
  for (int i = 0; i < N; i++) {
    if (q1[i] > 1 && q2[i] > 1 && q3[i] > 1 && q4[i] > 1) {
      ans = max(ans, q1[i] + q2[i] + q3[i] + q4[i] - 3);
    }
  }

  if (ans == -1) cout << "-1\n";
  else cout << N - ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
