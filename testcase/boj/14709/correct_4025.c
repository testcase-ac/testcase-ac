#include <stdio.h>
#define SUCCESS "Wa-pa-pa-pa-pa-pa-pow!"
#define FAIL "Woof-meow-tweet-squeek"

int main() {
    int num;
    int has13=0, has14=0, has34=0;
    int d1, d2;
    scanf("%d", &num);
    for(int i=0; i<num; i++) {
        scanf("%d %d", &d1, &d2);
        if((d1 == 1 && d2 == 3) || (d1 == 3 && d2 == 1))
            has13 = 1;
        else if((d1 == 1 && d2 == 4) || (d1 == 4 && d2 == 1))
            has14 = 1;
        else if((d1 == 3 && d2 == 4) || (d1 == 4 && d2 == 3))
            has34 = 1;
    }
    if((num == 3) && (has13 && has14 && has34))
        printf(SUCCESS);
    else
        printf(FAIL);
    return 0;
}
