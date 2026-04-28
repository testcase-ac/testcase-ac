#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
string p[MAX];
map<string, int> invx, invi;

void solve() {
  int N;
  cin >> N;

  multiset<pii> o;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> p[i] >> x;
    invx[p[i]] = x;
    invi[p[i]] = i;
    o.insert({x, i});
  }

  auto sit = o.end();
  for (int i = 0; i < o.size() / 5; i++) sit--;

  int Q;
  cin >> Q;
  for (int i = N; i < N + Q; i++) {
    string op;
    cin >> op >> p[i];
    if (op == "+") {
      int x;
      cin >> x;
      invx[p[i]] = x;
      invi[p[i]] = i;
      
      o.insert({x, i});
      if (sit == o.end() || pii(x, i) < *sit) {
        if (o.size() % 5 == 0) {
          sit--;
          auto [x, j] = *sit;
          if (p[i] != p[j]) cout << p[i] << " is not working now.\n";
          cout << p[j] << " is working hard now.\n";
        }
        else cout << p[i] << " is not working now.\n";
      }
      else {
        cout << p[i] << " is working hard now.\n";
        if (o.size() % 5 != 0) {
          auto [x, j] = *sit;
          cout << p[j] << " is not working now.\n";
          sit++;
        }
      }
    }
    if (op == "-") {
      int x = invx[p[i]], ii = invi[p[i]];
      if (sit != o.end() && pii(x, ii) == *sit) {
        sit--;
        o.erase({x, ii});

        if (o.size() % 5 == 4) sit++;
        else {
          auto [x, j] = *sit;
          cout << p[j] << " is working hard now.\n";
        }
      }
      else if (sit == o.end() || pii(x, ii) < *sit) {
        o.erase({x, ii});
        if (o.size() % 5 == 4) {
          auto [x, j] = *sit;
          cout << p[j] << " is not working now.\n";
          sit++;
        }
      }
      else {
        o.erase({x, ii});
        if (o.size() % 5 != 4) {
          sit--;
          auto [x, j] = *sit;
          cout << p[j] << " is working hard now.\n";
        }
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
