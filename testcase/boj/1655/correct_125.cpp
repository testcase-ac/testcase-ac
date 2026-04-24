#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, inp;
	cin >> n;
	priority_queue<int> leftque;
	priority_queue<int, vector<int>, greater<int>> rightque;
	int mid;
	rep(i, n) {
		cin >> inp;
		if(i % 2) {  // even number of elem
			rightque.push(max(mid, inp));
			leftque.push(min(mid, inp));
			cout << leftque.top() << '\n';			
		} else {  // odd number of elem
			if(i == 0) {
				mid = inp;
			} else {
				if(inp <= leftque.top()) {
					leftque.push(inp);
					mid = leftque.top();
					leftque.pop();
				} else if(inp >= rightque.top()) {
					rightque.push(inp);
					mid = rightque.top();
					rightque.pop();
				} else {
					mid = inp;
				}
			}
			cout << mid << '\n';
		}
	}

}
