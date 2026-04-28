#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int fib[43] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733};
  int t, n, ans;
  stack<int> answers;
  int* lbp;

  cin >> t;
  while (t--) {
    cin >> n;
    while (n) {
      lbp = lower_bound(fib, fib + 43, n);
      if (*lbp != n) lbp--;
      ans = (*lbp);
      n -= ans;
      answers.push(ans);
    }

    while (!answers.empty()) {
      cout << answers.top() << ' ';
      answers.pop();
    }
    cout << '\n';
  }
}
