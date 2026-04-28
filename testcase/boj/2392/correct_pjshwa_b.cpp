#define forin(i, n) for(int i{0}; i < n; ++i)
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
template <int p>
struct Z_p{
    static int _c[256];
    static const int prim;
    int v;
    static int euc(int a){ // ax + by = g = 1, find x
        int b = p, i = 0;
        while(b){
            _c[i] = a / b;
            ++i;
            int tmp = a;
            a = b;
            b = tmp % b;
        }
        int x = 0, y = 1, tmp;
        for(i -= 2; i >= 0; --i){
            tmp = y;
            y = x - _c[i] * y;
            x = tmp;
        }
        if(x < 0) x += p;
        return x;
    }
    Z_p(int a = 0) noexcept:v(a){}
    Z_p operator+(const Z_p & other) const{
        int tmp = v - p + other.v;
        if(tmp < 0) tmp += p;
        return tmp;
    }
    Z_p& operator+=(const Z_p & other){
        v += other.v - p;
        if(v < 0) v += p;
        return *this;
    }
    Z_p operator-(const Z_p & other) const{
        int tmp = v - other.v;
        if(tmp < 0) tmp += p;
        return tmp;
    }
    Z_p& operator-=(const Z_p & other){
        v -= other.v;
        if(v < 0) v += p;
        return *this;
    }
    Z_p operator*(const Z_p & other) const{
        return (long long)v * other.v % p;
    }
    Z_p &operator*=(const Z_p & other){
        v = (long long)v * other.v % p;
        return *this;
    }
    Z_p operator/(const Z_p & other) const{
        return (long long)v * euc(other.v) % p;
    }
    Z_p &operator/=(const Z_p & other){
        v = (long long)v * euc(other.v) % p;
        return *this;
    }
    bool operator==(const Z_p & other) const{
        return v == other.v;
    }
    static Z_p pow(Z_p base, int exp){
        Z_p ans = 1;
        while(exp){
            if(exp & 1) ans *= base;
            base *= base;
            exp >>= 1;
        } return ans;
    }
};
template<int p>
Z_p<p> operator-(const Z_p<p>& self){
    return self.v == 0 ? 0 : p - self.v;
}
template<int p>
ostream& operator<<(ostream &f, const Z_p<p> &x){
return f << x.v;
}
template<int p>
istream& operator>>(istream &f, Z_p<p> &x){
    return f >> x.v;
}
constexpr int mod = 1e9;
using Zm = Z_p<mod>;
template<> int Zm::_c[256] = {};

Zm C[1005] = {1, 1, 2};
Zm q[501] = {1, 0, 1};
Zm s[501] = {0, 0, 1};
int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    if (n < 3) { cout << "0\n0"; return 0; }
    if (n == 3) { cout << "1\n0"; return 0; }

    for (int i = 3; i <= n; i++){
        for (int j = 0; j < i / 2; j++)
            C[i] += C[j] * C[i - 1 - j];
        C[i] *= 2;
        if(i & 1) C[i] += C[i / 2]*C[i / 2];
    }
    for(int i = 3; i <= n / 2; ++i){
        for(int j = 2; j < i - 1; ++j){
            s[i] += q[j] * q[i - j];
        }
        q[i] = (s[i] + q[i-1]) * 3;
        for (int j = 2; j <= i - 2; ++j){
            q[i] += q[j] * s[i-j+1];
        }
    }

    cout << C[n - 2] << '\n' << (n & 1 ? 0 : q[n / 2]);
}
