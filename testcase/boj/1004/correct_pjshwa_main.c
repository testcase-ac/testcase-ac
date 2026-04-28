#include <stdio.h>

int main(void){
    int t;
    int x1, y1, x2, y2;
    int n;
    int cx, cy, r;

    int innout;

    int x_sq1, y_sq1, x_sq2, y_sq2;

    scanf("%d", &t);
    for(int i = 0; i < t; i++){

        innout = 0;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        scanf("%d", &n);

        for(int j = 0; j < n; j++){
            scanf("%d %d %d", &cx, &cy, &r);
            x_sq1 = (x1-cx)*(x1-cx);
            y_sq1 = (y1-cy)*(y1-cy);
            x_sq2 = (x2-cx)*(x2-cx);
            y_sq2 = (y2-cy)*(y2-cy);
            if(x_sq1 + y_sq1 < r*r ^ x_sq2 + y_sq2 < r*r){
                innout++;
            }
        }

        printf("%d\n", innout);
    }
}