#include <bits/stdc++.h>
using namespace std;
struct point {
	int x, isstart, r, i;
};
const int MX = 3e5+2;
point arr[MX*2];
int ans;
int dfs(int ptr) {
	//printf("entered at ptr=%d. x, isstart, r, i=%d %d %d %d\n",
	//	ptr, arr[ptr].x, arr[ptr].isstart, arr[ptr].r, arr[ptr].i);
	int r = arr[ptr].x, i = arr[ptr].i, fullright = arr[ptr].x+2*arr[ptr].r;
	bool closed = 1;
	while(1) {
		ptr++;
		if(arr[ptr].i == i)
			break;
		if(arr[ptr].x != r) {
			closed = 0;
		}
		int tmp = arr[ptr].x+2*arr[ptr].r;
		ptr = dfs(ptr);
		r = arr[ptr].x; // should be same as original's right side
		assert(r == tmp);
	}
	if(closed && r == fullright) {
		//printf("plus 1 at i=%d\n", arr[ptr].i);
		ans++;
	}
	return ptr;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int x, r;
		cin >> x >> r;
		arr[2*i] = {x-r, 1, r, i};
		arr[2*i+1] = {x+r, 0, r, i};
	}
	sort(arr, arr+2*n, [](point& a, point& b){
		if(a.x != b.x)
			return a.x < b.x;
		if(a.isstart != b.isstart)
			return a.isstart < b.isstart;
		if(!a.isstart)
			return a.r < b.r;
		else
			return a.r > b.r;
	});
	ans = n+1;
	int ptr = 0;
	while(ptr < 2*n-1) {
		ptr = dfs(ptr);
		ptr++;
	}
	cout << ans;
}
