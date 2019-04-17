#include<cmath>


//parameters
int N = 500; //how many isochrones
int every = 10; //every which one is plotted
double delta = 0.001; //how much to perturb
int pp = 5*N; //how many delta_t's to run
double t_relax = 1000.0; //time to relax to the stable orbit
double dt = 0.005; //time step
double thr = 0.0; //threshold that determines the zero phase
double x_ini = 0.1; //initial condition
double y_ini = 0.1;
double x_min = -6.5; //plot range
double x_max = 5.0;
double y_min = -6.5;
double y_max = 5.0; 

//the system
double dx(double x, double y){
	return y - sin(y)*x;
}
double dy(double x, double y){
	return -x + cos(x)*y;
}



//OTHER EXAMPLES
/*
 * 	- Rayleigh oscillator
 * 	- Van der Pol oscillator
 * 	- Fitzhugh-Nagumo model
 * 	- Morris-Lecar model
 */

//-----------------------------------------------------------------

/*
//RAYLEIGH OSCILLATOR
//parameters
int N = 500; //how many isochrones
int every = 10; //every which one is plotted
double delta = 0.0005; //how much to perturb
int pp = 5*N; //how many delta_t's to run
double t_relax = 1000.0; //time to relax to the stable orbit
double dt = 0.01; //time step
double thr = 0.0; //threshold that determines the zero phase
double x_ini = -0.5; //initial condition
double y_ini = 0.5;
double x_min = -1.6; //plot range
double x_max = 1.6;
double y_min = -1.6;
double y_max = 1.6; 

//the system
double mu = 1.0; 
double dx(double x, double y){
	return y;
}
double dy(double x, double y){
	return mu*(1-y*y)*y - x;
}
*/

//-----------------------------------------------------------------

/*
//VAN DER POL OSCILLATOR
//parameters
int N = 500; //how many isochrones
int every = 10; //every which one is plotted
double delta = 0.001; //how much to perturb
int pp = 5*N; //how many delta_t's to run
double t_relax = 1000.0; //time to relax to the stable orbit
double dt = 0.01; //time step
double thr = 0.0; //threshold that determines the zero phase
double x_ini = -0.5; //initial condition
double y_ini = 0.5;
double x_min = -2.5; //plot range
double x_max = 2.5;
double y_min = -3.0;
double y_max = 3.0; 

//the system
double mu = 0.5; 
double dx(double x, double y){
	return y;
}
double dy(double x, double y){
	return mu*(1-x*x)*y - x;
}
*/

//-----------------------------------------------------------------

/*
//FITZHUGH-NAGUMO MODEL
//parameters
int N = 1500; //how many isochrones
int every = 20; //every which one is plotted
double delta = 0.0005; //how much to perturb
int pp = 1*N; //how many delta_t's to run
double t_relax = 1000.0; //time to relax to the stable orbit
double dt = 0.005; //time step
double thr = 0.0; //threshold that determines the zero phase
double x_ini = -0.5; //initial condition
double y_ini = 0.5;
double x_min = -2.7; //plot range
double x_max = 2.7;
double y_min = -3.3;
double y_max = 1.8; 

//the system
double II = -1.0;
double sig = 0.5;
double a = 0.7;
double b = 0.5; 
double dx(double x, double y){
	return x-x*x*x/3-y+II;
}
double dy(double x, double y){
	return sig*(x+a+b*y);
}
*/

//-----------------------------------------------------------------

/*
//MORRIS-LECAR MODEL
//parameters
int N = 1000; //how many isochrones
int every = 5; //every which one is plotted
double delta = 0.00001; //how much to perturb
int pp = 0.5*N; //how many delta_t's to run
double t_relax = 1000.0; //time to relax to the stable orbit
double dt = 0.05; //time step
double thr = 0.0; //threshold that determines the zero phase
double x_ini = -0.5; //initial condition
double y_ini = 0.5;
double x_min = -0.6; //plot range
double x_max = 0.5;
double y_min = -0.1;
double y_max = 0.6; 

//the system
double II = 0.07; 
double CC = 1;
double gL = 0.5;
double gCa = 1.33; 
double gK = 2;
double VL = -0.5;
double VCa = 1;
double VK = -0.7;
double V1 = -0.01;
double V2 = 0.15;
double V3 = 0.1; 
double V4 = 0.145; 
double fi = 1.0/3; 
double Mss(double V){
	return 0.5*(1+tanh((V-V1)/V2));
}
double Nss(double V){
	return 0.5*(1+tanh((V-V3)/V4));
}
double tauN(double V){
	return 1.0/(fi*cosh((V-V3)/(2*V4)));
}
double dx(double V, double N){
	return (II-gL*(V-VL)-gCa*Mss(V)*(V-VCa)-gK*N*(V-VK))/CC;
} 
double dy(double V, double N){
	return (Nss(V)-N)/tauN(V);
}
*/
