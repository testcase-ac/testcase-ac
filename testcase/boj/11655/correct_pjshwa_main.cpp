#include <cstdio>
#include <cstring>
int main(){
    char s[101];
    scanf("%[^\n]%*c", s);
    int l = strlen(s);
    for(int i = 0; i < l; i++){
        if(s[i] >= 65 && s[i] <= 90){
            s[i] %= 65;
            s[i] += 13;
            s[i] %= 26;
            s[i] += 65;
        }
        else if(s[i] >= 97 && s[i] <= 122){
            s[i] %= 97;
            s[i] += 13;
            s[i] %= 26;
            s[i] += 97;
        }
    }
    printf("%s", s);
}