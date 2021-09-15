# Toy robot simulator
Toy Robot code challange using C++20.
The console runner will read the input from stdin, report errors to stderr and output to stdout as is customery. 
Standard shell redirection can be used to read/write to files instead. 
When running interactively, please use Ctrl+Z followed by Enter to finish reading the instruction list. 
Alternatively, Ctrl+C should also do the trick. 

## Additional implementation notes
The simulator accepts case insensitive instructions and will ignore any commands until an initial valid PLACE command is accepted by the robot.

## How to build
Compile solution in latest stable visual studio. 
The projects are configured with toolset 142 and C++20. This is requried for Boost::UT.

## How to run tests
$ .\x64\Debug\ToyRobotTests.exe

## How to run
$ .\x64\Debug\ToyRobotConsole.exe


