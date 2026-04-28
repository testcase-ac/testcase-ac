#include <bits/stdc++.h>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();
  const int MAX = 1e6;
  int n, lp[MAX+1];
  vector<int> pr;

  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  while (1) {
    cin >> n;
    if (n == 0) break;

    for (int i = 3; i <= n / 2; i += 2) {
      if (lp[i] == i && lp[n - i] == n - i) {
        cout << n << " = " << i << " + " << n - i << '\n';
        break;
      }
    }
  }
  
}
