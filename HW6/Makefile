CXX=g++
CXXFLAGS=-std=c++11 -g -Wall
CXXLINK=g++

firewall.exe : main.o libfirewall.so
	$(CXXLINK) ip.o port.o string.o main.o -o firewall.exe -L. -linput -L. -lfirewall

libfirewall.so : ip.o port.o string.o
	$(CXXLINK) -shared ip.o port.o string.o -o libfirewall.so

main.o : main.cpp ip.h port.h string.cpp
	$(CXX) $(CXXFLAGS) -c -fPIC main.cpp

ip.o : ip.cpp ip.h string.cpp
	$(CXX) $(CXXFLAGS) -c -fPIC ip.cpp

port.o : port.cpp port.h string.cpp
	$(CXX) $(CXXFLAGS) -c -fPIC port.cpp

string.o : string.cpp
	$(CXX) $(CXXFLAGS) -c -fPIC string.cpp

clean:
	rm -f *.o *.exe libfirewall.so