#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a,b=0,c=0,d=0;
    cin >> a;
    int r[2][a],s[200][200];
    for(int i=0;i<a;i++) {
        cin >> r[0][i] >> r[1][i];
        b=max(b,r[0][i]+10);
        c=max(c,r[1][i]+10);
        for(int j=r[0][i];j<r[0][i]+10;j++) {
            for(int k=r[1][i];k<r[1][i]+10;k++) {
                s[j][k]=1;
            }
        }
    } for(int i=0;i<b;i++) {
        for(int j=0;j<c;j++) {
            if(s[i][j]==1) {
                d+=1;
            }
        }
    } cout << d;
}
