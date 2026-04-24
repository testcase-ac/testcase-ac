#include <bits/stdc++.h>
using namespace std;
#define fail exit(!(cout << -1))
string raw, str;
int n;
void test(int ind, initializer_list<char> ls, bool shouldInBnd) {
	if(ind < 0 || ind >= n) {
		if(shouldInBnd) fail;
		else return;
	}
	for(char i: ls)
		if(i == str[ind])
			return;
	fail;
}
int main() {
	int w;
	cin >> w;
	cin.get();
	getline(cin, raw);
	for(char c: raw) if(c != ' ') str.push_back(c);
	n = str.size();
	int s = 0, l = 0, b = 0;
	stack<char> stk;
	for(int i=0; i<n; i++) {
		char c = str[i];
		if(c == '[' || c == '(') stk.push(c);
		else if(c == ']') {
			if(stk.empty() || stk.top() != '[') fail;
			stk.pop();
		} else if(c == ')') {
			if(stk.empty() || stk.top() != '(') fail;
			stk.pop();
		} else if(c == 'S')
			s++;
		else if(c == 'L')
			l++;
		else if(c == 'B')
			b++;
		else if(c != ',') {
			fail;
		}
	}
	if(!stk.empty()) fail;
	for(int i=0; i<n; i++) {
		char c = str[i];
		if(c == '(' || c == '[') {
			test(i-1, {'L','B'}, 1);
			test(i+1, {'L','S','B'}, 1);
		} else if(c == ')' || c == ']') {
			test(i-1, {'S',')',']'}, 1);
			test(i+1, {',',']',')'}, 0);
		} else if(c == ',') {
			test(i-1, {'S',')',']'}, 1);
			test(i+1, {'L','S','B'}, 1);
		} else if(c == 'L' || c == 'B') {
			test(i-1, {',','[','('}, 0);
			test(i+1, {'(','['}, 1);
		} else if(c == 'S') {
			test(i-1, {',','[','('}, 0);
			test(i+1, {',',']',')'}, 0);
		}
	}
	test(0, {'L','S','B'}, true);
	if(str[0] == ',' || str[0] == '[' || str[0] == ']' || str[0] == '(' || str[0] == ')') assert(false);
	int eb = l, v = s+(l+b)*2, ef = v-1+b;
	cout << ef+w*eb-v+2;
}
