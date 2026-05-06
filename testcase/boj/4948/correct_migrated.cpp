#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int b,a=0;
    while(1) {
        cin >> b;
        if(b==0) {
            break;
        }
        vector<bool> prime(2*b + 1, true);
        prime[0] = prime[1] = false;
        for (int i = 2; i * i <= 2*b; i++) {
            if (prime[i]) {
                for (int j = i * i; j <= 2*b; j += i) {
                    prime[j] = false;
                }
            }
        }
        for (int i = b+1; i <= 2*b; i++) {
            if (prime[i]) {
                a+=1;
            }
        } cout << a << endl;
        a=0;
    }
}
