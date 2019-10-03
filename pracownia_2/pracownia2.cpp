#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

typedef struct p{
    int x,y;
} point;

bool operator< (point &A,point &B){
    long    k=((long)A.x)*A.y,
            l=((long)B.x)*B.y;
    return k<l;
}

class my_PQ{
    point *tab;
    int _size,_last_cell;
    void _make_it_bigger(){
        _size*=2;
        tab = (point*) realloc (tab,_size*sizeof(point));
    }
    void _fix_from_index(int g){
        bool ok = false;
        while(g != 1 && !ok){
            if (tab[g/2]<tab[g]){
                std::swap(tab[g/2],tab[g]);
                g/=2;
            }else {
                ok = true;
            }
        }
    }
public:
    my_PQ(){
        _size = 2;
        _last_cell = 1 ;
        tab = (point*) malloc(_size*sizeof(point));
    };
    void push(point a){
        if(_size==_last_cell)
            _make_it_bigger();
        tab[_last_cell] = a;
        int g = _last_cell++;
        _fix_from_index(g);
    };
    void pop(){
        int g=1;
        while(g*2<_last_cell){
            if(g*2+1<_last_cell){
                if(tab[g*2+1]<tab[g*2]){
                    tab[g]=tab[g*2];
                    g*=2;
                }else{
                    tab[g]=tab[g*2+1];
                    g=2*g+1;
                }
            }else{
                tab[g]=tab[2*g];
                g*=2;
            }
        }
        tab[g]=tab[--_last_cell];
        _fix_from_index(g);
    };
    point top(){
        return tab[1];
    };
    void debug_dump(){
        printf("////////Stack DeBug Begin////////\n");
        if (1 == _last_cell){
            printf("Empty\n");
        }else {
            for (int i=1;i<_last_cell;i++)
                printf("%d %d\n",tab[i].x,tab[i].y);
        }
        printf("////////Stack DeBug End////////\n");
    };
};

int main(){
    my_PQ Queue;
    int m,k,counter = 0;
    long last_put=0x7FFFFFFFFFFFFFFF,w;
    scanf("%d%d",&m,&k);
    Queue.push(point{m,m});
    while(counter<k){
        //Queue.debug_dump();
        point h=Queue.top();
        Queue.pop();
        //Queue.debug_dump();
        w = ((long)h.x)*h.y;
        //printf("%d %d ",h.x,h.y);
        if(last_put>w){
            printf("%ld\n",w);
            counter++;
            last_put = w;
        }
        if(h.x>1&&h.y>1)
            Queue.push(point{h.x-1,h.y-1});
        if(h.x == m && h.y > 1)
            Queue.push(point{h.x,h.y-1});
    }
    return 0;
}
