CC=g++-4.7

rpi2edam: rpi2edam.cpp
	$(CC) -o rpi2edam rpi2edam.cpp -lwiringPi -std=c++11