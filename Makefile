Exe: flanging.o echo.o phase_shifter.o main.o random_LSB.o random_MSB.o modulation.o speed_up.o reverse.o
	g++ -o Exe flanging.o echo.o phase_shifter.o main.o random_LSB.o random_MSB.o modulation.o speed_up.o reverse.o

flanging.o: flanging.cpp
	g++ -c flanging.cpp

echo.o: echo.cpp
	g++ -c echo.cpp

modulation.o: modulation.cpp
	g++ -c modulation.cpp	

phase_shifter.o: phase_shifter.cpp
	g++ -c phase_shifter.cpp

random_LSB.o: random_LSB.cpp
	g++ -c random_LSB.cpp

random_MSB.o: random_MSB.cpp
	g++ -c random_MSB.cpp

speed_up.o: speed_up.cpp
	g++ -c speed_up.cpp

reverse.o: reverse.cpp
	g++ -c reverse.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm *.o Exe