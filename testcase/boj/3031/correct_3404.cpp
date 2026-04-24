#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		int arr[5];
		for(int i=0; i<5; i++) {
			string s;
			cin >> s;
			if(isdigit(s[0])) {
				arr[i] = stoi(s);
			} else {
				arr[i] = -1;
			}
		}
		int a, b, c;
		for(int w=0; w<=100; w++) {
			if(arr[1] != -1 && arr[1] != w) continue;
			for(int d=0; d<=100-w; d++) {
				if(arr[2] != -1 && arr[2] != d) continue;
				if(arr[3] != -1 && w+d+arr[3] > 100) continue;
				if(arr[4] != -1 && 3*w+d != arr[4]) continue;
				int l = -1;
				if(w+d == 100) l = 0;
				if(arr[0] != -1) {
					l = arr[0]-w-d;
					if(l < 0) continue;
				}
				if(arr[3] == -1) {
					if(l == -1) continue;
				} else {
					if(l == -1) l = arr[3];
					else if(arr[3] != l) continue;
				}
				tie(a,b,c) = tie(w,d,l);
			}
		}
		printf("%d %d %d %d %d\n", a+b+c, a, b, c, 3*a+b);
	}
}
