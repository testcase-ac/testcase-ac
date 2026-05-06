#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int a,b,c=0,d=0;
    cin >> a;
    for(int i=0;i<a;i++) {
        cin >> b;
        if(b==1) {
            continue;
        }
        for(int j=2;j<=sqrt(b);j++) {
            if((b%j)==0) {
                d=1;
                break;
            } 
        } if(d==1) {
            d=0;
            continue;
        } c+=1;
    } cout << c;
}
