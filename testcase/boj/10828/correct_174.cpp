#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	stack<int> st;
	int temp, n;
	string str;
	cin >> n;
	while(n--) {
		cin >> str;
		if(str == "push") {
			cin >> temp;
			st.push(temp);
		} else if (str == "pop") {
			if(st.empty()) {
				cout << -1 << '\n';
				continue;
			}
			temp = st.top();
			st.pop();
			cout << temp << '\n';
		} else if (str == "size") {
			cout << sz(st) << '\n';
		} else if (str == "empty") {
			cout << (st.empty() ? 1 : 0) << '\n';
		} else {  // top
			cout << (st.empty() ? -1 : st.top()) << '\n';
		}
	}
}
