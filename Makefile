
NSPR_FLAGS=`nspr-config --cflags`
NSPR_LIBS=`nspr-config --libs`

CC=g++
INCLUDES=-Iinclude $(NSPR_FLAGS)
CFLAGS=-c -Wall
LIB=$(NSPR_LIBS)



all: xzHTTPd

xzHTTPd: obj/main.o obj/Server.o obj/Socket.o obj/Utility.o obj/Log.o obj/Exception.o obj/Config.o obj/HTTPResponse.o obj/Client.o
	$(CC) $(LIB) obj/main.o obj/Server.o obj/Socket.o obj/Utility.o obj/Log.o obj/Exception.o obj/Config.o obj/HTTPResponse.o obj/Client.o -g -o  xzHTTPd


obj/main.o:    src/main.cpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/main.cpp          -g    -o  obj/main.o

obj/Server.o:  src/Server.cpp include/Server.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/Server.cpp        -g    -o  obj/Server.o

obj/Socket.o:  src/Socket.cpp include/Socket.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/Socket.cpp        -g    -o  obj/Socket.o

obj/Utility.o: src/Utility.cpp include/Utility.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/Utility.cpp       -g    -o  obj/Utility.o

obj/Log.o:     src/Log.cpp include/Log.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/Log.cpp           -g    -o  obj/Log.o

obj/Exception.o: src/Server.cpp include/Server.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/Exception.cpp     -g    -o  obj/Exception.o

obj/Config.o:  src/Config.cpp include/Config.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/Config.cpp        -g    -o  obj/Config.o

obj/HTTPResponse.o: src/HTTPResponse.cpp include/HTTPResponse.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/HTTPResponse.cpp  -g    -o  obj/HTTPResponse.o

obj/Client.o:  src/Client.cpp include/Client.hpp
	$(CC)  $(CFLAGS)  $(INCLUDES)    src/Client.cpp        -g    -o  obj/Client.o

clean:
	rm -rf obj/*.o 
	rm -f  xzHTTPd

