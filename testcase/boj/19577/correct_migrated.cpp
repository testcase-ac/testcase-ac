#include <bits/stdc++.h>
using namespace std;

vector<long> divisor;

void getDivisor(long long n) {
    for (long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            divisor.push_back(i);
            divisor.push_back(n / i);
        }
    }
    divisor.push_back(n);
}

long long phi(long long n) {
    long long res = n;

    for (long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            res = res - res / i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        res = res - res / n; 
    }

    return res;
}

int main() {
    long long n;
    cin >> n;
    if (n == 1) {
        cout<<1;
        return 0;
    }
    getDivisor(n);
    for (unsigned long long i = 0; i < divisor.size(); i++) {
        if (divisor[i]*phi(divisor[i]) == n) {
            cout << divisor[i];
            return 0;
        }
    } cout<<-1;
}
