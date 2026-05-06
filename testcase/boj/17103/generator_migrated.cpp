#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> t_dist(1, 15);
    uniform_int_distribution<> n_dist(2, 500000);

    int T = t_dist(gen);
    cout << T << "\n";

    for (int i = 0; i < T; i++) {
        int N;
        N = 2*n_dist(gen);
        cout<<N<<"\n";
    }
}
