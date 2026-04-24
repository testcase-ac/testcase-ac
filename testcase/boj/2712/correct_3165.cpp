#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		double t;
		string s;
		cin >> t >> s;
		if(s == "kg")
			printf("%.4f lb\n", t*2.2046);
		else if(s == "l")
			printf("%.4f g\n", t*0.2642);
		else if(s == "lb")
			printf("%.4f kg\n", t*0.4536);
		else
			printf("%.4f l\n", t*3.7854);
	}
}
