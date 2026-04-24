#include <stdio.h>
#include <math.h>
#include <string.h>
#define min(x,y) ((x)<(y)?(x):(y))


int main() {
	double x, y, c;
	char b1[100], b2[100];
	while(scanf("%lf%lf%lf", &x, &y, &c) != EOF) {
		double l = 0, r = min(x,y), mid;
		while(1) {
			sprintf(b1, "%.3lf", l), sprintf(b2, "%.3lf", r);
			if(!strcmp(b1, b2)){
				printf("%s\n", b1);
				goto next;
			}
			mid = (l+r)/2;
			double val = c/sqrt(x*x-mid*mid)+c/sqrt(y*y-mid*mid);
			if(val >= 1) {
				r = mid;
			} else {
				l = mid;
			}
		}
		next:;
	}
}
