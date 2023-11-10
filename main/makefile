all: main.o
	g++ -g -o Blinky main.o 

main.o: main_rt_model.cpp include/
	g++ -g -c -std=c++17 -I ../components/cadmium_v2/include -I include main_rt_model.cpp -o main.o

clean:
	rm -f *.o
	rm -f *.csv
	rm -f Blinky