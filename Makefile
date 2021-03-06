CXX=g++
CXXFLAGS=-std=c++11 -ggdb -Wall -pthread -I.
CXXLIBS=-lpthread
LDFLAGS=-L.
CXXOBJS=Mutex.o Thread.o Logger.o CondVar.o Util.o Socket.o Buffer.o Channel.o EventLoop.o TcpAcceptor.o
AR=ar
CXXTESTS=$(shell find test -name "*.cpp")
TESTS=${CXXTESTS:.cpp=}

LIBRARY=libyoungnet.a
TARGETS=${CXXOBJS} ${LIBRARY} ${TESTS}
all:${TARGETS}

${LIBRARY}:${CXXOBJS}
	rm -f $@
	${AR} -rs $@ ${CXXOBJS}

${TESTS}: ${LIBRARY} ${CXXTESTS}

.cpp.o:
	${CXX} ${CXXFLAGS} -c $< -o $@
.cpp:
	${CXX} -o $@ $< ${CXXFLAGS} ${LDFLAGS} ${LIBRARY} ${CXXLIBS}

clean:
	-rm -f ${TARGETS}
	-rm -f */*.o
