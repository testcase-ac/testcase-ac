#include <iostream>
using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int N; char c1, c2;
int ans, tbl[128][128];


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    tbl['5']['5'] = tbl['2']['2'] = 1;
    tbl[']']['['] = -1;

    cin >> N >> c1; N--;
    while (N--) {
        cin >> c2;
        ans += tbl[c1][c2] + 1;
        c1 = c2;
    }

    cout << ans;
}
