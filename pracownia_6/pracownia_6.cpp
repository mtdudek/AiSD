#include <cstdio>
#include <complex>
#include <vector>
#include <cmath>

void bit_revers(std::vector<std::complex<double>> &v){
	int n=v.size();
	std::vector<std::complex<double>> temp(n);
	for (int i=0;i<n;i++){
		int t=i,new_pos=0,j=1;
		while(t>0){
			if(t&1)
				new_pos+=n/(1<<j);
			j++;
			t>>=1;
		}
		temp[new_pos]=v[i];
	}
	v=temp;
}

void FFT_probe(std::vector<std::complex<double>> &v ){
	bit_revers(v);
	int n=v.size();
	for (int i=1;(1<<i)<=n;i++){
		int m=1<<i;
		std::complex<double> omega_m = std::polar<double>(1.0,2*M_PI/(double)m);
		for (int k=0;k<n;k+=m){
			std::complex<double> omega(1.0,0.0);
			for(int j=0;j<m/2;j++){
				std::complex<double> t = omega*v[k+j+m/2],
								u = v[k+j];
				v[k+j]= u + t;
				v[k+j+m/2] = u - t;
				omega*=omega_m;
			}
		}
	}
}

void FFT_inter(std::vector<std::complex<double>> &v ){
	bit_revers(v);
	int n=v.size();
	for (int i=1;(1<<i)<=n;i++){
		int m=1<<i;
		std::complex<double> omega_m = std::polar<double>(1.0,-2*M_PI/(double)m);
		for (int k=0;k<n;k+=m){
			std::complex<double> omega(1.0,0.0);
			for(int j=0;j<m/2;j++){
				std::complex<double> t = omega*v[k+j+m/2],
								u = v[k+j];
				v[k+j]= u + t;
				v[k+j+m/2] = u - t;
				omega*=omega_m;
			}
		}
	}
}

int main(){
	int n,max=0;
	scanf("%d",&n);
	std::vector<bool> temp(1000100);
	for (int i=0;i<n;i++){
		int t;
		scanf("%d",&t);
		temp[t]=1;
		max = (t > max) ? t : max;
	}
	int g=1;
	while (g<(max+1)) g<<=1;
	g<<=1;
	std::vector<std::complex<double>> coefficients(g);
	coefficients[0]=std::complex<double>(1.0,0.0);
	int t=temp.size();
	for (int i=0;i<t;i++){
		if(temp[i])
			coefficients[i]=std::complex<double>(1.0,0.0);
	}
	
	FFT_probe(coefficients);
	for (int i=0;i<g;i++)
		coefficients[i]*=coefficients[i];
	FFT_inter(coefficients);
	
	for (int i=0;i<g;i++)
		coefficients[i]/=g;

	std::vector<int> ans(g);
	
	for (int i=0;i<g;i++)
		if(abs(coefficients[i])>0.9)
			ans[i]=round(abs(coefficients[i]));
	for (int i=1;i<t;i++)
		if(temp[i])
			ans[2*i]--;

	for (int i=1;i<g;i++)
		ans[i]/=2;

	for (int i=0;i<g;i++)
		if(ans[i]>0)
			printf("%d %d\n",i,ans[i]);
	return 0;
}