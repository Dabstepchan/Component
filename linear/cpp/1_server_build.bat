g++ -c ./source/server/components.cpp -o ./build/server/components.o
g++ -c ./source/server/main.cpp -o ./build/server/main.o

g++ -shared ./build/server/components.o ./build/server/main.o -o ./build/server/server.dll -Wl,--kill-at -lole32 -loleaut32 -luser32

g++ -c ./source/server2/components.cpp -o ./build/server2/components.o
g++ -c ./source/server2/main.cpp -o ./build/server2/main.o

g++ -shared ./build/server2/components.o ./build/server2/main.o -o ./build/server2/server2.dll -Wl,--kill-at -lole32 -loleaut32 -luser32

pause