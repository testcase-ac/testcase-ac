#include <iostream>

int search(int* a, int x, int y1, int y2){
    if (y2 == y1){
        return y1;
    } else {
        int middle = (int)(y2+y1)/2;
        if (a[middle] >= x){
            return search(a,x,middle+1,y2);
        } else {
            return search(a,x,y1,middle);
        }
    }
}

int main(int argc, const char * argv[]) {
    
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    
    int N, Q;
    std::cin >> N;
    std::cin >> Q;
    
    int* a = new int[N];
    for (int i=0; i<N; i++){
        std::cin >> a[i];
    }
    
    int** r = new int*[Q];
    for (int i=0; i<Q; i++){
        r[i] = new int[2];
        std::cin >> r[i][0];
        std::cin >> r[i][1];
    }
    
    for (int i=0; i<Q; i++){
        int x = r[i][0] - 1;
        int y = r[i][1] - 1;
        int counter = 0;
        if (a[y] - 1 >= x){
            counter += (a[y] - 1) - x + 1;
            counter += search(a,x+1,y,N) - y - 1;
        }
        
        std::cout << counter << "\n";
    }
    
    return 0;
}
