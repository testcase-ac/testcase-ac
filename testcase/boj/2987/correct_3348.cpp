#include <bits/stdc++.h>
using namespace std;
struct Pt {
	int x, y;
	Pt operator- (Pt &p) {
		return {x-p.x, y-p.y};
	}
};
int area2(Pt a, Pt b, Pt c) {
	return abs(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));
}
Pt t[3], p;
int main() {
	for(int i=0; i<3; i++) {
		scanf("%d%d", &t[i].x, &t[i].y);
	}
	printf("%.1f\n", area2(t[0], t[1], t[2])/2.);
	int n, ans = 0;
	cin >> n;
	while(n--) {
		cin >> p.x >> p.y;
		if(area2(t[0], t[1], p)+area2(t[1], t[2], p)+area2(t[2], t[0], p) == area2(t[0], t[1], t[2]))
			ans++;
	}
	printf("%d", ans);
}
