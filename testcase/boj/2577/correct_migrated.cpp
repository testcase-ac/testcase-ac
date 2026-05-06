#include <iostream>
#include <string>
using namespace std;
int main() {
    int a,b,c,e,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9;
    x0=0;
    x1=0;
    x2=0;
    x3=0;
    x4=0;
    x5=0;
    x6=0;
    x7=0;
    x8=0;
    x9=0;
    cin >> a;
    cin >> b;
    cin >> c;
    string d=to_string(a*b*c);
    e=d.size();
    for(int i=0;i<e;i++) {
        if(d[i]=='1') {
            x1+=1;
        } else if(d[i]=='2') {
            x2+=1;
        } else if(d[i]=='3') {
            x3+=1;
        } else if(d[i]=='4') {
            x4+=1;
        } else if(d[i]=='5') {
            x5+=1;
        } else if(d[i]=='6') {
            x6+=1;
        } else if(d[i]=='7') {
            x7+=1;
        } else if(d[i]=='8') {
            x8+=1;
        } else if(d[i]=='9') {
            x9+=1;
        } else if(d[i]=='0') {
            x0+=1;
        }
    } cout << x0 << "\n" << x1 << "\n" << x2 << "\n" << x3 << "\n" << x4 << "\n" << x5 << "\n" << x6 << "\n" << x7 << "\n" << x8 << "\n" << x9;
}
