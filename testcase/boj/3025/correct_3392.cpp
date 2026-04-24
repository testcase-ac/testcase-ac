#include <bits/stdc++.h>
using namespace std;
char arr[30000][31];
int r, c;
struct Point {int r, c;};
Point table[30000][30];
vector<Point> chain[30];
bool nxt(Point &pt) {
	if(pt.r == r-1 || arr[pt.r+1][pt.c] == 'X') return 0;
	if(arr[pt.r+1][pt.c] == '.') {
		pt.r++;
		return 1;
	}
	if(pt.c && arr[pt.r][pt.c-1] == '.' && arr[pt.r+1][pt.c-1] == '.') {
		pt.r++, pt.c--;
		return 1;
	}
	if(pt.c < c-1 && arr[pt.r][pt.c+1] == '.' && arr[pt.r+1][pt.c+1] == '.') {
		pt.r++, pt.c++;
		return 1;
	}
	return 0;
}
void extend(int i) {
	Point p = chain[i].back();
	while(nxt(p))
		chain[i].push_back(p);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> r >> c;
	for(int i=0; i<r; i++) {
		cin >> arr[i];
	}
	for(int j=0; j<c; j++) {
		chain[j].push_back({0,j});
		extend(j);
	}
	int n, t;
	cin >> n;
	while(n--) {
		cin >> t;
		t--;
		while(arr[chain[t].back().r][chain[t].back().c] == 'O')
			chain[t].pop_back();
		extend(t);
		arr[chain[t].back().r][chain[t].back().c] = 'O';
		chain[t].pop_back();
		if(!chain[t].empty()) extend(t);
	}
	for(int i=0; i<r; i++) {
		cout << arr[i] << '\n';
	}
}
