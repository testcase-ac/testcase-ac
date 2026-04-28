#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9;
ll C[3005] = {1,1}, D[3005] = {0,0,0,0,1}, E[3005]={0,0,0,0,1};
int n;

int main(){
    cin >> n;
    if(n < 3){
        cout << 0 << ' ' << 0 << '\n';
        return 0;
    }
    for(int i = 2; i <= n; i++){
        for(int j = 0; j < n; j++) C[i] = (C[i] + C[j] * C[i-1-j]) % mod;
    }
    cout << C[n-2] << ' ';
    if(n & 1){
        cout << 0 << '\n';
        return 0;
    }
    for(int i = 6; i <= n; i += 2){
        E[i] = 2ll * D[i-2] % mod;
        for(int j = 4; j <= i-4; j += 2){
            E[i] = (E[i] + D[j] * D[i-j]) % mod;
        }
        D[i] = E[i] % mod;
        for(int j = 4; j <= i-2; j += 2){
            D[i] = (D[i] + E[j] * D[i+2-j]) % mod;
        }
    }
    cout << D[n] << '\n';
}
