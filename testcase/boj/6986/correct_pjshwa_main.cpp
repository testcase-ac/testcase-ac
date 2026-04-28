#include <bits/stdc++.h>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  int n, k, scores[100000];
  double s;
  cin >> n >> k;

  for(int i = 0; i < n; i++) {
    cin >> s;
    scores[i] = (int)(s * 10 + 0.5);
  }
  sort(scores, scores + n);

  int trimmed_sum = 0, adjusted_sum = 0;
  for(int i = k; i < n - k; i++) {
    trimmed_sum += scores[i];
  }
  for(int i = 0; i < k; i++) {
    adjusted_sum += scores[k];
    adjusted_sum += scores[n - k - 1];
  }
  adjusted_sum += trimmed_sum;

  cout <<
    fixed <<
    setprecision(2) <<
    (double)trimmed_sum / (10 * (n - 2 * k)) + 1e-9 << '\n' <<
    (double)adjusted_sum / (10 * n) + 1e-9  << '\n';
}
