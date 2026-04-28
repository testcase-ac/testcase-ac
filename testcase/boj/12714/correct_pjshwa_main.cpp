#include <bits/stdc++.h>
using namespace std;

int modular(string s) { // 숫자가 매우 클 수 있으므로, 한 자리씩 끊어서 계산합니다.
  int ret = 0;
  for (int i = 0; i < s.size(); ++i) {
    ret = (ret * 10 + (s[i] - '0')) % 210;
  }
  return ret;
}

string S;
long long table[45][211];
int main() {
  int T;
  scanf("%d", &T);
  for (int cn = 1; cn <= T; ++cn) {
    cin >> S;
    memset(table, 0, sizeof(table));
    for (int i = 0; i < S.size(); ++i) {
      for (int j = 0; j <= i; ++j) {
        int last = modular(S.substr(j, i - j + 1)); // last = j번째 ~ i번째 자리의 수를 210으로 나눈 나머지 값
        if (j == 0) table[i][last]++; // 사이에 아무 부호도 없는 경우
        else {
          for (int k = 0; k < 210; ++k) {
            table[i][k] += table[j - 1][(k + last) % 210]; // 두 수 사이에 (-) 부호를 넣는 경우
            table[i][k] += table[j - 1][(k + 210 - last) % 210]; // 두 수 사이에 (+) 부호를 넣는 경우
          }
        }
      }
    }
    long long ret = 0;
    for (int i = 0; i < 210; ++i) {
      if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0) ret += table[S.size() - 1][i];
    }
    printf("Case #%d: %lld\n", cn, ret);
  }
}
