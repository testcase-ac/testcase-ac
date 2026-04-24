#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#define rep(i,n) for(int i=0; i<n; i++)
using namespace std;

int main() {
	int a[10], b[10];
	rep(i,10) cin >> a[i];
	rep(i,10) cin >> b[i];
	int asc = 0, bsc = 0;
	char last = 'D';
	rep(i,10) {
		if(a[i] > b[i]) asc += 3, last = 'A';
		else if(a[i] < b[i]) bsc += 3, last = 'B';
		else asc += 1, bsc += 1;
	}
	cout << asc << ' ' << bsc << '\n';
	if(asc > bsc) cout << 'A';
	else if(asc < bsc) cout << 'B';
	else cout << last;
    
}
