#include <algorithm>
#include <iostream>
using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
bool arr[1000002];
int N;

void init() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        long long a;
        cin >> a;
        if (a < 1000001)
            arr[a] = true;
    }
}

void solve() {
    for (int i = 1; i <= 1000002; i++) {
        if (!arr[i]) {
            cout << i;
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}
