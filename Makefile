all: OTPake

OTPake: OTPake.o OTPakeClient.o OTPakeServer.o example.o
	g++ OTPake.o OTPakeClient.o OTPakeServer.o example.o -lgmpxx -lgmp -lsodium -o example.out

OTPake.o:
	g++ -c OTPake.cxx -std=c++11

OTPakeClient.o:
	g++ -c OTPakeClient.cxx -std=c++11

OTPakeServer.o:
	g++ -c OTPakeServer.cxx -std=c++11

example.o:
	g++ -c example.cxx -std=c++11

clean:
	rm -rf *.o *.out *.so *.py *.pyc *_wrap.cxx *.js *.js.map *.js.mem

python: _OTPake.so

_OTPake.so: OTPake_wrap.o
	g++ -shared OTPake.o OTPakeClient.o OTPakeServer.o OTPake_wrap.o -lgmp -lgmpxx -lsodium -o _OTPake.so

OTPake_wrap.o: OTPake_wrap.cxx
	g++ -fPIC -c OTPake.cxx OTPakeClient.cxx OTPakeServer.cxx OTPake_wrap.cxx -I/usr/include/python2.7 -std=c++11

OTPake_wrap.cxx:
	swig -c++ -python OTPake.i

javascript: OTPake.js

OTPake.js:
	em++ -O2 --llvm-opts 3 --bind OTPake.cxx OTPakeClient.cxx OTPakeJS.cxx -lgmpxx -lgmp -lsodium -o OTPake.js
