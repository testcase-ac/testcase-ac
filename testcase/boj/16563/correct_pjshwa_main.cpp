#include <iostream>
#include <vector>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 5e6;
int lp[MAX+1];

int main() {
  FastIO();
  
  int t, n, lpc;
  vector<int> pr;

  for (int i=2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];

  }

  cin >> t;
  while (t--) {
    cin >> n;

    while (n != 1) {
      lpc = lp[n];
      n /= lpc;
      cout << lpc << ' ';
    }
    cout << '\n';
  }
  
}
