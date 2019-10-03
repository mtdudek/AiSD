#include <cstdio>
#include <cstdlib>
#include <cstring>

//#define DEBUG1
//#define DEBUG2
//#define DEBUG3


long pow7[]={1,7,49,343,2401,16807,117649,823543,5764801,40353607};

long maximum(long a,long b){
    if(a>b)
        return a;
    return b;
}

int main(){
    int w,k;
    scanf("%d%d",&w,&k);
    long *tab[3];
    char *s[3];
    for (int i=0;i<3;i++){
        s[i] = (char*) malloc(sizeof(char)*(k+10));
        scanf("%s",s[i]);
        for (int j=0;j<k;j++)
            s[i][j]-='0';
        tab[i]= (long*) malloc(sizeof(long)*k);
        memset(tab[i],-1,sizeof(long)*k);
    }
    for (int i=0;i<k;i++)
        tab[0][i]=pow7[s[0][i]];

    tab[2][1]=maximum(tab[2][1],tab[0][0]+pow7[s[2][1]]);
    for (int i=1;i<k-1;i++){
        tab[2][i-1]=maximum(tab[2][i-1],tab[0][i]+pow7[s[2][i-1]]);
        tab[2][i+1]=maximum(tab[2][i+1],tab[0][i]+pow7[s[2][i+1]]);
    }
    tab[2][k-2]=maximum(tab[2][k-2],tab[0][k-1]+pow7[s[2][k-2]]);

    int h=3;

    if(k==3&&h<w){
        h++;
        long *lt = tab[0];
        char *ct = s[0];
        tab[0]=tab[1];
        s[0] = s[1];
        tab[1]=tab[2];
        s[1] = s[2];
        tab[2] = (long*) memset(lt,-1,sizeof(long)*k);
        s[2] = ct;
        scanf("%s",s[2]);
        for (int j=0;j<k;j++)
            s[2][j]-='0';

        tab[0][0]=maximum(tab[0][0],tab[1][2]+pow7[s[0][0]]);
        tab[0][2]=maximum(tab[0][2],tab[1][0]+pow7[s[0][2]]);
        tab[2][1]=maximum(tab[2][1],tab[0][0]+pow7[s[2][1]]);
        tab[2][1]=maximum(tab[2][1],tab[0][2]+pow7[s[2][1]]);

    }

    for (int i=h;i<w;i++){
        long *lt = tab[0];
        char *ct = s[0];
        tab[0]=tab[1];
        s[0] = s[1];
        tab[1]=tab[2];
        s[1] = s[2];
        tab[2] = (long*) memset(lt,-1,sizeof(long)*k);
        s[2] = ct;
        scanf("%s",s[2]);
        for (int j=0;j<k;j++)
            s[2][j]-='0';

        #ifdef DEBUG1
        printf("////////BEGIN DEBUG1//////\n");
        for (int j=0;j<3;j++){
            for (int h=0;h<k;h++)
                printf("%ld ",tab[j][h]);
            for (int h=0;h<k;h++)
                printf("%hhd",s[j][h]);
            printf("\n");
        }
        printf("////////END DEBUG1////////\n");
        #endif // DEBUG

        for (int j=2;j<k-2;j++){
            tab[0][j]=maximum(tab[0][j],tab[1][j-2]+pow7[s[0][j]]);
            tab[0][j]=maximum(tab[0][j],tab[1][j+2]+pow7[s[0][j]]);
        }
        tab[0][0]=maximum(tab[0][0],tab[1][2]+pow7[s[0][0]]);
        tab[0][k-1]=maximum(tab[0][k-1],tab[1][k-3]+pow7[s[0][k-1]]);
        if(k!=3){
            tab[0][1]=maximum(tab[0][1],tab[1][3]+pow7[s[0][1]]);
            tab[0][k-2]=maximum(tab[0][k-2],tab[1][k-4]+pow7[s[0][k-2]]);
        }

        #ifdef DEBUG2
        printf("////////BEGIN DEBUG2//////\n");
        for (int j=0;j<3;j++){
            for (int h=0;h<k;h++)
                printf("%ld ",tab[j][h]);
            printf("\n");
        }
        printf("////////END DEBUG2////////\n");
        #endif // DEBUG
        tab[2][1]=maximum(tab[2][1],tab[0][0]+pow7[s[2][1]]);
        for (int j=1;j<k-1;j++){
            tab[2][j-1]=maximum(tab[2][j-1],tab[0][j]+pow7[s[2][j-1]]);
            tab[2][j+1]=maximum(tab[2][j+1],tab[0][j]+pow7[s[2][j+1]]);
        }
        tab[2][k-2]=maximum(tab[2][k-2],tab[0][k-1]+pow7[s[2][k-2]]);

        #ifdef DEBUG3
        printf("////////BEGIN DEBUG3//////\n");
        for (int j=0;j<3;j++){
            for (int h=0;h<k;h++)
                printf("%ld ",tab[j][h]);
            printf("\n");
        }
        printf("////////END DEBUG3////////\n");
        #endif // DEBUG
    }
    long ans=0;
    for (int i=0;i<k;i++)
        ans=maximum(ans,tab[2][i]);
    printf("%ld",ans);
    return 0;
}
