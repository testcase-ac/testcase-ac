#include <cstdio>

long double abs(long double a){
	if(a >= 0) return a;
	else return -a;
}

int main(){
	long double a, b, prev_a, prev_b;
	scanf("%Lf%Lf", &a, &b);
	do {
		prev_a = a;
		prev_b = b;
		a = (prev_b + prev_a) / 2;
		b = 2 * prev_a * prev_b / (prev_b + prev_a);
	} while (abs(prev_a - a) >= 0.0001 && abs(prev_b - b) >= 0.0001);

	printf("%.3Lf %.3Lf", a, b);
} 