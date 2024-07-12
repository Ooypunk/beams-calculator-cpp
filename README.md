# beams-calculator-cpp

## Compiling
g++ main.cpp -g -o main -I/opt/vcpkg/installed/x64-linux/include/

Note: this is with https://github.com/nlohmann/json installed using vcpkg.

## Usage
./main config.json

## To do
- Calculator returns and expects groups-vector: should be a pointer to that same vector
- Make import (for both Parts and Materials) fully configurable in config.json
-- general import settings in "config", overrides in "parts" or "materials"
- CPU usage is now dosed by using usleep(), but number of microseconds are fixed now: this should be flexible, depending on the machine it is running on
- limit/expand output, depending on -v (or -vv, -vvv) command line argument
