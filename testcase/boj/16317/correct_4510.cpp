#include <bits/stdc++.h>
using namespace std;

int arr[380];
int32_t main() {
	int N;
	scanf("%d",&N);
	for(int i=0,x; i<N; i++) {
		scanf("%d",&x);
		arr[x] = 1;
	}
	int cur = 0, num = 0, cnt = 0;
	for(int i=1; i<=365; i++) {
		cur += num;
		num += arr[i];
		if(cur+num>=20) {
			cnt++;
			cur = 0;
			num = 0;
		}
	}
	if(cur+num != 0) {
		cnt++;
	}
	printf("%d",cnt);	
}
