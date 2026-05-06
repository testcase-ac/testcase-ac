#include <bits/stdc++.h>
using namespace std;
int main() {
	random_device rd;
	mt19937_64 g(rd());
    uniform_int_distribution<int> n(2,6);
    int a[6];
    while(1) {
        for(int i=0;i<6;i++) a[i]=n(g);
        if(a[0]*2-a[3]*2+a[1]-a[2]-a[4]+a[5]==0&&a[1]+a[2]==a[4]+a[5]) break;
    } cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<' '<<a[4]<<' '<<a[5];
}
