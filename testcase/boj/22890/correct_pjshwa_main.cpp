#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool lg(string a, string b) {
  return a.size() < b.size() || (a.size() == b.size() && a < b);
}

string inc(string s) {
  string t = s;
  int ii = s.size() - 1;
  bool carry = false;

  if (t[ii] == '9') {
    t[ii] = '0';
    carry = true;
  }
  else t[ii]++;

  while (carry && ii > 0) {
    carry = false;
    ii--;
    if (t[ii] == '9') {
      t[ii] = '0';
      carry = true;
    }
    else t[ii]++;
  }
  
  if (carry) t = "1" + t;
  return t;
}

string a[100];
int main() {
  fast_io();

  int t, n;
  cin >> t;

  for (int tc = 1; tc <= t; tc++) {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    int cost = 0;
    for (int i = 0; i < n - 1; i++) {
      if (lg(a[i], a[i + 1])) continue;

      string target = inc(a[i]);

      int asz = target.size();
      int bsz = a[i + 1].size();

      // From here, always asz >= bsz

      bool substr = true;
      for (int j = 0; j < bsz; j++) {
        if (target[j] != a[i + 1][j]) {
          substr = false;
          break;
        }
      }

      if (substr) {
        cost += (asz - bsz);
        a[i + 1] = target;
      }
      else {
        while (!lg(a[i], a[i + 1])) {
          cost++;
          a[i + 1] += '0';
        }
      }
    }

    cout << "Case #" << tc << ": " << cost << '\n';
  }
}
