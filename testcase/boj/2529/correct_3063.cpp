#include <iostream>
#include <string>
#include <algorithm>
#define rep(i,n) for(int i=0; i<n; i++)
using namespace std;
int n;
char op[10];
string minans="9999999999", maxans="0", curr;
void solve() {
	if(curr.size() == n+1) {
		minans = min(minans, curr);
		maxans = max(maxans, curr);
		return;
	}
    for(char c='0'; c<='9'; c++) {
        if(curr.find(c) == string::npos) {
        	if(!curr.empty() && op[curr.size()-1] == '>' ? curr.back()<c : curr.back()>c) {
        	    continue;
        	}
        	curr.push_back(c);
        	solve();
        	curr.pop_back();
        }
    }
}
int main() {
    cin >> n;
    string s;
    rep(i,n) {
        cin >> s;
        op[i] = s[0];
    }
    solve();
    cout << maxans << '\n' << minans;
    
} 
