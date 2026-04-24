#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)
#define sz(x) ((int)(x).size())
#define ll long long
using namespace std;

bool a[5][100050];
vector<vector<int>> check = {{1,1,1,1,1,0,1}, {1,1,0,0,0,0,0}, {0,1,1,0,1,1,1},{0,0,1,1,1,1,1},{1,0,1,1,0,1,0}, {1,0,0,1,1,1,1},{1,1,0,1,1,1,1},{0,0,1,1,1,0,0},{1,1,1,1,1,1,1}, {1,0,1,1,1,1,1}};
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    rep(i,5) {
        rep(j,n/5) a[i][j] = (s[i*n/5+j] == '#');
    }
    n /= 5;
    int i = 0;
    vector<int> ans;
    while(i < n) {
        bool st[7];
        bool emp = !a[0][i+1] && !a[1][i+1] && !a[2][i+1] && !a[3][i+1] && !a[4][i+1];
        st[0] = a[0][i] && a[1][i] && a[2][i];
        st[1] = a[2][i] && a[3][i] && a[4][i];
        st[2] = a[0][i+2] && a[1][i+2] && a[2][i+2];
        st[3] = a[2][i+2] && a[3][i+2] && a[4][i+2];
        st[4] = a[0][i] && a[0][i+1] && a[0][i+2];
        st[5] = a[2][i] && a[2][i+1] && a[2][i+2];
        st[6] = a[4][i] && a[4][i+1] && a[4][i+2];
        if(st[0] && st[1] && emp) {
            ans.push_back(1);
            i += 2;
            continue;
        }
        bool ok = true;
        for(int j=0; j<=9; j++) {
            ok = true;
            for(int k=0; k<=6; k++) {
                if((bool)check[j][k] != st[k]) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                ans.push_back(j);
                i += (j == 1 ? 2 : 4);
                break;
            }
        }
        if(!ok) i++;
    }
    for(int a: ans) cout << a;
}
