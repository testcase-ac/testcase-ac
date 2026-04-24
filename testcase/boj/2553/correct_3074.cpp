#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    int ans = 1;
    int two_cnt = 0;
    for (int i = 1; i <= N; i++) {
        int t = i;
        while (t % 2 == 0) {
            two_cnt++;
            t /= 2;
        }
        while(t % 5 == 0) {
            two_cnt--;
            t /= 5;
        }
        ans *= t;
        ans %= 10;
    }
    for (int i = 0; i < two_cnt; i++) {
        ans *= 2;
        ans %= 10;
    }
    cout << ans << '\n';
}
