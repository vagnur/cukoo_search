TARGET=cs

CXX=g++
CXXFLAGS=-std=c++14 -g -ggdb -Wall -O3
INCLUDE=-I./include
OBJS=obj/egg.o obj/cuckoo.o obj/nest.o obj/cuckoo_search.o

all:
	 make $(TARGET)

$(TARGET):$(OBJS)
		    $(CXX) $^ -o $@ $(CXXFLAGS) $(INCLUDE) 

obj/egg.o:src/egg.cc include/egg.hh 
				$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)
obj/cuckoo.o:src/cuckoo.cc include/cuckoo.hh 
				$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)
obj/nest.o:src/nest.cc include/nest.hh 
				$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)
obj/cuckoo_search.o:src/cuckoosearch.cc
				$(CXX) $< -c -o $@ $(CXXFLAGS) $(INCLUDE)
				
clean:
	${RM} $(OBJS) $(TARGET) 