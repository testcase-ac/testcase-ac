#include<bits/stdc++.h>
using namespace std;

stack<int> d[30];
string Map[30000];
int N, M;

void update(int idx){
	int y = 0, x = idx;
	if(!d[idx].empty()){
		int cur = d[idx].top();
		x = cur % M; y = cur / M;
	}
	while(y < N){
		d[idx].push(y * M + x);
		if(y != N - 1 && Map[y + 1][x] == 'X') return;
		else if(y != N - 1 && Map[y + 1][x] == 'O'){
			if(x > 0 && Map[y][x-1] == '.' && Map[y+1][x-1] == '.')x--;
			else if(x < M - 1 && Map[y][x+1] == '.' && Map[y+1][x+1] == '.')x++;
			else return;
		}
		y++;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for(int i=0;i<N;i++)cin >> Map[i];
	int q; cin >> q;
	while(q--){
		int idx; cin >> idx; --idx;
		int c,y,x;
		while(true){
			if(d[idx].empty())break;
			c=d[idx].top();
			y=c/M,x=c%M;
			if(Map[y][x]=='.')break;
			d[idx].pop();
		}
		update(idx);
		c=d[idx].top();
		y=c/M,x=c%M;
		Map[y][x]='O';
		d[idx].pop();
	}
	for(int i=0;i<N;i++)cout<<Map[i]<<'\n';
	return 0;
}
