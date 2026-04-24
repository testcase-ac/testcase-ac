#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<string, int> any_m, left_m, right_m;
    set<string> types;
    for(int i=0; i<n; i++) {
        string s1, s2;
        int m;
        cin >> s1 >> s2 >> m;
        types.insert(s1);
        if(s2=="any") {
            any_m[s1] = m;
        }
        else if(s2=="left") {
            left_m[s1] = m;
        }
        else {
            right_m[s1] = m;
        }
    }
    bool pos = false;
    int cnt = 0;
    for(auto s: types) {
        bool this_pos =  (any_m[s] > 0 && (left_m[s] + right_m[s] >0)) || (left_m[s] > 0 && right_m[s] >0) || any_m[s] >= 2;
        if(!this_pos) {
            cnt += (any_m[s] + left_m[s] + right_m[s]);
        }
        else {
            if(left_m[s] == 0 && right_m[s] == 0)
                cnt+=1;
            else
                cnt+=max(left_m[s], right_m[s]);
            pos = true;
        }
    }
    if(pos)
        cout << cnt+1;
    else
        cout << "impossible";
}
