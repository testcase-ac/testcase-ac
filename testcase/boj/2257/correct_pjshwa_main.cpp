#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int L[100];

void solve() {
  string S;
  cin >> S;

  int c = 0, prev;
  for (int i = 0; i < S.size(); i++) {
    if (S[i] == '(') c++;
    else if (S[i] == ')') {
      if (i + 1 < S.size() && '2' <= S[i + 1] && S[i + 1] <= '9') {
        L[c] *= (S[i + 1] - '0');
        i++;
      }
      L[c - 1] += L[c];
      L[c] = 0;
      c--;
    }
    else {
      if ('2' <= S[i] && S[i] <= '9') {
        L[c] += (S[i] - '1') * prev;
      }
      else {
        int val;
        if (S[i] == 'H') val = 1;
        if (S[i] == 'C') val = 12;
        if (S[i] == 'O') val = 16;

        L[c] += val;
        prev = val;
      }
    }

  }

  cout << L[0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
