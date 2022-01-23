# NomadEmu
NomadEmu is an Emulator written in C++ for the "Nomad" platform, which I designed back in 2019 for the HCS Tech Fair.
_________
# Building
Building should be simple enough. Just open in Visual Studio and build the default (Release x86) build.  
I don't really think I use any platform specific features yet, so I'm sure you could manually link and compile it via GCC.
_________
# Running
You'll need a Logisim "v2.0 raw" formatted ROM file.  
If you check out my /Nomad repository there are a few of these roms in the "roms" folder  
All you need to run a ROM is simply use the path as a command line argument, and it will run. If you don't supply a ROM, the program will exit.  
Once a ROM has finished execution, you'll be asked to hit the enter key to exit.
_________
# Features
Emulates all 16 of the base instructions, with correct register support.  
The i0 register, or 0xA, automatically outputs the character stored to cout. I haven't written a proper TTY for this as I'm still learning C++, so some features don't work. This seems to be a fair compromise though.  
The clock speed is by default hardcoded as 120Hz. You can adjust this in "Nomad.h" as CLOCK_SPEED, which is an expression of milliseconds / desired clock speed.  
_________
# Issues
Some features aren't properly emulated. Some of the registers should be read only, but I haven't implemented input yet so consider it a side effect until I have.  
Clock speed is hardcoded. I might change it to be a command line argument later on, with a default of 120Hz.  
There's probably some other nasty stuff I haven't thought about. Don't download random files and run them off the internet without understanding what they do.
