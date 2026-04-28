#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int s[1000];
int main() {
  fast_io();

  int n, k;
  cin >> n;

  if (n == 2) {
    cout << "1 1\n";
    return 0;
  }

  for (int i = 0; i < n * n; i++) {
    cin >> k;
    s[i % n] += k;
  }

  long long as = 0;
  for (int i = 0; i < n; i++) as += s[i];
  as /= (2 * n - 2);

  for (int i = 0; i < n; i++) cout << (s[i] - as) / (n - 2) << ' ';
  cout << '\n';
}
