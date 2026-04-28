#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, P; cin >> N >> P;

  vector<int> C[4];
  for (int i = 0; i < N; ++i) {
    int c, p; cin >> c >> p;
    C[p].push_back(c);
  }
  for (int p = 1; p <= 3; ++p) {
    int Z = C[p].size();

    C[p].push_back(0);
    sort(C[p].begin(), C[p].end());
    for (int i = 1; i <= Z; ++i) C[p][i] += C[p][i - 1];
  }

  int Z1 = C[1].size(), Z2 = C[2].size(), Z3 = C[3].size();

  double p1 = 1, ans = P;
  for (int s1 = 0; s1 < Z1; ++s1) {

    double p2 = 1;
    for (int s2 = 0; s2 < Z2; ++s2) {

      double p3 = 1;
      for (int s3 = 0; s3 < Z3; ++s3) {
        int tot = C[1][s1] + C[2][s2] + C[3][s3];

        double price = P;
        price *= p1; price *= p2; price *= p3;
        price += tot;
        ans = min(ans, price);

        p3 *= (1 - 0.03);
      }
      p2 *= (1 - 0.02);
    }
    p1 *= (1 - 0.01);
  }

  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
