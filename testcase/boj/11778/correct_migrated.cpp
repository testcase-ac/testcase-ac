#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;
void multiply(long long F[2][2], long long M[2][2]) {
    long long x = (F[0][0] * M[0][0] + F[0][1] * M[1][0]) % MOD;
    long long y = (F[0][0] * M[0][1] + F[0][1] * M[1][1]) % MOD;
    long long z = (F[1][0] * M[0][0] + F[1][1] * M[1][0]) % MOD;
    long long w = (F[1][0] * M[0][1] + F[1][1] * M[1][1]) % MOD;

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
void power(long long F[2][2], long long n) {
    long long M[2][2] = {{1, 1}, {1, 0}};
    while (n > 0) {
        if (n % 2 == 1) {
            multiply(F, M);
        }
        multiply(M, M);
        n /= 2;
    }
}
long long fibonacci(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long F[2][2] = {{1, 1}, {1, 0}};
    power(F, n - 1);

    return F[0][0];
}
long long gcd(long long a, long long b) {
    while(a!=b) {
        if(a>b) {
            if(a%b==0) return b;
            else a%=b;
        } else {
            if(b%a==0) return a;
            else b%=a;
        }
    } return a;
}
int main() {
    long long a,b;
    cin>>a>>b;
    if(a==1||b==1) cout<<1;
    else cout<<fibonacci(gcd(a,b)-1);
}
