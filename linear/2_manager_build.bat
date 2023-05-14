g++ -c ./manager/source/manager.cpp -o ./manager/build/manager.o

g++ -shared ./manager/build/manager.o -o ./client/source/lib/manager.dll -Wl,--kill-at

pause