#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

string generate_large_number(int digits) {
    string num;
    num += (rand() % 9 + 1) + '0';
    for (int i = 1; i < digits; i++) {
        num += (rand() % 10) + '0';
    }
    return num;
}
int main() {
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    int a_digits = rand() % 50 + 20;
    int b_digits = rand() % 50 + 20;
    string a = generate_large_number(a_digits);
    string b = generate_large_number(b_digits);
    cout << a << " " << b << endl;
    return 0;
}
