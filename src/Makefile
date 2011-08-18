.PHONY all: main

# optimalRMQ.o jf/optimalRMQ/sdsl-0.7.0/src/sdsl/.libs/libsdsl.a
main: *.h *.cpp qsufsort.o RMQ.a
	g++ -O3 -m32 -g -o main.exe \
		main.cpp \
		correctness.cpp \
		timer.cpp \
		algDirectComp.cpp \
		algDirectLookup.cpp \
		algDirectCompLookup.cpp \
		algHash.cpp \
		algHash2Ldq.cpp \
		algHash2LCache.cpp \
		algHash2LCacheMul.cpp \
		algHash3L.cpp \
		algHash3Ld.cpp \
		algHash3Ldq.cpp \
		algHashLog.cpp \
		algHashLogD.cpp \
		algHashLogDCache.cpp \
		algRmqN.cpp \
		algRmq1.cpp \
		algRmq11.cpp \
		algFingerprint3AQCacheHorizShift.cpp \
		algFingerprint3AQCacheHorizMult.cpp \
		testRandom.cpp \
		graphIncreasingLength.cpp \
		graphSpaceIncreasingLength.cpp \
		graphValue.cpp \
		tableFiles.cpp \
		functionalTest.cpp \
		str.cpp \
		algRmq.cpp \
		graphBySaDistance.cpp \
		cacheTest.cpp \
		plotDirectCompLookup.cpp \
		qsufsort.o RMQ.a \
		$(CXXFLAGS) \
		-Wl,--enable-auto-import

qsufsort.o: qsufsort.c qsufsort.h
	gcc -c -g -O3 -m32 -fomit-frame-pointer -W -Wall -Winline -DDEBUG=0 -DNDEBUG=1 qsufsort.c -o qsufsort.o

RMQ.a: force_look
	cd RMQ_n_logn; $(MAKE) RMQ.a
	cp RMQ_n_logn/RMQ.a RMQ.a

#optimalRMQ.o: jf/optimalRMQ/optimalRMQ.cpp jf/optimalRMQ/optimalRMQ.hpp
#	g++ -O3 -g -c jf/optimalRMQ/optimalRMQ.cpp -o optimalRMQ.o

clean:
	rm *.o
	rm main.exe

force_look:
	true
