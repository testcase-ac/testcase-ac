#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_a(1, 1000);
    uniform_int_distribution<> dis_b(1, 999);
    uniform_int_distribution<> dis_v(1, 1000000000);
    
    int A = dis_a(gen);
    int B = dis_b(gen);
    int V = dis_v(gen);
    
    while (A <= B || V <= A) {
        A = dis_a(gen);
        B = dis_b(gen);
        V = dis_v(gen);
    }
    cout << A << " " << B << " " << V << endl;
    return 0;
}
