#include <string>
#include "colored_dealt.h"

std::string guess(int N) {
  std::string Q = std::string(N, 'R');
  
  int S = design(Q); int O = S;
  std::string ans = std::string(N, 'R');
  for (int i = 0; i < N - 1; i++) {
    Q[i] = 'B';
    int T = design(Q);

    if (T == S) ans[i] = 'B';
    else if (T == S + 1) ans[i] = 'G';
    else ans[i] = 'R';

    S = T;
  }

  int A = 0;
  for (int i = 0; i < N - 1; i++) {
    if (ans[i] == 'R') A += 1;
    else if (ans[i] == 'G') A += 2;
    else A += 3;
  }
  if (A + 1 == O) ans[N - 1] = 'R';
  else if (A + 2 == O) ans[N - 1] = 'G';
  else ans[N - 1] = 'B';

  return ans;
}
