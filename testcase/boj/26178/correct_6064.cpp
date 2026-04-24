#include <bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int,int>;

void solve(int a, int b) {
    // cout << "a,b" << a << " " << b << endl;
    vector<pii> ans;
    ans.push_back({1, a-1});
    b -= a-1;
    while(b>0) {
        // cout << "b: " << b << "\n"; 
        auto curr = ans.back();
        // cout << b << " " << curr.first << " " << curr.second << endl;
        ans.pop_back();
        int diff = min(curr.second-1, b);
        b-=diff;
        curr.second-=diff;
        ans.push_back(curr);
        ans.push_back({curr.first+1, diff});
    }
    cout << a << " " << a-1 << "\n";
    int max_dist = ans.back().first;
    int i;
    for(i=2; i<=max_dist+1; i++)
        cout << i-1 << " " << i << endl;
    for(auto a: ans) {
        // cout << "ans: " << a.first << " " << a.second << "\n";
        for(int j=0; j<a.second-1; j++) {
            cout << a.first << " " << i << "\n";
            i++;
        }
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int a, b;
    for(int i=0; i<s.length(); i++) {
        if(s[i]=='/') {
            a = stoi(s.substr(0, i));
            b = stoi(s.substr(i+1));
            break;
        }
    }
    if(a < b) {
        if(a+1==b) {
            cout << b << " " << b-1 << "\n";
            for(int i=2; i<=b; i++)
                cout << 1 << " " << i << "\n"; 
            return 0;
        }
        else {
            cout << "impossible" << "\n";
            return 0;
        }
    }
    else {
        swap(a, b);
        int k = (2*b+a-1)/(a*a) + 1;
        solve(a*k, b*k);
    }
}
