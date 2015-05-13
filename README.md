# inputFileGenerator
To use this, just download the zip and compile the fileGenerator.cpp. 

If you're going to run it from a command line, just pass it the name of the output file as an argument. 
Otherwise it should just print to 'output.txt'

It doesn't compile correctly on the csegrid server, probably because the RNG that it uses is only supported in C++11.
Anywhere else that has C++11 should work fine (Works for me on Visual Studio).
