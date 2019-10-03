#include <cstdio>
#include <cstdlib>
#include <cstdint>

int64_t max(int64_t a, int64_t b) {
	if (a > b)
		return a;
	return b;
}

int main() {
	int32_t n,l=0,r=0;
	int32_t *tab;
	int64_t r_sum = 0, l_sum = 0,maximum=0;
	scanf("%d", &n);
	tab = (int32_t *) malloc(sizeof(int32_t)*n);
	for (int i = 0; i < n; i++)
		scanf("%d", tab + i);
	for (int i = 1; i < n; i++) {
		if (r_sum + tab[r] > l_sum + tab[(l + n - 1) % n]) {
			l_sum += tab[(l + n - 1) % n];
			l = (l + n - 1) % n;
		} else {
			r_sum += tab[r];
			r++;
		}
	}
	maximum = max(r_sum, l_sum);
	//printf("%lld %d %d\n", maximum, l, r);
	for (int i = 1; i < n; i++) {
		l_sum += tab[i - 1];
		r_sum -= tab[i - 1];
		while (r_sum + tab[r] < l_sum) {
			l_sum -= tab[l];
			r_sum += tab[r];
			l++;
			l %= n;
			r++;
			r %= n;
		}
		maximum = max(maximum,max(r_sum,l_sum));
		//printf("%lld %d %d\n", maximum, l, r);
	}
	printf("%lld\n", maximum);
	return 0;
}