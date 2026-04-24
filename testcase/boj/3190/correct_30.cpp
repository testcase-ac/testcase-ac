#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
inline int newdir(int dir, char d) {
	if(d == 'L') return (dir+1)%4;
	else return (dir+3)%4;
}
int dr[] = {-1,0,1,0}, dc[] = {0,-1,0,1};
inline int isvalid(int r, int c, int n) {
	return r>=0 && r<n && c>=0 && c<n;
}
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int board[n][n]; set0(board);
	int k;
	cin >> k;
	while(k--) {
		int r, c;
		cin >> r >> c;
		r--,c--;
		board[r][c] = 2;
	}
	int L;
	cin >> L;
	vector<pair<int,char>> movement(L);
	rep(i, L) {
		char c;
		cin >> movement[i].first >> movement[i].second;
	}
	int dir = 3;
	int t = 0;
	int atmove = 0;
	vector<pair<int,int>> snake = {{0,0}};
	board[0][0] = 1;
	int posr = 0, posc = 0;
	while(++t) {
		posr += dr[dir];
		posc += dc[dir];
		if(!isvalid(posr, posc, n) || board[posr][posc] == 1)
			return !(cout << t);
		snake.emplace_back(posr, posc);
		if(board[posr][posc] != 2) {
			auto l = snake.front();
			board[l.first][l.second] = 0;
			snake.erase(snake.begin());
		}
		board[posr][posc] = 1;
		while(atmove < L && movement[atmove].first == t) {
			dir = newdir(dir, movement[atmove].second);
			atmove++;
		}
	}
}
