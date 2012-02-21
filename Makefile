
NSPR_FLAGS=`nspr-config --cflags`
NSPR_LIBS=`nspr-config --libs`

CC=g++
INCLUDES=-Iinclude $(NSPR_FLAGS)
CFLAGS=-g -O -Wall -pedantic -ansi -std=c++0x
LIB=$(NSPR_LIBS)



all: xzHTTPd

xzHTTPd: obj/main.o obj/Server.o obj/Socket.o obj/Utility.o obj/Log.o obj/Exception.o obj/Config.o obj/HTTPResponse.o obj/Client.o
	$(CC)  $(CFLAGS) $(LIB) obj/main.o obj/Server.o obj/Socket.o obj/Utility.o obj/Log.o obj/Exception.o obj/Config.o obj/HTTPResponse.o obj/Client.o  -o  xzHTTPd


obj/main.o:    src/main.cpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/main.cpp              -o  obj/main.o

obj/Server.o:  src/Server.cpp include/Server.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/Server.cpp            -o  obj/Server.o

obj/Socket.o:  src/Socket.cpp include/Socket.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/Socket.cpp            -o  obj/Socket.o

obj/Utility.o: src/Utility.cpp include/Utility.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/Utility.cpp           -o  obj/Utility.o

obj/Log.o:     src/Log.cpp include/Log.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/Log.cpp               -o  obj/Log.o

obj/Exception.o: src/Server.cpp include/Server.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/Exception.cpp         -o  obj/Exception.o

obj/Config.o:  src/Config.cpp include/Config.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/Config.cpp            -o  obj/Config.o

obj/HTTPResponse.o: src/HTTPResponse.cpp include/HTTPResponse.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/HTTPResponse.cpp      -o  obj/HTTPResponse.o

obj/Client.o:  src/Client.cpp include/Client.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES) -c   src/Client.cpp            -o  obj/Client.o


clean:
	rm -rf obj/*.o 
	rm -f  xzHTTPd

