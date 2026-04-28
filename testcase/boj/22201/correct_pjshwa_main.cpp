#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<int> O(N);
  for (int i = 0; i < N; i++) cin >> O[i];

  vector<int> Q;
  for (int i = 0; i < N; i++) {
    // cout << "i = " << i + 1 << endl;

    if (O[i] == 3) {
      if (Q.empty()) {
        cout << "1\n";
        Q.push_back(2);
      }
      else {
        bool f = false;
        for (int i = 0; i < Q.size(); i++) {
          int& e = Q[i];
          if (e == 6) continue;
          if (i > 0 && Q[i - 1] < e + 2) continue;

          f = true;
          cout << e + 1 << '\n';
          e += 2;
          break;
        }

        if (!f) {
          cout << "1\n";
          Q.push_back(2);
        }

      }
    }
    if (O[i] == 5) {
      if (Q.empty()) {
        cout << "1\n";
        Q.push_back(3);
      }
      else {
        bool f = false;
        for (int i = 0; i < Q.size(); i++) {
          int& e = Q[i];
          if (e == 5 || e == 7) continue;
          if (i > 0 && Q[i - 1] < e + 3) continue;

          f = true;
          cout << e + 1 << '\n';
          e += 3;
          break;
        }

        if (!f) {
          cout << "1\n";
          Q.push_back(3);
        }
      }
    }

    // cout << "Q: ";
    // for (int e : Q) cout << e << ' ';
    // cout << endl;

    vector<int> nQ;
    for (int e : Q) {
      if (e == 9) continue;
      nQ.push_back(e);
    }
    swap(Q, nQ);

  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
