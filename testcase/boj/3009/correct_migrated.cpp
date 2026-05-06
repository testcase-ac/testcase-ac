#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a,b,r[3],s[3];
    for(int i=0;i<3;i++) {
        cin >> r[i] >> s[i];
    } if(count(r,r+3,r[0])==1) {
        a=r[0];
    } else if(count(r,r+3,r[1])==1) {
        a=r[1];
    } else {
        a=r[2];
    } if(count(s,s+3,s[0])==1) {
        b=s[0];
    } else if(count(s,s+3,s[1])==1) {
        b=s[1];
    } else {
        b=s[2];
    } cout << a << ' ' << b;
}
