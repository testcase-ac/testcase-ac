#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int T = rnd.next(1, 2);
    println(T);
    
    for (int t = 0; t < T; t++) {
        int k = rnd.next(1, 10);
        println(k);
        
        for (int i = 0; i < k; i++) {
            if (rnd.next(1, 100) <= 70) {
                // Insert operation
                int num = rnd.next(-5, 5);
                println("I", num);
            } else {
                // Delete operation: 1 for max, -1 for min
                int d = rnd.next(0, 1) * 2 - 1;
                println("D", d);
            }
        }
    }
    
    return 0;
}
