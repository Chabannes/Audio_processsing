Exe: flanging/flanging.o echo/echo.o phase_shifter/phase_shifter.o main.o random_LSB/random_LSB.o random_MSB/random_MSB.o modulation/modulation.o speed_up/speed_up.o reverse/reverse.o
	g++ -o Exe flanging/flanging.o echo/echo.o phase_shifter/phase_shifter.o main.o random_LSB/random_LSB.o random_MSB/random_MSB.o modulation/modulation.o speed_up/speed_up.o reverse/reverse.o

flanging.o: flanging/flanging.cpp
	g++ -c flanging/flanging.cpp

echo.o: echo/echo.cpp
	g++ -c echo/echo.cpp

modulation.o: modulation/modulation.cpp
	g++ -c modulation/modulation.cpp	

phase_shifter.o: phase_shifter/phase_shifter.cpp
	g++ -c phase_shifter/phase_shifter.cpp

random_LSB.o: random_LSB/random_LSB.cpp
	g++ -c random_LSB/random_LSB.cpp

random_MSB.o: random_MSB/random_MSB.cpp
	g++ -c random_MSB/random_MSB.cpp

speed_up.o: speed_up/speed_up.cpp
	g++ -c speed_up/speed_up.cpp

reverse.o: reverse/reverse.cpp
	g++ -c reverse/reverse.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm main.o Exe
	rm */*.o