#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int cards[12];
	for(int i=2; i<10; i++)
		cards[i] = 4;
	cards[10] = 16;
	cards[11] = 4;
	int sum = 0, cnt = 0;
	while(n--) {
		int t;
		cin >> t;
		cards[t]--;
		cnt++;
		sum += t;
	}
	int x = 21-sum, small = 0;
	for(int i=2; i<=min(x,11); i++)
		small += cards[i];
	if(small <= (52-cnt-small))
		cout << "DOSTA";
	else
		cout << "VUCI";
}
