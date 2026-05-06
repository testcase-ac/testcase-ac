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
    uniform_int_distribution<> dis(0, 5);
    uniform_int_distribution<> len_dis(1, 50);
    uniform_int_distribution<> t_dis(1, 10);

    char L_color = 'W';
    char D_color = 'O';
    char B_color = 'R';
    char U_color = 'B';
    char F_color = 'G';
    char R_color = 'Y';

    char colors[] = {'W', 'O', 'R', 'B', 'G', 'Y'};

    int t = t_dis(gen);
    cout << t << endl;

    for (int test_case = 0; test_case < t; test_case++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? L_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? D_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? B_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? U_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? F_color : colors[dis(gen)]) << ' ';
            }
            for (int j = 0; j < 3; j++) {
                cout << (i == 1 && j == 1 ? R_color : colors[dis(gen)]) << ' ';
            }
            cout << endl;
        }
        string random_string = "";
        int len = len_dis(gen);
        for (int i = 0; i < len; i++) {
            random_string += colors[dis(gen)];
        }
        cout << random_string << endl;
    }

    return 0;
}
