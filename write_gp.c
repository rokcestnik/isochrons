#include<stdio.h>
#include"parameters.h"

int main(void){
	
	FILE *f;
	f = fopen("gp","wt");
	fprintf(f, "set size ratio -1\n");
	fprintf(f, "set nokey\n");
	//isochrones
	fprintf(f, "plot [%lf:%lf] [%lf:%lf] \"data_iso/0_in.dat\" with lines lw 1.5 lt rgb \"#999999\", \\\n", x_min, x_max, y_min, y_max);
	for(int i = every; i < N; i = i+every){
		fprintf(f, "				   \"data_iso/%d_in.dat\" with lines lw 1.5 lt rgb \"#999999\", \\\n", i);
	}
	fprintf(f, "				   \"data_iso/0_out.dat\" with lines lw 1.5 lt rgb \"#999999\", \\\n");
	for(int i = every; i < N; i = i+every){
		fprintf(f, "				   \"data_iso/%d_out.dat\" with lines lw 1.5 lt rgb \"#999999\", \\\n", i);
	}
	//limit cycle
	fprintf(f, "				   \"limit_cycle.dat\" with lines lw 3.5 lt rgb \"#FF0000\", \n");
	fprintf(f, "pause -1 \"Hit any key to continue\"\n");
	fclose(f);
	
	return 0;
	
}

