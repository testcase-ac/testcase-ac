#include <bits/stdc++.h>
using namespace std;
bool arr[11][11];
int cnt[6], n = 10;
pair<int, int> nxt(int i, int j) {
	while(!arr[i][j]) {
		j++;
		if(j >= n) {
			i++;
			j = 0;
			if(i >= n) break;
		}
	}
	return {i, j};
}
int ans = 100, used = 0;
void f(int i, int j) {
	tie(i, j) = nxt(i, j);
	if(i == n) {
		ans = min(ans, used);
		return;
	}
	if(used >= ans) return;
	used++;
	int s=1;
	for(; s<=5; s++) {
		bool ok = 1;
		for(int r=i; r<i+s; r++)
			if(!arr[r][j+s-1]) ok = 0;
		for(int c=j; c<j+s; c++)
			if(!arr[i+s-1][c]) ok = 0;
		if(!ok)
			goto end;
		for(int r=i; r<i+s; r++)
			arr[r][j+s-1] = 0;
		for(int c=j; c<j+s; c++)
			arr[i+s-1][c] = 0;
		if(cnt[s]) {
			cnt[s]--;
			f(i, j+1);
			cnt[s]++;
		}
	}
	end:;
	s--;
	for(int r=i; r<i+s; r++) {
		for(int c=j; c<j+s; c++) {
			arr[r][c] = 1;
		}
	}
	used--;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=1; i<=5; i++) {
		cnt[i] = 5;
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			int t;
			cin >> t;
			arr[i][j] = t;
		}
	}
	f(0, 0);
	cout << (ans == 100 ? -1 : ans);
}
