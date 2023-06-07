CXX=g++
CXXFLAGS=-std=c++11 -g -Wall -c
CXXLINK=g++

firewall.exe : main.o libinput.so libfirewall.so
	$(CXXLINK) -o firewall.exe ip.o port.o string.o main.o -L. -linput -lfirewall

main.o : main.cpp ip.h port.h
	$(CXX) $(CXXFLAGS) main.cpp

libfirewall.so : ip.o port.o string.o
	$(CXXLINK) -shared -o libfirewall.so ip.o port.o string.o

ip.o : ip.cpp ip.h generic-field.h string.h
	$(CXX) $(CXXFLAGS) -fPIC ip.cpp

port.o : port.cpp port.h generic-field.h string.h
	$(CXX) $(CXXFLAGS) -fPIC port.cpp

string.o : string.cpp string.h
	$(CXX) $(CXXFLAGS) -fPIC string.cpp

clean:
	rm -f *.o *.exe