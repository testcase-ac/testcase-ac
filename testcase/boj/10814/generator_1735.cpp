#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(3, 20);
    vector<string> names(N);
    if(rnd.next(0, 1)) {
        for(int i = 0; i < N; i++) {
            names[i] = (char)('A' + i);
        }
    } else {
        set<string> used;
        for(int i = 0; i < N; i++) {
            string name;
            do {
                name = rnd.next("[a-z]{1,3}");
            } while(used.count(name));
            used.insert(name);
            names[i] = name;
        }
    }
    shuffle(names.begin(), names.end());
    println(N);
    int age_min = rnd.next(1, 80);
    int age_max = rnd.next(age_min, age_min+5);
    for(int i = 0; i < N; i++) {
        println(rnd.next(age_min, age_max), names[i]);
    }
}
