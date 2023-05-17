g++ -c ./source/client/Client.cpp -o ./build/client/client.o
g++ -c ./source/client/Wrapper.cpp -o ./build/client/wrapper.o

g++ ./build/client/client.o ./build/client/wrapper.o -o ./build/client/client.exe -lole32 -loleaut32 -luser32

pause