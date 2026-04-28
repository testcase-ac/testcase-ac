#include <bits/stdc++.h>
using namespace std;

int N, X[555], Y[555], A[555][555], S[555][555];

int Sum(int r1, int c1, int r2, int c2){
    return S[r2][c2] - S[r1-1][c2] - S[r2][c1-1] + S[r1-1][c1-1];
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> N;
    for(int i=1; i<=N; i++) cin >> X[i] >> Y[i];

    vector<int> CX(X+1, X+N+1), CY(Y+1, Y+N+1);
    sort(CX.begin(), CX.end()); CX.erase(unique(CX.begin(), CX.end()), CX.end());
    sort(CY.begin(), CY.end()); CY.erase(unique(CY.begin(), CY.end()), CY.end());
    for(int i=1; i<=N; i++) X[i] = lower_bound(CX.begin(), CX.end(), X[i]) - CX.begin() + 1;
    for(int i=1; i<=N; i++) Y[i] = lower_bound(CY.begin(), CY.end(), Y[i]) - CY.begin() + 1;
    for(int i=1; i<=N; i++) A[X[i]][Y[i]] = 1;

    int R = CX.size(), C = CY.size();
    for(int i=1; i<=R; i++) for(int j=1; j<=C; j++) S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + A[i][j];

    int mx = 0;
    for(int i=1; i<=R; i++){
        for(int j=i; j<=R; j++){
            int cup = 0;
            for(int k=1; k<=C; k++){
                int lid = Sum(i, k, j, k);
                mx = max(mx, cup + lid);
                cup += A[i][k] + A[j][k] - (i == j ? A[i][k] : 0);
                cup = max(cup, lid);
            }
        }
    }
    cout << mx;
}
