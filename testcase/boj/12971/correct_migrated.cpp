#include<iostream>
using namespace std;

int r, p1, p2, p3, x1, x2, x3;

int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a%b);
}

int main(){
	cin >> p1 >> p2 >> p3 >> x1 >> x2 >> x3;
	r = p1*p2/gcd(p1,p2);
	r = r*p3/gcd(r,p3);
	for(int i = x1; i <= r; i += p1){
		if(i%p2 == x2 && i%p3 == x3){
			cout << i;
			return 0;
		}
	}
	cout << -1;
}
