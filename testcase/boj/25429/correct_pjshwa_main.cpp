#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, l, Q;
  cin >> N >> l >> Q;

  map<int, int> cval, gval;
  map<int, multiset<int>> vz;
  map<int, bool> derror;
  ll run = 0, dz = 0;

  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x, t;
      cin >> x >> t;

      bool err_bef = (
        vz[x % l].size() &&
        vz[x % l].upper_bound(*vz[x % l].begin()) != vz[x % l].end()
      );

      if (cval[x]) {
        vz[x % l].erase(vz[x % l].find(cval[x]));
      }
      cval[x] = t;
      vz[x % l].insert(t);

      bool err_aft = (
        vz[x % l].size() &&
        vz[x % l].upper_bound(*vz[x % l].begin()) != vz[x % l].end()
      );

      if (!err_bef && err_aft) {
        if (!derror[x % l]) {
          dz++;
          derror[x % l] = true;
        }
      }
      if (err_bef && !err_aft) {
        if (derror[x % l]) {
          dz--;
          derror[x % l] = false;
        }
      }

      int nval = *vz[x % l].begin();
      run += nval - gval[x % l];
      gval[x % l] = nval;

      if (dz) cout << "NO\n";
      else cout << "YES " << run << '\n';
    }
    if (op == 2) {
      int x;
      cin >> x;

      bool err_bef = (
        vz[x % l].size() &&
        vz[x % l].upper_bound(*vz[x % l].begin()) != vz[x % l].end()
      );

      vz[x % l].erase(vz[x % l].find(cval[x]));

      bool err_aft = (
        vz[x % l].size() &&
        vz[x % l].upper_bound(*vz[x % l].begin()) != vz[x % l].end()
      );

      if (err_bef && !err_aft) {
        if (derror[x % l]) {
          dz--;
          derror[x % l] = false;
        }
      }

      cval[x] = 0;

      int nval = *vz[x % l].begin();
      run += nval - gval[x % l];
      gval[x % l] = nval;

      if (dz) cout << "NO\n";
      else cout << "YES " << run << '\n';
    }

    // cout << "dz = " << dz << '\n';
    // for (int e : vz[0]) cout << e << ' ';
    // cout << '\n';
    // for (int e : vz[1]) cout << e << ' ';
    // cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
