#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  set<int> landmarks;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x == 1) landmarks.insert(i);
  }

  int pos = 0;
  while (q--) {
    int op, qi;
    cin >> op;
    if (op == 1) {
      cin >> qi;
      qi--;
      if (landmarks.count(qi)) landmarks.erase(qi);
      else landmarks.insert(qi);
    }
    if (op == 2) {
      cin >> qi;
      pos = (pos + qi) % n;
    }
    if (op == 3) {
      if (landmarks.size()) {
        auto it = landmarks.lower_bound(pos);
        if (it == landmarks.end()) {
          cout << (*landmarks.begin() + n - pos) << '\n';
        }
        else cout << *it - pos << '\n';
      }
      else cout << "-1\n";
    }
  }
}
