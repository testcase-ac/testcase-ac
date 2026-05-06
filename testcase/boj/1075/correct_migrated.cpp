#include <iostream>
using namespace std;
int main() {
    int n,f;
    cin>>n>>f;
    n-=n%100;
    for(int i=0;i<99;i++) {
        if((n+i)%f==0) {
            if(i<10) {
                cout<<0<<i;
                return 0;
            } else {
                cout<<i;
                return 0;
            }
        }
    }
}
