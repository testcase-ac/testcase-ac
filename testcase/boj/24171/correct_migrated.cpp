#include <stdio.h>

typedef struct {
    long long a,b,c,d;
} frac;

typedef struct {
    frac f0,f1;
} comp;

long long gcd(long long a,long long b){
    if(a<0)a=-a;
    if(b<0)b=-b;
    if(!b) return a;
    return gcd(b,a%b);
}

frac fplus(frac x,frac y){
    frac r;
    r.a=x.a*y.a;
    r.b=x.b*y.a + x.a*y.b;
    r.c=x.c*y.a + x.a*y.c;
    r.d=x.d?x.d:y.d;

    long long g=gcd(gcd(r.a,r.b),r.c);
    if(g>1){
        r.a/=g; r.b/=g; r.c/=g;
    }
    if(!r.c) r.d=0;
    return r;
}

frac frev(frac x){
    x.b=-x.b;
    x.c=-x.c;
    return x;
}

frac fminus(frac x,frac y){
    return fplus(x,frev(y));
}

frac fmult(frac x,frac y){
    frac r;
    r.a=x.a*y.a;

    if(!x.d && !y.d){
        r.b=x.b*y.b;
        r.c=0;
        r.d=0;
    }
    else if(!x.d){
        r.b=x.b*y.b;
        r.c=x.b*y.c;
        r.d=y.d;
    }
    else if(!y.d){
        r.b=x.b*y.b;
        r.c=x.c*y.b;
        r.d=x.d;
    }
    else{
        r.b=x.b*y.b + x.c*y.c*x.d;
        r.c=x.c*y.b + x.b*y.c;
        r.d=x.d;
    }

    long long g=gcd(gcd(r.a,r.b),r.c);
    if(g>1){
        r.a/=g; r.b/=g; r.c/=g;
    }
    if(!r.c) r.d=0;
    return r;
}

comp cplus(comp x,comp y){
    comp r;
    r.f0=fplus(x.f0,y.f0);
    r.f1=fplus(x.f1,y.f1);
    return r;
}

comp crev(comp x){
    x.f0.b=-x.f0.b;
    x.f0.c=-x.f0.c;
    x.f1.b=-x.f1.b;
    x.f1.c=-x.f1.c;
    return x;
}

comp cmult(comp x,comp y){
    comp r;
    r.f0=fminus(fmult(x.f0,y.f0),fmult(x.f1,y.f1));
    r.f1=fplus(fmult(x.f0,y.f1),fmult(x.f1,y.f0));
    return r;
}

comp cinv(comp x){
    long long d=x.f0.d?x.f0.d:x.f1.d;

    long long p=(x.f1.a*x.f1.a*x.f0.b*x.f0.b)+(x.f0.a*x.f0.a*x.f1.b*x.f1.b);
    p+=d*((x.f1.a*x.f1.a*x.f0.c*x.f0.c)+(x.f0.a*x.f0.a*x.f1.c*x.f1.c));

    long long q=2*(x.f1.a*x.f1.a*x.f0.b*x.f0.c + x.f0.a*x.f0.a*x.f1.b*x.f1.c);

    comp r={{p*p-d*q*q,x.f0.a*x.f1.a,0,0},{1,0,0,0}};
    comp t={{1,p,-q,d},{1,0,0,0}};
    r=cmult(r,t);

    comp t2={{1,x.f1.a*x.f0.b,x.f1.a*x.f0.c,d},
             {1,-x.f0.a*x.f1.b,-x.f0.a*x.f1.c,d}};
    r=cmult(r,t2);

    return r;
}

comp cdiv(comp x,comp y){
    return cmult(x,cinv(y));
}

void printcomp(comp x){
    printf("%lld %lld %lld %lld ",x.f0.a,x.f0.b,x.f0.c,x.f0.d);
    printf("%lld %lld %lld %lld\n",x.f1.a,x.f1.b,x.f1.c,x.f1.d);
}

int main(){
    comp x,y;

    scanf("%lld %lld %lld %lld",&x.f0.a,&x.f0.b,&x.f0.c,&x.f0.d);
    scanf("%lld %lld %lld %lld",&x.f1.a,&x.f1.b,&x.f1.c,&x.f1.d);
    scanf("%lld %lld %lld %lld",&y.f0.a,&y.f0.b,&y.f0.c,&y.f0.d);
    scanf("%lld %lld %lld %lld",&y.f1.a,&y.f1.b,&y.f1.c,&y.f1.d);

    printcomp(cplus(x,y));
    printcomp(cplus(x,crev(y)));
    printcomp(cmult(x,y));
    printcomp(cdiv(x,y));
}
