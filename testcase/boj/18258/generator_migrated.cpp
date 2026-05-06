#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <chrono>
using namespace std;

static std::mt19937_64 seedRng;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device


int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> cmd_dist(1, 8);
    uniform_int_distribution<int> tc_dist(1, 100);
    uniform_int_distribution<int> num_dist(1, 100000);
    int n = tc_dist(gen);
    
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int cmd = cmd_dist(gen);
        if (cmd==1||cmd==7||cmd==8) {
            cout << "push " << num_dist(gen) << endl;
        } else if (cmd == 2) {
            cout << "pop" << endl;
        } else if (cmd == 3) {
            cout << "size" << endl;
        } else if (cmd == 4) {
            cout << "empty" << endl;
        } else if (cmd == 5) {
            // front
            cout << "front" << endl;
        } else if (cmd == 6) {
            // back
            cout << "back" << endl;
        }
    }
    return 0;
}
