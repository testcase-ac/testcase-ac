#include <iostream>
#include <vector>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();
  const int MAX = 123456 * 2;
  int n, lp[MAX+1], pc[MAX+1];
  vector<int> pr;

  int primes_cnt_till_now = 0;
  pc[0] = primes_cnt_till_now;
  pc[1] = primes_cnt_till_now;

  for (int i=2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      primes_cnt_till_now++;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];

    pc[i] = primes_cnt_till_now;
  }

  while (1) {
    cin >> n;
    if (n == 0) break;

    cout << pc[2 * n] - pc[n] << '\n';
  }
  
}
