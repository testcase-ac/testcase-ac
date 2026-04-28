#include <cstdio>
long long a, p, T;
int mu;
long long po(long long v)
{
    if(v==1) return a;
    long long S=po(v/2)%p;
    S=(S*S)%p;
    S*=(v&1)?(a):(1);
    return S%p;
}
int main()
{
    scanf("%d",&T);
    int god;
    for(int c=1;c<=T;c++)
    {
        god=1;
        scanf("%lld %lld",&a,&p);
        if(a<0)
        {
            a+=(p*(a/p)+p);
        }
        a%=p;
        if(!a) god=0;
        else god=po((p-1)/2);
        if(god>1) god-=p;
        printf("Scenario #%d:\n%d\n\n",c,god);
    }
    return 0;
}
