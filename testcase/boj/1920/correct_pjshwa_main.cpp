#include <cstdio>
#include <algorithm>
using namespace std;


int main(void){
    int n, m;
    
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    int number;
    scanf("%d", &m);

    for(int i = 0; i < m; i++){
        scanf("%d", &number);
        printf("%d\n", binary_search(a, a + n, number)?1:0);
    }


    return 0;
}