#include <bits/stdc++.h>
using namespace std;
#define int long long
struct info {
    int a[11];
};
/*
특정 두 점 간의 방향관계는 11bit로 표현 가능.
(a1 - b1) + (a2 - b2) + (b3 - a3)
-> (a1 + a2 - a3) + (- b1 - b2 + b3)

임의의 (Q * 방향)에 대해서 term 2는 이미 고정. term 1을 최대화하기만 하면 됨
*/
vector<int> farthest(2048, LLONG_MIN);
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    vector<info> arr(N), qry(Q);

    for(int i=0; i<N; i++) {
        for(int t=0; t<11; t++) {
            cin >> arr[i].a[t];
        }
        function<void(int, int, int)> get_far = [&](int bm, int pos, int res) {
            if(pos == 11) {
                farthest[bm] = max(farthest[bm], res);
                return;
            }
            get_far(bm,            pos+1, res - arr[i].a[pos]);
            get_far(bm | (1<<pos), pos+1, res + arr[i].a[pos]);
        };
        get_far(0, 0, 0);
    }
    for(int i=0; i<Q; i++) {
        for(int t=0; t<11; t++) {
            cin >> qry[i].a[t];
        }
    }
    for(int q=0; q<Q; q++) {
        int ans = 0;
        function<void(int, int, int)> get_ans = [&](int bm, int pos, int res) {
            if(pos == 11) {
                ans = max(ans, res + farthest[bm]);
                return;
            }
            get_ans(bm,            pos+1, res + qry[q].a[pos]);
            get_ans(bm | (1<<pos), pos+1, res - qry[q].a[pos]);
        };
        get_ans(0, 0, 0);
        cout << ans << '\n';
    }
}
