#include <iostream>
#include <math.h>
using namespace std;
#define type double
int main() {
	int d, h, w;
	cin >> d >> h >> w;
	type t = sqrt((type)(d*d)/(h*h+w*w));
	cout << (int)(h*t) << ' ' << (int)(w*t);
}
