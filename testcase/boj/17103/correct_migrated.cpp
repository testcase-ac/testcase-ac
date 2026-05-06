#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<bool> sieve(int max_val) {
    vector<bool> is_prime(max_val + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i <= sqrt(max_val); i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max_val; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

int main() {
    int n, a;
    cin >> n;
    int max_val = 1000000;
    vector<bool> is_prime = sieve(max_val);
    
    while (n--) {
        cin >> a;
        int b = 0;
        for (int j = 2; j <= a / 2; j++) {
            if (is_prime[j] && is_prime[a - j] && j != 1 && (a - j) != 1) {
                b++;
            }
        }
        
        cout << b << endl;
    }
}
