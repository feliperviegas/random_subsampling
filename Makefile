main:   random_subsampling.cpp 
	g++ -O3 random_subsampling.cpp -o hold-out

clean :
	rm -f hold-out

