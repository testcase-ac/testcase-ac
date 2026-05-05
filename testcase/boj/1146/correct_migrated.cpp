#include<cstdio>
#define MOD 1000000
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int dp[105][105];

int main() {
  int N; scanf("%d",&N);
  for(int i=1;i<=N;i++) {
    for(int j=1;j<=i;j++) {
      if(i == 1) dp[i][j] = 1;
      else dp[i][j] = (dp[i][j-1] + dp[i-1][i-j+1])%MOD;
    }
  }
  int ans = 0;
  for(int i=1;i<=N;i++) {
    ans += dp[N][i]; ans %= MOD;
  }
  printf("%d",N == 1 ? 1 : (ans*2)%MOD);
}
