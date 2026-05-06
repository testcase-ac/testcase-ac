#include <iostream>
using namespace std;

int main() {
    long long a;
    cin >> a;
    int b=1500000;
    int f[b+1]={0,1};
    for(int i=2; i<b;i++){
        f[i]=(f[i-1]+f[i-2])%1000000;
    }
    cout <<f[a%b];
}
