#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include"parameters.h"
#define Pi 3.1415926535

using namespace std;

void integrator(double *x, double *y, double dt){
	double kx1 = dx(*x, *y);
	double ky1 = dy(*x, *y);
	double kx2 = dx(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double ky2 = dy(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double kx3 = dx(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double ky3 = dy(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double kx4 = dx(*x + kx3*dt, *y + ky3*dt);
	double ky4 = dy(*x + kx3*dt, *y + ky3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
}

double distance(double x, double y){
	return sqrt(x*x+y*y);
}

int main(){
		
	//output file
	FILE *f;
	f = fopen("limit_cycle.dat", "wt");
	fclose(f);
	
	//warmup integration
	double x = x_ini; //initial condition
	double y = y_ini;
	//let the system go to the periodic orbit
	for(double t = 0; t < t_relax; t = t+dt){
		integrator(&x, &y, dt);
	}
	
	//measure the period
	double xh = x; //previous x
	while((xh < thr && x > thr) != 1){ //when this loop ends we will be at a point where x has just crossed the threshold from below
		xh = x;
		integrator(&x, &y, dt);
	}
	//Henon trick
	double rest_t_1 = 1.0/dx(x,y)*(x-thr);
	integrator(&x, &y, -rest_t_1); //integrate back to zero
	//first time outside the loop to ensure x > thr
	double period = 0;
	integrator(&x, &y, dt);
	period += dt;
	//...and now time how long it takes to cross zero from bellow again
	xh = 1; //break the condition (xh < thr && x > thr)
	while((xh < thr && x > thr) != 1){
		xh = x;
		integrator(&x, &y, dt);
		period += dt;
	}
	//Henon trick
	double rest_t_2 = 1.0/dx(x,y)*(x-thr);
	integrator(&x, &y, -rest_t_2); //integrate back to zero
	period = period-rest_t_2; 
	
	//print the orbit to file
	double start_x = x;
	double start_y = y;
	f = fopen("limit_cycle.dat", "wt");
	for(double t = 0; t < period; t = t+dt){
		fprintf(f, "%lf, %lf\n", x, y);
		integrator(&x, &y, dt);
	}
	//twice more for good measure
	fprintf(f, "%lf, %lf\n", x, y);
	integrator(&x, &y, dt);
	fprintf(f, "%lf, %lf\n", start_x, start_y);
	fclose(f);

	//measure the average x and y
	double x_avg = 0;
	double y_avg = 0;
	int x_cnt = 0;
	int y_cnt = 0;
	for(double t = 0; t < period; t = t+dt){ //average over one period
		integrator(&x, &y, dt);
		x_avg += x;
		y_avg += y;
		x_cnt++;
		y_cnt++;
	}
	x_avg /= x_cnt;
	y_avg /= y_cnt;
	
	//get points on the period orbit, perturb them and run backwards in time
	double delta_t = period/N;
	//initialize the files
	for(int p = 0; p < N; ++p){
		char buffer[100];
		snprintf(buffer, 100, "data_iso/%d_in.dat", p);
		f = fopen(buffer, "wt");
		fclose(f);
		snprintf(buffer, 100, "data_iso/%d_out.dat", p);
		f = fopen(buffer, "wt");
		fclose(f);
	}
	//start running
	double last_t;
	double x_in[N];
	double y_in[N];
	double x_out[N];
	double y_out[N];
	double x_in_h[N];
	double y_in_h[N];
	double x_out_h[N];
	double y_out_h[N];
	double x0 = x;
	double y0 = y;
	for(int i = 0; i < N; ++i){
		for(double t = 0; t < delta_t; t = t+dt){
			integrator(&x0, &y0, dt);
			last_t = t+dt;
		}
		//last bit by hand
		integrator(&x0, &y0, (delta_t-last_t));
		double delta_x = x_avg-x0;
		double delta_y = y_avg-y0;
		//perturb in
		x = x0 + delta*delta_x/distance(delta_x,delta_y);
		y = y0 + delta*delta_y/distance(delta_x,delta_y);
		x_in[i] = x;
		y_in[i] = y;
		//perturb out
		x = x0 - delta*delta_x/distance(delta_x,delta_y);
		y = y0 - delta*delta_y/distance(delta_x,delta_y);
		x_out[i] = x;
		y_out[i] = y;
	}
	for(int p = 0; p < pp; ++p){
		if(p%100 == 0) printf("iso: p = %d/%d\n", p, pp);
		//print
		for(int i = 0; i < N; ++i){
			int index = (100*N+i-p)%N;
			char buffer[100];
			snprintf(buffer, 100, "data_iso/%d_in.dat", index);
			f = fopen(buffer, "at");
			if(x_in[i] == x_in[i] && y_in[i] == y_in[i]){
				fprintf(f, "%lf, %lf\n", x_in[i], y_in[i]);
			}
			fclose(f);
			snprintf(buffer, 100, "data_iso/%d_out.dat", index);
			f = fopen(buffer, "at");
			if(x_out[i] == x_out[i] && y_out[i] == y_out[i]){
				fprintf(f, "%lf, %lf\n", x_out[i], y_out[i]);
			}
			fclose(f);
		}
		//perturb
		for(int i = 0; i < N; ++i){
			int index = (100*N+i-p)%N;
			x_in_h[index] = x_in[i];
			y_in_h[index] = y_in[i];
			x_out_h[index] = x_out[i];
			y_out_h[index] = y_out[i];
			for(double t = 0; t < delta_t; t = t+dt){
				integrator(&(x_in[i]), &(y_in[i]), -dt); //notice we're going back in time
				integrator(&(x_out[i]), &(y_out[i]), -dt);
				last_t = t+dt;
			}
			//last bit by hand
			integrator(&(x_in[i]), &(y_in[i]), -(delta_t-last_t)); //notice we're going back in time
			integrator(&(x_out[i]), &(y_out[i]), -(delta_t-last_t));
		}
	}
	
	return 0;
	
}
