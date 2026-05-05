#include <iostream>
#include <vector>
#include <algorithm>
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    const long long INF = 9e18;
    long long N;
    int X;
    while (T--) {
        std::cin >> N >> X;

        std::vector<long long> spikes(X + 1);
        for (int i = 1; i <= X; i++) {
            std::cin >> spikes[i];
        }

        std::vector<long long> dp(X + 1, INF);
        dp[0] = -4;

        for (int i = 1; i <= X; i++) {
            for (int j = i; j >= 1 && spikes[i] - spikes[j] <= 2; j--) {
                long long left = std::max(1LL, spikes[i] - 2);
                long long right = spikes[j];

                long long prev = dp[j - 1];
                if (prev == INF) {
                    continue;
                }

                long long start = std::max(left, prev + 4); // 점프 시작 위치
                if (start <= right) {
                    dp[i] = std::min(dp[i], start);
                }
            }
        }

        std::cout << (dp[X] == INF ? "IMPOSSIBLE\n" : "POSSIBLE\n");
    }

    return 0;
}
