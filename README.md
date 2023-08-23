# CommunicationsProtocol
A sample Satellite Communications Protocol. This project parses a known packet of size 12 byes, verifies the packet contents, and updates the system with the verified packet. 

To build, use the following instruction set.

# Prepare the build folder by running CMake
cmake -S. -Bbuild

# Change directory to the build folder
cd build

# Make the project
make

# Run Unit Tests
./TlmParserTests

# Alternatively, the project can be compiled and run with the following command
./build_and_run.sh
