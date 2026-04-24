#include <bits/stdc++.h>
using namespace std;
void put(int i, int j) {printf("(%d,%d)\n", i, j);}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		printf("1\n");
		if(n % 2 == 0) {
			for(int i=0; i<n; i+=2) {
				for(int j=0; j<m; j++)
					put(i,j);
				for(int j=m-1; j>=0; j--)
					put(i+1,j);
			}
		} else if(m % 2 == 0) {
			for(int j=0; j<m; j+=2) {
				for(int i=0; i<n; i++)
					put(i, j);
				for(int i=n-1; i>=0; i--)
					put(i, j+1);
			}
		} else {
			for(int i=0; i<n; i++)
				put(i, 0);
			for(int i=1; i<m; i++)
				put(n-1, i);
			for(int i=n-2; i>=0; i-=2) {
				for(int j=m-1; j>=1; j--)
					put(i, j);
				for(int j=1; j<m; j++)
					put(i-1, j); 
			}
		}
	}
}
