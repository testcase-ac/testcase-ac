#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 6);
    vector<int> colors;
    for (int i = 1; i <= 6; i++) {
        for (int j = 0; j < 4; j++) {
            colors.push_back(i);
        }
    }
    shuffle(colors.begin(), colors.end(), gen);
    for (int i = 0; i < 24; i++) {
        cout << colors[i] << " ";
    }
}
