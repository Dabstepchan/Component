g++ -c ./server/source/EquationSolver.cpp -o ./server/build/EquationSolver.o
g++ -c ./server/source/ClassFactory.cpp -o ./server/build/ClassFactory.o
g++ -c ./server2/source/EquationSolver2.cpp -o ./server2/build/EquationSolver2.o
g++ -c ./server2/source/ClassFactory2.cpp -o ./server2/build/ClassFactory2.o

g++ -shared ./server/build/EquationSolver.o ./server/build/ClassFactory.o -o ./manager/source/lib/server.dll -Wl,--kill-at
g++ -shared ./server2/build/EquationSolver2.o ./server2/build/ClassFactory2.o -o ./manager/source/lib/server2.dll -Wl,--kill-at
pause