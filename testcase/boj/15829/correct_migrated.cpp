#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    
    char* b = new char[a + 1];
    unsigned long long int s = 0, n = 1;
    for (int i = 0; i < a; i++) {
        cin >> b[i];
        s = (s + (b[i] - 96) * n) % 1234567891;
        n = (n * 31) % 1234567891;
    }
    cout << s;
    
    return 0;
}
