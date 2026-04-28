#include <bits/stdc++.h>
#define ll long long
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  int n; 
  ll m, primes[10], stack[10], ans = 0;
  cin >> n >> m;

  for(int i = 0; i < n; i++) cin >> primes[i];

  int stack_pointer;
  bool finished;

  // combinations
  for(int i = 1; i <= n; i++) {
    stack_pointer = -1;
    stack[0] = 0;

    finished = false;
    while (!finished) {

      for (stack_pointer++; stack_pointer < i - 1; stack_pointer++) {
        stack[stack_pointer + 1] = stack[stack_pointer] + 1;
      }

      // stack[0]..stack[i - 1] contains the indexes
      // do work here
      ll mul = 1;
      for(int j = 0; j < i; j++) {
        mul *= primes[stack[j]];
      }
      ll cnt = m / mul;
      (i % 2 == 0) ? ans -= cnt : ans += cnt;
      // do work here

      do {
        if (stack_pointer == -1) {
          finished = true;
          break;
        }
        stack[stack_pointer--]++;
      } while (stack[stack_pointer + 1] + i == n + stack_pointer + 2);
    }
  }

  cout << ans << '\n';
}
