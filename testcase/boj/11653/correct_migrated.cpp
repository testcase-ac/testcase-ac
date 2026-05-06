#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
    int a;
    cin >> a;

    vector<int> factors;

    while (a % 2 == 0) {
        factors.push_back(2);
        a /= 2;
    }
    int limit = sqrt(a);
    for (int i = 3; i <= limit; i += 2) {
        while (a % i == 0) {
            factors.push_back(i);
            a /= i;
        }
    }
    if (a > 1) {
        factors.push_back(a);
    }
    for (int i = 0; i < factors.size(); i++) {
        cout << factors[i] << endl;
    }

    return 0;
}
