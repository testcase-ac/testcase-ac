// md5
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* MD5 context */
typedef struct {
    uint32_t h[4];
    uint8_t  buf[64];
    uint64_t bits;
} MD5_CTX;

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROL(x,n) ((x << n) | (x >> (32 - n)))

static const uint32_t K[64] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
    0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
    0x6b901122,0xfd987193,0xa679438e,0x49b40821,
    0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
    0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
    0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
    0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
    0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
    0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
    0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

static const uint8_t S[64] = {
     7,12,17,22, 7,12,17,22, 7,12,17,22, 7,12,17,22,
     5, 9,14,20, 5, 9,14,20, 5, 9,14,20, 5, 9,14,20,
     4,11,16,23, 4,11,16,23, 4,11,16,23, 4,11,16,23,
     6,10,15,21, 6,10,15,21, 6,10,15,21, 6,10,15,21
};

static void md5_transform(MD5_CTX *c, const uint8_t *b){
    uint32_t a=c->h[0], d=c->h[3], b0=c->h[1], c0=c->h[2], x[16];
    for(int i=0;i<16;i++)
        x[i]=(uint32_t)b[i*4]|((uint32_t)b[i*4+1]<<8)|
             ((uint32_t)b[i*4+2]<<16)|((uint32_t)b[i*4+3]<<24);

    for(int i=0;i<64;i++){
        uint32_t f,g;
        if(i<16){f=F(b0,c0,d); g=i;}
        else if(i<32){f=G(b0,c0,d); g=(5*i+1)%16;}
        else if(i<48){f=H(b0,c0,d); g=(3*i+5)%16;}
        else{f=I(b0,c0,d); g=(7*i)%16;}
        uint32_t t=d;
        d=c0; c0=b0;
        b0+=ROL(a+f+K[i]+x[g],S[i]);
        a=t;
    }
    c->h[0]+=a; c->h[1]+=b0; c->h[2]+=c0; c->h[3]+=d;
}

void md5_init(MD5_CTX *c){
    c->bits=0;
    c->h[0]=0x67452301; c->h[1]=0xefcdab89;
    c->h[2]=0x98badcfe; c->h[3]=0x10325476;
}

void md5_update(MD5_CTX *c,const void *data,size_t len){
    const uint8_t *p=(uint8_t*)data;
    size_t i=c->bits/8%64;
    c->bits+=len*8;
    while(len--){
        c->buf[i++]=*p++;
        if(i==64){ md5_transform(c,c->buf); i=0; }
    }
}

void md5_final(uint8_t out[16],MD5_CTX *c){
    size_t i=c->bits/8%64;
    c->buf[i++]=0x80;
    if(i>56){
        while(i<64)c->buf[i++]=0;
        md5_transform(c,c->buf);
        i=0;
    }
    while(i<56)c->buf[i++]=0;
    for(int j=0;j<8;j++) c->buf[56+j]=c->bits>>(8*j);
    md5_transform(c,c->buf);
    for(int j=0;j<4;j++)
        for(int i2=0;i2<4;i2++)
            out[j*4+i2]=(c->h[j]>>(8*i2))&0xff;
}

int main(){
    char buff[51];
    scanf("%s",buff);
    const char *s=buff;
    uint8_t d[16];
    MD5_CTX c;

    md5_init(&c);
    md5_update(&c,s,strlen(s));
    md5_final(d,&c);

    for(int i=0;i<16;i++)
        printf("%02x",d[i]);
}
