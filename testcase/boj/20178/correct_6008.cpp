#include <bits/stdc++.h>
using namespace std;
const int MX = 501;
int arr[MX][MX], idx[MX][MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        idx[i][i] = 1;
        for(int j=0; j<N; j++) {
            cin >> arr[i][j];
        }
    }

    vector<int> row_selected(N);

    for (int i = 0; i < N; ++i) {
        int j;
        for (j = 0; j < N; ++j) {
            if (!row_selected[j] && arr[j][i])
                break;
        }

        if (j == N) {
            return !(cout << -1);
        }
        row_selected[j] = i+1;
        for (int k = 0; k < N; ++k) {
            if (k != j && arr[k][i]) {
                for (int p = 0; p < N; ++p) {
                    arr[k][p] ^= arr[j][p];
                    idx[k][p] ^= idx[j][p];
                }
            }
        }
    }
    vector<vector<int>> ans(N);

    for(int i=0; i<N; i++) {
        int j = find(row_selected.begin(), row_selected.end(), i+1) - row_selected.begin();
        for(int k=0; k<N; k++) {
            if(idx[j][k]) {
                cout << k+1 << ' ';
            }
        }
        cout << '\n';
    }

}
