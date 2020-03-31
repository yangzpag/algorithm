CXX := g++
LD := g++

CXXFLAGS = -std=c++11
INCLUDE = -I.
LD_LIBS = -lgtest -lgtest_main -lpthread

SRCS = $(wildcard *.cpp) 
SRCS += $(wildcard test/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: clean test 


test:testRB

testRB:$(OBJS)
	@echo $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $(OBJS) $(LD_LIBS)



%.o : %.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c -o  $@ $<





clean:
	rm -rf $(OBJS) testRB


	

