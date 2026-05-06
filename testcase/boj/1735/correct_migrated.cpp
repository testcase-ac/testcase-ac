#include <iostream>
using namespace std;
int main() {
    int a,b,c,d,e,t;
    cin >> a >> b;
    cin >> c >> d;
    int x=b,y=d;
    while(x!=y) {
        if(x>y) {
            x=x-y;
        } else {
            y=y-x;
        }
    } e=b*d/x;
    t=c*b/x+a*d/x;
    int f=t,g=e;
    while(f!=g) {
        if(f>g) {
            f=f-g;
        } else {
            g=g-f;
        }
    } cout << t/g << ' ' << e/g;
}
