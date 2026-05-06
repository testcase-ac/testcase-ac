#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < abs(n - 1 - i); j++) {
            cout << " ";
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << "*";
        }
        cout << endl;
    }
    for (int i = 0; i < 2 * n - 1; i++) {
        cout << "*";
    }
    cout << endl;
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < abs(n - 1 - i); j++) {
            cout << " ";
        }
        for (int j = 0; j < 2 * i + 1; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}
