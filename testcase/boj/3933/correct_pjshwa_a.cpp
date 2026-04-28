#include <iostream>

using namespace std;
const int SZ = (1 << 15) + 5;
int memo[SZ][5];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memo[0][0] = 1;
    // n을 i개의 제곱수를 사용하여 나타낼 수 있는 경우의 수
    for (int i = 1; i * i < SZ; i++) {
        memo[i * i][1] = 1;
        // 중복을 허용하는 경우 오름차순으로 계속 더해나갈 수 있고,
        // 허용하지 않는 경우엔 내림차순으로 간다.
        for (int j = i*i; j < SZ; j++) {
            for (int k = 2; k <= 4; k++) {
                // knapsack의 기본은 가방에 item을 넣었을 때 무게
                // 기존의 무겟값이랑 잘 비교할 줄 알아야 함.
                memo[j][k] += memo[j-i*i][k-1];
            }
        }
    }

    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        int res = 0;
        for (int i = 1; i < 5; i++) res += memo[n][i];
        cout << res << '\n';
    }
    return 0;
}
