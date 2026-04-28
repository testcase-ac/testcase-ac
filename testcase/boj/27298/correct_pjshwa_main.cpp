#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int D[10][7] = {
  {1, 1, 1, 0, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0},
  {1, 0, 1, 1, 1, 0, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {0, 1, 1, 1, 0, 1, 0},
  {1, 1, 0, 1, 0, 1, 1},
  {1, 1, 0, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1},
};

bool comp(vector<int>& a, vector<int>& b) {
  int asum = 0, bsum = 0, amul = 1, bmul = 1;
  for (int e : a) asum += e, amul *= e;
  for (int e : b) bsum += e, bmul *= e;
  
  if (asum != bsum) return asum < bsum;
  if (amul != bmul) return amul < bmul;
  return false;
}

bool comp_sum(vector<ll>& a, vector<ll>& b) {
  assert(a.size() == b.size());

  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) return a[i] < b[i];
  }
  return false;
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  map<int, int> values;
  for (int i = 1; i <= 9; i++) {
    int p = 1, v = 0;
    for (int j = 0; j < 7; j++) {
      if (D[i][j] == 1) v += p;
      p *= 2;
    }
    values[v] = i;
  }

  map<int, vector<int>> m[10];
  for (int s = 0; s < (1 << 10); s++) {
    int b[7]{};
    for (int i = 1; i <= 9; i++) {
      if (!(s & (1 << i))) continue;

      for (int j = 0; j < 7; j++) b[j] ^= D[i][j];
    }

    int p = 1, v = 0;
    for (int j = 0; j < 7; j++) {
      if (b[j] == 1) v += p;
      p *= 2;
    }

    if (values.count(v)) {
      vector<int> u;
      for (int i = 1; i <= 9; i++) {
        if (s & (1 << i)) u.push_back(i);
      }

      int x = values[v];
      if (m[u.size()].count(x)) {
        auto old = m[u.size()][x];
        if (comp(u, old)) m[u.size()][x] = u;
      }
      else m[u.size()][x] = u;
    }
  }

  for (int i = 1; i <= 9; i++) {
    vector<int> u{i, i, i};

    if (m[3].count(i)) {
      auto old = m[3][i];
      if (comp(u, old)) m[3][i] = u;
    }
    else m[3][i] = u;
  }

  vector<ll> osum(N, 1e18); int oz = -1;
  for (int z = 2; z <= 9; z++) {
    bool f = true;
    for (int i = 0; i < N; i++) {
      int x = S[i] - '0';
      f &= m[z].count(x);
    }
    if (!f) continue;

    vector<ll> sum(N);
    for (int i = N - 1; i >= 0; i--) {
      ll acc = 0;
      for (int j = 0; j < z; j++) {
        int x = S[i] - '0';
        acc += m[z][x][j];
      }

      if (i) {
        sum[i] += acc;
        sum[i - 1] += sum[i] / 10;
        sum[i] %= 10;
      }
      else sum[i] += acc;
    }

    if (comp_sum(sum, osum)) osum = sum, oz = z;
  }

  if (oz == -1) {
    cout << -1 << '\n';
    return;
  }

  for (ll& e : osum) cout << e;
  cout << ' ' << oz << '\n';

  for (int z = 0; z < oz; z++) {
    for (int i = 0; i < N; i++) {
      int x = S[i] - '0';
      cout << m[oz][x][z];
    }
    cout << '\n';
  }
}

// 1. TC 간 전역 변수 초기화
// 2. int overflow 체크
// 3. edge case 체크
// 4. 자주 하는 실수
//   - long long에 sqrt() 사용
//   - multiset::count() 사용
int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
