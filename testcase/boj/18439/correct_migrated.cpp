#include <iostream>
using namespace std;
char o[50010];
char u[50010];
unsigned long long s[256][784];
unsigned long long d[50010];
int main() {
    int n, m;
    cin >> o;
    cin >> u;
    for(n = 0; o[n] != 0; n++);
    for(m = 0; u[m] != 0; m++);

    int c = (m >> 6) + 1;
    for(int i = 0; i < m; i++) s[u[i]][i >> 6] |= 1llu << (i & 63);

    for(int i = 0; i < m; i++) if(o[0] == u[i]) { d[i >> 6] |= 1llu << (i & 63); break; }

    for(int i = 1; i < n; i++) {
        unsigned long long left_carry = 1;
        unsigned long long minus_carry = 0;
    
        for(int j = 0; j < c; j++) {
            unsigned long long x = s[o[i]][j] | d[j];

            unsigned long long tmp1 = (d[j] << 1) | left_carry;
            left_carry = d[j] >> 63;

            auto sub_carry = [](unsigned long long &x, unsigned long long y){
                unsigned long long tmp = x;
                return (x = tmp - y) > tmp;
            };

            unsigned long long tmp2 = x;
            minus_carry = sub_carry(tmp2, minus_carry);
            minus_carry += sub_carry(tmp2, tmp1);

            d[j] = x & (x ^ tmp2);
        }

        d[m >> 6] &= (1llu << (m & 63)) - 1;
    } int ans = 0;
    for(int i = 0; i < m; i++) if(d[i >> 6] & (1llu << (i & 63))) ans++;
    cout << ans;
    return 0;
}
