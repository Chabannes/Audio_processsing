Exe:  main.o Random_LSB_filter/Random_LSB.o Random_MSB_filter/Random_MSB.o Flanging_filter/Flanging.o Echo_filter/Echo.o Phase_shifter_filter/Phase_shifter.o Modulation_filter/Modulation.o Speed_up_filter/Speed_up.o Reverse_filter/Reverse.o Filter/Filter.o 
	g++ -o Exe main.o Random_LSB_filter/Random_LSB.o Random_MSB_filter/Random_MSB.o Flanging_filter/Flanging.o Echo_filter/Echo.o Phase_shifter_filter/Phase_shifter.o Modulation_filter/Modulation.o Speed_up_filter/Speed_up.o Reverse_filter/Reverse.o Filter/Filter.o 

Filter.o: Filter/Filter.cpp
	g++ -c Filter/Filter.cpp

Reverse.o: Reverse_filter/Reverse.cpp
	g++ -c Reverse_filter/Reverse.cpp

Speed_up.o: Speed_up_filter/Speed_up.cpp
	g++ -c Speed_up_filter/Speed_up.cpp

Modulation.o: Modulation_filter/Modulation.cpp
	g++ -c Modulation_filter/Modulation.cpp

Phase_shifter.o: Phase_shifter_filter/Phase_shifter.cpp
	g++ -c  Phase_shifter_filter/Phase_shifter.cpp

Echo.o: Echo_filter/Echo.cpp
	g++ -c Echo_filter/Echo.cpp

Flanging.o: Flanging_filter/Flanging.cpp
	g++ -c Flanging_filter/Flanging.cpp

Random_MSB.o: Random_MSB_filter/Random_MSB.cpp
	g++ -c Random_MSB_filter/Random_MSB.cpp

Random_LSB.o: Random_LSB_filter/Random_LSB.cpp
	g++ -c Random_LSB_filter/Random_LSB.cpp


main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm main.o Exe
	rm */*.o