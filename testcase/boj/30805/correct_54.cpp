// https://www.acmicpc.net/source/84188248
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> ans;
void f(vector<int> A, vector<int> B) {
    if(A.empty() || B.empty()) {
        return;
    }
    int mx_common = 0;
    vector<int> bs(B.begin(), B.end());
    sort(bs.begin(), bs.end());
    for(int a: A) {
        if(binary_search(bs.begin(), bs.end(), a)) {
            mx_common = max(mx_common, a);
        }
    }
    if(!mx_common) {
        return;
    }
    ans.push_back(mx_common);
    int ai = find(A.begin(), A.end(), mx_common) - A.begin(), bi = find(B.begin(), B.end(), mx_common) - B.begin();
    vector<int> A_nxt(A.begin() + ai + 1, A.end()), B_nxt(B.begin() + bi + 1, B.end());
    f(A_nxt, B_nxt);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int M;
    cin >> M;
    vector<int> B(M);
    for (int i = 0; i < M; i++) {
        cin >> B[i];
    }
    f(A, B);
    cout << ans.size() << '\n';
    for(int i: ans) {
        cout << i << ' ';
    }
}
