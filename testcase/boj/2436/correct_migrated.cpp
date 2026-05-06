#include <iostream>
#include <cmath>
using namespace std;

long long gc(long long a,long long b) {
	while (b!=0) {
		long long t=b;
		b=a%b;
		a=t;
	}
	return a;
}
int main() {
	long long gcd,lcm;
	cin>>gcd>>lcm;

	long long n=lcm/gcd;
	long long a=gcd,b=lcm;
	long long min_diff=lcm;

	for (long long x=1;x*x<=n;x++) {
		if (n%x==0) {
			long long y=n/x;
			if (gc(x,y)==1) {
				long long temp_a=gcd*x;
				long long temp_b=gcd*y;
				if(abs(temp_a-temp_b)<min_diff) {
					a=temp_a;
					b=temp_b;
					min_diff=abs(temp_a-temp_b);
				}
			}
		}
	}
	cout<<a<<' '<<b<<"\n";
}
