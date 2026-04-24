#include <bits/stdc++.h>
using namespace std;

int a[] = {1,2,3,3,4,10}, b[] = {1,2,2,2,3,5,10};
int main() {
	int T;
	cin >> T;
	for(int tc=1; tc<=T; tc++) {
		int as = 0, bs = 0;
		for(int i=0; i<6; i++) {
			int t;
			cin >> t;
			as += t*a[i];
		}
		for(int i=0; i<7; i++) {
			int t;
			cin >> t;
			bs += t*b[i];
		}
		if(as > bs)
			printf("Battle %d: Good triumphs over Evil\n", tc);
		else if(as < bs)
			printf("Battle %d: Evil eradicates all trace of Good\n", tc);
		else
			printf("Battle %d: No victor on this battle field\n", tc);
	}
}
