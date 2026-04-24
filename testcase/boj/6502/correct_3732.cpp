#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int t=1;;t++) {
		int a, b, c;
		scanf("%d", &a);
		if(!a) break;
		scanf("%d%d", &b, &c);
		printf("Pizza %d %s on the table.\n", t, (4*a*a>=b*b+c*c) ? "fits" : "does not fit");
	}
}
