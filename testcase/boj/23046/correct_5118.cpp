#include <bits/stdc++.h>
using namespace std;
const int MX = 2000001;
int ans[MX];
/*
1
12
123
1234
-----
43215
432156
4321567
-----
76512348
765123489
-----
9843215671
98432156712
984321567123

1563733443901
number 1: add from 0 - 6, 1 - 7
number 2: add from 0 - 5, 2 - 8
number 3: add from 0 - 4, 3 - 9
number 4: add from 0 - 3, 4 - 10
number 5: add from 0 - 6, 5 - 7
number 6: add from 0 - 5, 6 - 8
number 7: add from 0 - 4, 7 - 9
number 8: add from 0 - 2, 8 - 11
number 9: add from 0 - 1, 9 - 12
number 1: add from 0 - 3, 10 - 10
number 2: add from 0 - 2, 11 - 11
number 3: add from 0 - 1, 12 - 12
*/
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    vector<vector<int>> num = {{}};
    int ecnt = 0, ocnt = 0;
    for(char c: s) {
        if(isdigit(c)) {
            num.back().push_back(c - '0');
            if(num.size() % 2 == 1) {
                ecnt++;
            } else {
                ocnt++;
            }
        } else {
            if(num.back().size()) {
                num.push_back({});
            } else {
                num.pop_back();
            }
        }
    }
    int acc = 0;
    for(int i=0; i<num.size(); i++) {
        for(int j=0; j<num[i].size(); j++) {
            if(i % 2 == 0) {
                ans[0] += num[i][j];
                ans[ecnt] -= num[i][j];
                ans[acc+1] += num[i][j];
                ans[acc+ocnt+1] -= num[i][j];
                ecnt--;
            } else {
                ans[0] += num[i][j];
                ans[ocnt] -= num[i][j];
                ans[acc+1] += num[i][j];
                ans[acc+ecnt+1] -= num[i][j];
                ocnt--;
            }
            acc++;
        }
    }
    for(int i=1; i<MX; i++) {
        ans[i] += ans[i-1];
    }
    string ansstr;
    for(int i=0; i<MX; i++) {
        if(!ans[i]) {
            break;
        }
        ansstr.push_back(ans[i] % 10 + '0');
        ans[i+1] += ans[i] / 10;
    }
    reverse(ansstr.begin(), ansstr.end());
    cout << ansstr;
}
