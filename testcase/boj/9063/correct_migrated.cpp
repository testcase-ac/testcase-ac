#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a,b=-10000,c=10000,d=-10000,e=10000;
    cin >> a;
    int x[a],y[a];
    for(int i=0;i<a;i++) {
        cin >> x[i] >> y[i];
        b=max(b,x[i]);
        c=min(c,x[i]);
        d=max(d,y[i]);
        e=min(e,y[i]);
    } cout << (b-c)*(d-e);
}
