#include <bits/stdc++.h>
using namespace std;
int main() {
    long w,h,f,c,x1,y1,x2,y2;
    cin>>w>>h>>f>>c>>x1>>y1>>x2>>y2;
    long r=(c+1)*(x2-x1)*(y2-y1);
    if(f<=w/2) {
        if(f-x1>=0) {
            if(x2>f) r+=(c+1)*(f-x1)*(y2-y1);
            else r+=(c+1)*(x2-x1)*(y2-y1);
        }
    } else {
        if(w-x1-f>= 0) {
            if(x2+f>w) r+=(c+1)*(w-x1-f)*(y2-y1);
            else r+=(c+1)*(x2-x1)*(y2-y1);
        }
    } cout<<w*h-r;
}
