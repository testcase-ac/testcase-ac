#include <iostream>
#include <stdio.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int h, w, n, fl, room;
		cin >> h >> w >> n;
		fl = ((n-1)%h)+1;
		room = (n-1)/h+1;
		cout << fl;
		if(room < 10) cout << 0;
		cout << room << '\n'; 
	}
}
