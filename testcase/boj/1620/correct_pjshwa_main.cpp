#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;
string c[100001];
 
map<string, int> abc;
 
int main(void){
    int N, M;
 
    scanf("%d %d", &N, &M);
 
    for (int i = 0; i < N; i++){
        char name[30];
        scanf("%s", name);
        c[i] = name;
        abc.insert(map<string, int>::value_type(c[i], i));
    }
 
 
 
    for (int i = 0; i < M; i++)
    {
        int num=0;
        char cc;
        string s;
        char name[30];
        scanf("%s", name);
        s=name;
 
 
        cc = s[0];
        if (cc >= '0' && cc <= '9')
        {
            for (int i = 0; s[i] != 0; i++)
            {
                num *= 10;
                num += s[i] - '0';
            }
             printf("%s\n", c[num - 1].c_str());
        }
        else
        {
            int left = 0, right = N - 1;
            int result;
            result = abc[s];
 
            printf("%d\n", result + 1);
        }
 
    }
}
