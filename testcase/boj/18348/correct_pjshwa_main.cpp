#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
int lp[MAX + 1];

int main() {
  fast_io();

  string op;
  int n;
  cin >> op >> n;

  if (op == "chaos") {
    if (n <= 4) {
      for (int i = 1; i <= n; i++) cout << i << ' ';
    }
    else if (n == 5) cout << "1 5 2 3 4";
    else if (n == 6) cout << "1 4 3 2 5 6";
    else if (n == 7) cout << "1 7 4 3 2 5 6";
    else {
      bool odd = n & 1;
      if (odd) n--;
      vector<int> prs;

      // Sieve of Eratosthenes O(n)
      for (ll i = 2; i <= MAX; ++i) {
        if (lp[i] == 0) {
          lp[i] = i;
          prs.push_back(i);
        }
        for (int j = 0; j < prs.size() && prs[j] <= lp[i] && i * prs[j] <= MAX; j++)
          lp[i * prs[j]] = prs[j];
      }

      vector<int> nprs;
      for (int pr : prs) if (pr < n && lp[pr + n] == pr + n) nprs.push_back(pr);

      int p = nprs[0], q;
      for (int i = 1; i < nprs.size(); i++) {
        if (gcd(n, nprs[i] - p) == 2) {
          q = nprs[i];
          break;
        }
      }

      int a = p;
      vector<int> ans;
      for (int i = 1; i <= n; i++) {
        ans.push_back(a);
        if (i & 1) a = p - a;
        else a = q - a;
        if (a <= 0) a += n;
      }

      for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
        if (odd) {
          int left = ans[i] + (n + 1), right = ans[(i + 1) % n] + (n + 1);
          if (lp[left] == left || lp[right] == right) {
            odd = false;
            cout << n + 1 << ' ';
          }
        }
      }
    }
  }
  else {
    if (n >= 6) {
      cout << "3 ";
      for (int i = 1; i <= n; i += 2) if (i != 5 && i != 3) cout << i << ' ';
      cout << "5 4 2 ";
      for (int i = 8; i <= n; i += 2) cout << i << ' ';
      cout << '6';
    }
    else if (n == 1) cout << "1";
    else if (n == 2) cout << "1 2";
    else if (n == 3) cout << "1 2 3";
    else if (n == 4) cout << "1 2 4 3";
    else if (n == 5) cout << "1 2 4 5 3";
  }

}
