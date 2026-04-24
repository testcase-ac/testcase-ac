#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); i++)
#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin >> n;
    vector<int> pos, neg, cand;
    bool hasz = false;
    rep(i,n) {
        int t;
        cin >> t;
        if(t > 0)
            pos.push_back(t);
        else if(t < 0)
            neg.push_back(t);
        else
            hasz = true;
    }
    if(hasz) cand = {0};
    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end());
    reverse(pos.begin(), pos.end());
    if(pos.size() >= 2) {
        cand.push_back(pos[0]*pos[1]);
    }
    if(pos.size() >= 3)
        cand.push_back(pos[0]*pos[1]*pos[2]);
    if(neg.size() >= 2) {
        cand.push_back(neg[0]*neg[1]);
        if(pos.size() >= 1)
            cand.push_back(neg[0]*neg[1]*pos[0]);
    }
    if(pos.size() && neg.size())
        cand.push_back(pos[0]*neg.back());
    sort(cand.begin(), cand.end());
    cout << cand.back();

}


