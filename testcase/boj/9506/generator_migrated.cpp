#include <iostream>
#include <random>
#include <vector>
using namespace std;

vector<int> perfect_numbers = {6, 28, 496, 8128};
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 100000);

int main() {
    uniform_int_distribution<> perfect_dis(0, 5);

    while (true) {
        int random_value = dis(gen);
        
        if (random_value <= 10000) {
            cout << -1 << endl;
            break;
        }
        
        if (perfect_dis(gen) == 0) {
            cout << perfect_numbers[dis(gen) % perfect_numbers.size()] << endl;
        } else {
            cout << dis(gen) << endl;
        }
    }
}
