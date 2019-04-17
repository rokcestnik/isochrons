if [ ! -d "data_iso" ]; then
	mkdir data_iso
fi
g++ iso.c -o iso.out
./iso.out
g++ write_gp.c -o write_gp.out
./write_gp.out
gnuplot gp
