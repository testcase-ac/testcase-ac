#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<string> A(N), B(N);
    int acnt = 0, bcnt = 0, abot = 0, bbot = 0;
    for(int i=0; i<N; i++) {
        cin >> A[i];
        for(int j=0; j<M; j++) {
            if(A[i][j] == 'B') {
                acnt++;
                if(i == N-1) {
                    abot++;
                }
            }
        }
    }
    for(int i=0; i<N; i++) {
        cin >> B[i];
        for(int j=0; j<M; j++) {
            if(B[i][j] == 'A') {
                bcnt++;
                if(i == N-1) {
                    bbot++;
                }
            }
        }
    }
    int asc = acnt - (abot > 0), bsc = bcnt - (bbot > 0);
    // printf("asc = %lld, bsc = %lld\n", asc, bsc);
    if(asc <= bsc) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }
    int Q;
    cin >> Q;
    while(Q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        if(A[r1][c1] == 'A') {
            bcnt++;
            if(r2 == N-1) {
                bbot++;
            }
        } else {
            acnt--;
            if(r1 == N-1) {
                abot--;
            }
        }
        if(B[r2][c2] == 'B') {
            acnt++;
            if(r1 == N-1) {
                abot++;
            }
        } else {
            bcnt--;
            if(r2 == N-1) {
                bbot--;
            }
        }
        swap(A[r1][c1], B[r2][c2]);
        int asc = acnt - (abot > 0), bsc = bcnt - (bbot > 0);
        // printf("asc = %lld, bsc = %lld\n", asc, bsc);
        if(asc <= bsc) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
}
