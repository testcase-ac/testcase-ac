#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX = 1e5;
ll lp[MAX + 1];

bool isPalindrome(string s) {
  int sz = s.size();
  if (sz <= 1) return true;
  else return s[0] == s[sz - 1] && isPalindrome(s.substr(1, sz - 2));
}

int main() {
  vector<int> pr;

  int n;
  cin >> n;
  if (n > 98689) {
    cout << 1003001;
    return 0;
  }

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  while (1) {
    if (lp[n] == n && isPalindrome(to_string(n))) {
      cout << n;
      break;
    }
    n++;
  }
}
