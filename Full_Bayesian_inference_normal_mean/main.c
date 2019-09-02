/* Needed libraries are included */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Global required constants are defined */
#define n_iterations 50
const float gamma_star = 0.9347;
const float mu_star = 3.6843;

/* Global variables are initialized*/
float m0 = 0.0, g0 = 1.0;
float m [51];
float g [51];
float x [n_iterations];

/* Functions' headers*/
float randn(float mu, float gamma);
float generate_data();
float update_params(int k);
void export_params_data(char* file_name);

/* Functions' bodies*/
int main(){
  char file_name[60] = "results.csv";
  m[0] = m0, g[0] = g0;

  for(int k = 1; k <= n_iterations; k++){
    x[k-1] = generate_data();
    update_params(k);
  }
	printf("Finished Bayesian inference process.\n");

  export_params_data(file_name);
  return 0;
}

float polar_randn(float mu, float gamma){
    float U1, U2, W, f_W;
    static float X1, X2;
    static char iter = 0;

    if (iter == 0) {
      do{
        U1 = -1.0 + ((float) rand() / RAND_MAX)*2.0;
        U2 = -1.0 + ((float) rand() / RAND_MAX)*2.0;
        W = pow(U1,2) + pow(U2,2);
      }
      while (W >= 1 || W == 0);

      f_W = sqrt((-2 * log (W)) / W);
      X1 = U1 * f_W;
      X2 = U2 * f_W;
      iter == 1;

      return(mu + X1/sqrt(gamma));
    }
    else {
      iter == 0;

      return(mu + X2/sqrt(gamma));
    }
}

float generate_data(){
    float x_k = polar_randn(mu_star, gamma_star);
    return x_k;
}

float update_params(int k){
    g[k] = g[k-1] + gamma_star;
    m[k] = (g[k-1]*m[k-1] + gamma_star*x[k-1]) / g[k];
}

void export_params_data(char* file_name){
	printf("Saving parameters evolution and data...\n");
	FILE *file = fopen(file_name, "w");
	fprintf(file, "m,g,x\n");
	for(int k = 0; k < n_iterations; k++){
	   fprintf(file, "%f,%f,%f\n", m[k], g[k], x[k]);
	}
  fprintf(file, "%f,%f", m[n_iterations], g[n_iterations]);
	fclose(file);
}
