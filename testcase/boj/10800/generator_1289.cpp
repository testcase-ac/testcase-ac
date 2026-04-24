#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(2, 8);
    println(N);
    vector<int> colors;
    for(int i=1; i<=N; i++) {
        colors.push_back(i);
    }
    shuffle(colors.begin(), colors.end());
    int color_count = rnd.next(1, N);
    colors.resize(color_count);

    vector<int> sizes;
    for(int i=1; i<=10; i++) {
        sizes.push_back(i);
    }
    shuffle(sizes.begin(), sizes.end());
    int size_count = rnd.next(1, 10);
    sizes.resize(size_count);
    
    for (int i = 0; i < N; i++) {
        int color = colors[rnd.next(0, color_count - 1)];
        int size = sizes[rnd.next(0, size_count - 1)];
        println(color, size);
    }
    
    return 0;
}
