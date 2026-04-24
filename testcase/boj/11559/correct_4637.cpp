#include <bits/stdc++.h>
using namespace std;

string arr[12];
void fall() {
	for(int c=0; c<6; c++) {
		int nextr = 11;
		for(int r=11; r>=0; r--) {
			if(arr[r][c] != '.')
				swap(arr[r][c], arr[nextr--][c]);
		}
	}
}
int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
int parent[72], setsz[72];
int find(int i) {return i == parent[i] ? i : parent[i] = find(parent[i]);}
void join(int i, int j) {
	i = find(i), j = find(j);
	if(i != j) {
		parent[i] = j;
		setsz[j] += setsz[i];
	}
}
bool isvalid(int i, int j) {return 0 <= i && i < 12 && 0 <= j && j < 6;}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<12; i++) {
		cin >> arr[i];
	}
	int t = 0;
	while(1) {
		fall();
		for(int i=0; i<72; i++) {
			parent[i] = i;
			setsz[i] = 1;
		}
		
		for(int r=0; r<12; r++) {
			for(int c=0; c<6; c++) {
				for(int i=0; i<4; i++) {
					int tr = r+dr[i], tc = c+dc[i];
					if(isvalid(tr,tc) && arr[r][c] == arr[tr][tc] && arr[r][c] != '.') {
						join(r*6+c, tr*6+tc);
					}
				}
			}
		}
		bool boom = false;
		for(int r=0; r<12; r++) {
			for(int c=0; c<6; c++) {
				if(setsz[find(r*6+c)] >= 4) {
					boom = true;
					arr[r][c] = '.';
				}
			}
		}
		if(!boom) return !(cout << t);
		t++;
	}
}
