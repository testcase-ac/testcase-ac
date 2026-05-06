#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> n_dist(1, 123456);
    uniform_int_distribution<> chance_dist(1, 5);
    int x=0;
    while (true) {
        int n = n_dist(gen);
        x+=1;
        if (chance_dist(gen)==5 || x==15) {
            cout << "0\n";
            break;
        }
        cout << n << "\n";
    }
}
