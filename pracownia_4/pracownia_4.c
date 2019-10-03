#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct{
    int first,second;
} pair;

typedef struct{
    double d;
    int p1,p2;
} func_ret;

int pair_comp(pair* a,pair* b){
    if(a->first<b->first)
        return 1;
    return 0;
}

void mergesort(pair*, int, int);

static void __mergesort(pair*, pair*, int, int);

static int __select_marked(pair*, pair*, char*, int, int, int);

static double length_squared(int,int,int,int);

static func_ret __small_case(pair*, pair*, int, int);

func_ret find_closest_points(pair*, pair*, int, int);

int main(){
    int n;
    pair *x,*y;
    scanf("%d",&n);
    x=(pair*) malloc(n*sizeof(pair));
    y=(pair*) malloc(n*sizeof(pair));

    for (int i=0;i<n;i++)
        scanf("%d%d",&(x+i)->first,&(x+i)->second);

    mergesort(x,0,n);

    for (int i=0;i<n;i++){
        (y+i)->first = (x+i)->second;
        (y+i)->second = i;
        (x+i)->second = i;
    }

    func_ret ret = find_closest_points(x,y,0,n);

    printf("%.5lf\n",ret.d);
    //printf("%d %d\n",x[ret.p1].first,y[x[ret.p1].second].first);
    //printf("%d %d\n",x[ret.p2].first,y[x[ret.p2].second].first);

    return 0;
}

void mergesort(pair *y,int begin, int end){
    pair *temp = (pair*) malloc((end-begin)*sizeof(pair));
    __mergesort(y,temp,begin,end);
    free(temp);
}

static void __mergesort(pair *tab,pair *temp,int begin, int end){
    if (end-begin<20){
        for (int i = begin;i < end; i++) {
            for (int j = i+1;j < end; j++) {
                if(pair_comp(tab + j,tab + i)){
                    pair tmp=tab[j];
                    tab[j]=tab[i];
                    tab[i]=tmp;
                }
            }
        }
        return;
    }
    int s = (begin + end) / 2;
    __mergesort(tab,temp,begin,s);
    __mergesort(tab,temp,s,end);
    int it1 = begin,it2 = s,it3=0;
    while(it1<s && it2<end){
        if(pair_comp(tab + it1, tab + it2)){
            temp[it3] = tab[it1++];
        }else{
            temp[it3] = tab[it2++];
        }
        it3++;
    }
    while(it1<s) temp[it3++] = tab[it1++];
    while(it2<end) temp[it3++] = tab[it2++];
    for (int l=0;l<it3;l++){
        tab[begin+l] = temp[l];
    }
}

static double length_squared(int x1, int x2, int y1, int y2) {
	int dx = x1 - x2, dy = y1 - y2;
	return (double)dx*dx+(double)dy*dy;
}

static func_ret __small_case(pair *x, pair *y, int begin, int end) {
    func_ret ret_val = {-1.0,-1,-1};
	double d = DBL_MAX;
    for (int i = begin; i < end; i++) {
		for (int j = i + 1; j < end; j++) {
            if( d*d > length_squared(x[i].first,x[j].first,y[i].first,y[j].first)){
                d = sqrt(length_squared(x[i].first,x[j].first,y[i].first,y[j].first));
                ret_val.d = d;
                ret_val.p1 = i;
                ret_val.p2 = j;
            }
        }
    }
    for (int i = begin; i < end; i++) {
        for (int j = i + 1; j < end; j++){
            if (pair_comp(y+j,y+i)){
                x[y[j].second].second = i;
                x[y[i].second].second = j;
                pair tmp = y[j];
                y[j] = y[i];
                y[i] = tmp;
            }
        }
    }
    return ret_val;
}

static int __select_marked(pair *from, pair *to, char *marked, int begin, int end, int offest) {
    int size = 0;
    for (int i = end - 1; i >= begin; i--) {
        if (marked[i-offest]) {
            to[size++] = from[i];
        }
    }
    return size;
}

func_ret find_closest_points(pair *x, pair *y, int begin, int end) {
    int r = end-begin;
	if (r < 20) {
        return __small_case(x,y,begin,end);
	}
    double d;
    func_ret ret_val = {-1.0,-1,-1};

    int s = (begin + end) / 2;
    func_ret    r1 = find_closest_points(x,y,begin,s),
                r2 = find_closest_points(x,y,s,end);

    if(r2.d < r1.d){
        d = r2.d;
        ret_val = r2;
    }else{
        d = r1.d;
        ret_val = r1;
    }
    int x_div = x[s].first;

    char *marked = (char*) calloc(r,sizeof(char));
    int il1, il2;
    pair    *l1 = (pair*) malloc((s-begin)*sizeof(pair)),
            *l2 = (pair*) malloc((end-s)*sizeof(pair));

    for (int i=begin;i<end;i++){
        if(abs (x[i].first-x_div) <= d){
            marked[x[i].second-begin] = 1;
        }}

    il1 = __select_marked(y, l1, marked, begin, s, begin);
    il2 = __select_marked(y, l2, marked, s, end, begin);

    int t1=0,t2=0;
    double d_t;
    while (t1<il1 && t2<il2){
        if(l1[t1].first>l2[t2].first){
            for(int t=0; t2+t<il2 && l2[t2+t].first+d >= l1[t1].first; t++){
                d_t = length_squared(x[l1[t1].second].first,x[l2[t2+t].second].first,
                            l1[t1].first,l2[t2+t].first);
                if (d_t<d*d){
                    d = sqrt(d_t);
                    ret_val.d=d;
                    ret_val.p1=l1[t1].second;
                    ret_val.p2=l2[t2+t].second;
            }}
            t1++;
        } else {
            for(int t=0;t1+t<il1 && l1[t1+t].first+d>=l2[t2].first;t++){
                d_t = length_squared(x[l1[t1+t].second].first, x[l2[t2].second].first,
                            l1[t1+t].first, l2[t2].first);
                if (d_t<d*d){
                    d = sqrt(d_t);
                    ret_val.d=d;
                    ret_val.p1=l1[t1+t].second;
                    ret_val.p2=l2[t2].second;
            }}
            t2++;
        }}

    free(marked);
    free (l1);
    free (l2);

    pair *temp = (pair*) malloc(r*sizeof(pair));
    int it1 = begin,it2 = s,it3 = 0;
    while(it1<s && it2<end){
        if(pair_comp(y + it1, y + it2)){
            temp[it3] = y[it1];
            x[y[it1++].second].second = it3 + begin;
        }else{
            temp[it3] = y[it2];
            x[y[it2++].second].second = it3 + begin;
        }
        it3++;
    }
    while(it1<s){
        temp[it3] = y[it1];
        x[y[it1++].second].second = it3 + begin;
        it3++;
    }
    while(it2<end){
        temp[it3] = y[it2];
        x[y[it2++].second].second = it3 + begin;
        it3++;
    }
    for (int l=begin;l<end;l++){
        y[l] = temp[l-begin];
    }
    free(temp);
    return ret_val;
}
