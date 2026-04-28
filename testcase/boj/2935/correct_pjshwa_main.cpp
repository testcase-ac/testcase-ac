#include <cstdio>
#include <cstring>

int main(){
    char a[101] = {0};
    char b[101] = {0};
    char op[2] = {0};
    scanf("%s%s%s", a, op, b);
    int p = strcmp(a, b);
    int sa = strlen(a);
    int sb = strlen(b);
    if(p > 0){
        if(!strcmp(op, "+")){
            a[sa-sb] = '1';
        }
        else{
            for(int i = sa; i < sa+sb-1; i++){
                a[i] = '0';
            }
        }
        printf("%s", a);
    }
    else if (p == 0){
        if(!strcmp(op, "+")){
            a[0] = '2';
        }
        else{
            for(int i = sa; i < sa+sb-1; i++){
                a[i] = '0';
            }
        }
        printf("%s", a);
    }
    else {
        if(!strcmp(op, "+")){
            b[sb-sa] = '1';
        }
        else{
            for(int i = sb; i < sa+sb-1; i++){
                b[i] = '0';
            }
        }
        printf("%s", b);
    }
    
}