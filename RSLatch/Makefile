SYSTEMC_HOME = /path/to/systemc
SYSTEMC_LIBDIR = $(SYSTEMC_HOME)/lib-linux64
SYSTEMC_INCDIR = $(SYSTEMC_HOME)/include

CXX = g++
CXXFLAGS = -I$(SYSTEMC_INCDIR) -L$(SYSTEMC_LIBDIR) -lsystemc -lm -std=c++11

TARGET = testRSLatch
SRCS = RSLatch.cpp testRSLatch.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
    $(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET)

clean:
    rm -f $(TARGET) *.o