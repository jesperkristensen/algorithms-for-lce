cl -c qsufsort.c -Fo -Zi -Yd
cl -Zi -Yd \
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
		testRandom.cpp \
		graphIncreasingLength.cpp \
		graphSpaceIncreasingLength.cpp \
		graphValue.cpp \
		functionalTest.cpp \
		str.cpp \
		graphBySaDistance.cpp \
		qsufsort.obj

# VCExpress.exe -debugexe main.exe