#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
dp[i]: the total time required for building i to be built finally after all dependency
dp[i] = max(dp[j] for j in all of i's dependency) if i has dependency else 0 + time[i]
*/
int main() {
	int T;
	cin >> T;
	while(T--) {
		int N, K;
		cin >> N >> K;
		int time[N];
		int dependenceCnt[N], origDependenceCnt[N];
		memset(dependenceCnt, 0, sizeof(int) * N);
		bool dependenceMatrix[N][N]; // dm[i][j]: whether i is dependent on j
		memset(dependenceMatrix, 0, sizeof(bool) * N * N);
		for(int i=0; i<N; i++)
			cin >> time[i];
		int before, after, winning;
		for(int i=0; i<K; i++) {
			cin >> before >> after;
			before--;
			after--;
			dependenceCnt[after]++;
			dependenceMatrix[before][after] = true;
		}
		memcpy(origDependenceCnt, dependenceCnt, sizeof(int) * N);
		cin >> winning;
		winning--;
		int dp[N];
		memset(dp, 0, sizeof(int) * N);
		for(int i=0;;i=(i+1)%N) {
			if(dependenceCnt[i] == 0) {
				if(origDependenceCnt[i] == 0) {
					dp[i] = time[i];
				} else {
					int maxdp = 0;
					for(int j=0; j<N; j++) {
						if(dependenceMatrix[j][i])
							maxdp = max(maxdp, dp[j]);
					}
					dp[i] = maxdp + time[i];
				}
				if(i == winning)
					break;
				dependenceCnt[i]--;
				for(int j=0;j<N;j++) {
					if(dependenceMatrix[i][j])
						dependenceCnt[j]--;
				}
			}
		}
		cout << dp[winning] << endl;
	}
}
