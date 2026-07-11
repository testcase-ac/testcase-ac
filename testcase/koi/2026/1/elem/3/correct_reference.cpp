#include <iostream>
using namespace std;
const int mxN = 300'005;
const int inf = 1e9;
int N, M;
int A[mxN];
int max_pos[mxN], min_pos[mxN];
int ans;
void input(){
	cin >> N;
	for(int i=1;i<=N;i++) cin >> A[i];
}
void solv() {
    for(int i = 1; i <= N; i++) {
        max_pos[i] = 0;
        min_pos[i] = inf;
    }
    for(int i = 1; i <= N; i++) {
        if(max_pos[A[i]] < i) max_pos[A[i]] = i;
        if(min_pos[A[i]] > i) min_pos[A[i]] = i;
    }
    int pre = 0;
    for(int i = 1; i <= N; i++) {
        if(max_pos[i] == 0) continue;
        if(pre != 0 && max_pos[pre] > min_pos[i]) ans++;
        pre = i;
    }
}
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    input();
    solv();
    cout << ans;
}
