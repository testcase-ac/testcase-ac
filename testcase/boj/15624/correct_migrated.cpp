#include <iostream>
using namespace std;
int main() {
    int a;
    cin >> a;
    long long f[a+1]={0,1};
    for(int i=2; i<a+1;i++){
        f[i]=(f[i-1]+f[i-2])%1000000007;
    }
    cout <<f[a];
}
