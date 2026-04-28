#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;
  vector<tii> A(N);
  map<int, int> xinv, yinv;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    A[i] = {x, y, i + 1};
    xinv[i + 1] = x;
    yinv[i + 1] = y;
  }

  vector<int> um, dm, lm, rm;

  sort(A.begin(), A.end(), [] (const tii& a, const tii& b) {
    return get<0>(a) < get<0>(b);
  });
  for (int i = 1; i <= N; i++) {
    int cx = get<0>(A[i - 1]), ct = get<2>(A[i - 1]);
    for (int j = cx; j > i; j--) um.push_back(ct);
    for (int j = cx; j < i; j++) dm.push_back(ct);
  }
  sort(um.begin(), um.end(), [&] (const int& at, const int& bt) {
    return xinv[at] < xinv[bt];
  });
  sort(dm.begin(), dm.end(), [&] (const int& at, const int& bt) {
    return xinv[at] > xinv[bt];
  });

  sort(A.begin(), A.end(), [] (const tii& a, const tii& b) {
    return get<1>(a) < get<1>(b);
  });
  for (int i = 1; i <= N; i++) {
    int cy = get<1>(A[i - 1]), ct = get<2>(A[i - 1]);
    for (int j = cy; j > i; j--) lm.push_back(ct);
    for (int j = cy; j < i; j++) rm.push_back(ct);
  }
  sort(lm.begin(), lm.end(), [&] (const int& at, const int& bt) {
    return yinv[at] < yinv[bt];
  });
  sort(rm.begin(), rm.end(), [&] (const int& at, const int& bt) {
    return yinv[at] > yinv[bt];
  });

  cout << um.size() + dm.size() + lm.size() + rm.size() << '\n';
  for (int t : um) cout << t << " U\n";
  for (int t : dm) cout << t << " D\n";
  for (int t : lm) cout << t << " L\n";
  for (int t : rm) cout << t << " R\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
