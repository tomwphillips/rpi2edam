#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

string serialResponse(int fd) {
    // Returns a string with whatever is in the serial buffer, stopping once you
    // reach the termination character (CR, ASCII 13).
    // Note that the CR is NOT included in the returned string.
    char msg[20] = {0};
    char j = 0;

    while (serialDataAvail(fd)) {
        char ch = serialGetchar(fd);
        if (ch != 13) {
            msg[j] = ch;
            j++;
        } else {
            break;
        }

    }

    serialFlush(fd);
   
    return msg;
}

int setType(int fd, int channel) {
    // Set thermocouple type for channel. In this case, K type.
    // Note that 01 refers to the EDAM address, which is set using switches on back.
    // From manual: section 10.33 $AA7CiRrr Set the Single Channel Range
    serialPrintf(fd, "$017C%XR10\r",channel);
    delay(25); 

    string response = serialResponse(fd);

    if (response.compare("!01") != 0) { // returns !01 if successful
        cout << "Channel " << channel << " thermocouple set type unsuccessful" << endl;
        return 1;
    } else {
        return 0;
    }
}

double readTemp(int fd, int channel) {
    // Read temperature of a channel.
    // From manual: 10.4 #AAn\r Read The Single Analog Input
    // AA = address, n = channel in hexadecimal (0-F)
    serialPrintf(fd, "#01%X\r",channel);
    delay(25);

    string r = serialResponse(fd); // EDAM returns >+0000.0. 
    string rr(r,2,6); // slice to get rid of ">+"

    return stod(rr); // convert to double. This requires C++11.
}

int main() {
	if (wiringPiSetup() == -1)	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1;
	}

	int fd;

	if ((fd = serialOpen("/dev/ttyAMA0", 9600)) < 0) {
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno));
		return 1;
	}

    // Set TC types and read all the channels
	for (int ch = 0; ch < 16; ch++) {
        // printf("Channel: %i\n",ch);
        setType(fd,ch);
        float temp = readTemp(fd,ch);
        cout << "Channel " << ch << ": " << temp << " deg C" << endl;
    }

	return 0;
}