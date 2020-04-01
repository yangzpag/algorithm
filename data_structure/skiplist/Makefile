CXX := g++
LD := g++

CXXFLAGS = -std=c++11
INCLUDE = -I.
LD_LIBS = 

SRCS = $(wildcard *.cpp) 
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: clean test 


test:$(OBJS)



%.o : %.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c -o  $@ $<





clean:
	rm -rf $(OBJS) 


	

