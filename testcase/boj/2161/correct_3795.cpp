#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <deque>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
using namespace std;

int main() {
	int n;
	cin >> n;
	deque<int> dq;
	rep(i, n) dq.push_back(i+1);
	while(sz(dq) > 1) {
		cout << dq.front() << ' ';
		dq.pop_front();
		dq.push_back(dq.front());
		dq.pop_front();
	} 
	cout << dq.front();
}
