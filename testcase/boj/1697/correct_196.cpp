#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <queue>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 100000
int dp[MAXN*2+1];

int main() {
	int n, k, step=1;
	cin >> n >> k;
	queue<int> que;
	que.push(n);
	while(!que.empty()) {
		queue<int> nextque;
		while(!que.empty()) {
			int next = que.front();
			que.pop();
			if(dp[next] == 0) {
				dp[next] = step;
				if(next * 2 <= MAXN * 2) nextque.push(next * 2);
				if(next + 1 <= MAXN * 2) nextque.push(next + 1);
				if(next - 1 >= 0) nextque.push(next - 1);
			}
		}
		que = nextque;
		step++;
	}
	cout << (dp[k] - 1);
}
