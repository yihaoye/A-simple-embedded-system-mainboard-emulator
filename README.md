# A-simple-embedded-system-mainboard-emulator
This emulator program is written by C++, running on Qt
There are two programs, one is Embedded System Mainboard Emulator, another one is program allow user to write code to control the Emulator just like they do with real hardware.
Here is the real hardware prototype.
![alt tag](https://github.com/yihaoye/A-simple-embedded-system-mainboard-emulator/blob/master/screen%20shot/0.png)

1. First, run the GUI Emulator program by click client exe program.
![alt tag](https://github.com/yihaoye/A-simple-embedded-system-mainboard-emulator/blob/master/screen%20shot/1.png)

2. Open Qt, load the server C++ code project, and write your C++ command in the main.c area, then run it.
![alt tag](https://github.com/yihaoye/A-simple-embedded-system-mainboard-emulator/blob/master/screen%20shot/2.png)

3. Qt run the program which looks like console, and send your command relevant signal to Emulator by socket and UDP.
![alt tag](https://github.com/yihaoye/A-simple-embedded-system-mainboard-emulator/blob/master/screen%20shot/3.png)

4. Emulator now responds to your commands like the real hardware do.
![alt tag](https://github.com/yihaoye/A-simple-embedded-system-mainboard-emulator/blob/master/screen%20shot/4.png)

Overview:
![alt tag](https://github.com/yihaoye/A-simple-embedded-system-mainboard-emulator/blob/master/screen%20shot/5.png)