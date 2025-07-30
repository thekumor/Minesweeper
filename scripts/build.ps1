mkdir build
Copy-Item src/ -Destination build/ -Recurse
Copy-Item images/ -Destination build/ -Recurse
cd build
cmake ..