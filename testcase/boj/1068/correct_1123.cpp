#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<vector<int>> child(n);
	vector<int> parent(n);
	rep(i, n) {
		int p;
		cin >> p;
		if(p != -1)
			child[p].push_back(i);
		parent[i] = p;
	}
	int nochildcnt = 0;
	rep(i, n) {
		if(!sz(child[i]))
			nochildcnt++;
	}
	int del;
	cin >> del;
	if(parent[del] != -1 && sz(child[parent[del]]) == 1)
		nochildcnt++;
	queue<int> que;
	que.push(del);
	while(!que.empty()) {
		int q = que.front();
		que.pop();
		if(!sz(child[q]))
			nochildcnt--;
		else {
			for(int c: child[q])
				que.push(c);
		}
	}
	cout << nochildcnt;
}
