#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 10);
    set<tuple<int, int, int>> s;
    while (s.size() < N) {
        int x = rnd.next(-9, 9), y = rnd.next(-9, 9), z = rnd.next(-9, 9);
        s.insert({x, y, z});
    }
    vector<tuple<int, int, int>> v(s.begin(), s.end());
    shuffle(v.begin(), v.end());
    println(N);
    for(auto [x, y, z]: v) {
        println(x, y, z);
    }
}
