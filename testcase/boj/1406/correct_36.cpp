#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <list>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string str;
	cin >> str;
	list<char> ls;
	for(char c: str)
		ls.push_back(c);
	int t;
	cin >> t;
	char cmd;
	char inp;
	auto it = ls.end();
	while(t--) {
		cin >> cmd;
		if(cmd == 'L') {
			if(it != ls.begin()) it--;
		} else if(cmd == 'D') {
			if(it != ls.end()) it++;
		} else if(cmd == 'B') {
			if(it == ls.begin()) continue;
			auto temp = it;
			temp--;
			ls.erase(temp);
		} else if(cmd == 'P') {
			cin >> inp;
			ls.insert(it, inp);
		}
	}
	for(char c: ls) {
		cout << c;
	}
}
