CXX := g++
LD := g++

CXXFLAGS = -std=c++11
INCLUDE = -I include
LD_LIBS = -lgtest -lgtest_main -lpthread 

SRCS = DataInputStream.cpp      \
	   TupleDesc.cpp  Field.cpp \
	   DataOutputStream.cpp		\
		BTreeInternalPage.cpp	\
		BTreeLeafPage.cpp

TESTSRCS = test//TestDataInputStream.cpp \
		   test//TestTupleDesc.cpp       \
			test//TestRecordId.cpp		\
			test//TestBTreeInternalPage.cpp	\
			test//TestBTreeLeafPage.cpp

OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TESTOBJS = $(patsubst %.cpp,%.o,$(TESTSRCS))


TARGET = test//TestDataInputStream 	\
		 test//TestTupleDesc		\
		 test//TestRecordId			\
		 test//TestBTreeInternalPage	\
		 test//TestBTreeLeafPage
.PHONY: clean test 


test: $(TARGET)

test//TestDataInputStream: DataInputStream.o test//TestDataInputStream.o
	$(LD) $(CXXFLAGS) -o $@ $^ $(LD_LIBS)

test//TestTupleDesc:DataInputStream.o TupleDesc.o  Field.o test//TestTupleDesc.o
	$(LD) $(CXXFLAGS) -o $@ $^ $(LD_LIBS)


test//TestRecordId:test//TestRecordId.o
	$(LD) $(CXXFLAGS) -o $@ $^ $(LD_LIBS)

test//TestBTreeInternalPage:test//TestBTreeInternalPage.o $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $^ $(LD_LIBS)

test//TestBTreeLeafPage:test//TestBTreeLeafPage.o $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $^ $(LD_LIBS)

%.o : %.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c -o  $@ $<





clean:
	rm -rf $(OBJS) $(TARGET)

	

