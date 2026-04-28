#include <cstdio>
#include <cmath>
#include <algorithm>

int main(){
	int xa, ya, xb, yb, xc, yc;
	scanf("%d%d%d%d%d%d", &xa, &ya, &xb, &yb, &xc, &yc);
	if((yb-ya)*(xc-xb) == (yc-yb)*(xb-xa)) printf("-1");
	else{
		double ab, ac, bc;
		ab = sqrt((xb-xa)*(xb-xa)+(yb-ya)*(yb-ya));
		ac = sqrt((xc-xa)*(xc-xa)+(yc-ya)*(yc-ya));
		bc = sqrt((xc-xb)*(xc-xb)+(yb-yc)*(yb-yc));
		double length[3] = {2*(ab+ac),2*(ab+bc),2*(ac+bc)};
		std::sort(length, length+3);
		printf("%.10f", length[2] - length[0]);
	}
}