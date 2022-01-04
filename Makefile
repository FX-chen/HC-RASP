#app:   main.cpp        fun1.cpp        fun2.cpp
#       g++ main.cpp    fun1.cpp        fun2.cpp        -o app


# app: main.o fun1.o fun2.o
# 	g++ main.o fun1.o fun2.o -o app
# main.o: main.cpp
# 	g++ -c main.cpp -o main.o
# fun1.o: fun1.cpp
# 	g++ -c fun1.cpp -o fun1.o 
# fun2.o: fun2.cpp
# 	g++ -c fun2.cpp -o fun2.o



# obj = main.o fun1.o fun2.o  
# target = app  
# CC = g++  

# $(target):$(obj)
# 	$(CC) $(obj) -o $(target)

# %.o: %.cpp
# 	$(CC) -c $< -o $@


# clean:
# 	-rm app

src = $(wildcard ./*.cpp)
obj = $(patsubst %.cpp, %.o, $(src))
target = get_data
CXX = g++
LIBS =-lwiringPi
CFLAGS = -I/usr/include/python2.7 -lpython2.7 -std=c++11 -pthread
LDFLAGS := $(shell python-config --ldflags)
$(target):$(obj)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(LIBS) $(obj)  -o $(target)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(LIBS)  -c $< -o $@

.PHONY: clean  
clean:  
	rm -rf $(obj) $(target) 

