#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct{
    int first,second;
} pair;

int main(int argc, char **argv){
    srand(time(NULL));
    int l = 1000;
    if (argc>1)
        l = atoi(argv[1]);
    pair *g =(pair*) malloc(l*sizeof(pair));
    int good = 0;
    int x,y;
    for (int i = 0; i < l ; i++){
        good = 0;
        while(!good) {
            x = rand() % 10000000;
            y = rand() % 10000000;
            good = 1;
            for (int j = 0 ; j < i && good ; j++){
                if(g[j].first == x && g[j].second == y)
                    good = 0;
            }
        }
        g[i].first=x;
        g[i].second=y;
    }
    printf("%d\n",l);
    for (int i=0;i<l;i++)
        printf("%d %d\n",g[i].first,g[i].second);
    return 0;
}
