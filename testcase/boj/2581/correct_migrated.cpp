#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a,b,c=0;
    cin >> a;
    cin >> b;
    int d=b;
    vector<bool> prime(b + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= b; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= b; j += i) {
                prime[j] = false;
            }
        }
    }
    for (int i = a; i <= b; i++) {
        if (prime[i]) {
            c+=i;
            d=min(d,i);
        }
    } if(c==0) {
        cout << -1;
        return 0;
    }
    cout << c << endl << d;
}
