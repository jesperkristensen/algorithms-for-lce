FLAG = -O3 -m32 -DDEBUG=0 -DNDEBUG=1 -fomit-frame-pointer -funroll-loops -Winline

OBJECTS=RMQ_n_1_improved.o RMQ_nlogn_1.o RMQ_n_logn_2.o RMQ_n_logn_4.o RMQ_1_n.o RMQ_succinct.o RMQ_n_logn.o

RMQ_n_1_improved.o: RMQ_n_1_improved.cpp RMQ_n_1_improved.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_n_1_improved.cpp

RMQ_nlogn_1.o: RMQ_nlogn_1.cpp RMQ_nlogn_1.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_nlogn_1.cpp

RMQ_n_logn.o: RMQ_n_logn.cpp RMQ_n_logn.hpp RMQ.hpp RMQ_nlogn_1.hpp
	g++ $(FLAG) -c RMQ_n_logn.cpp

RMQ_n_logn_2.o: RMQ_n_logn_2.cpp RMQ_n_logn_2.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_n_logn_2.cpp
								 								                                                      
RMQ_n_logn_4.o: RMQ_n_logn_4.cpp RMQ_n_logn_4.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_n_logn_4.cpp
	
RMQ_1_n.o: RMQ_1_n.cpp RMQ_1_n.hpp
	g++ $(FLAG) -c RMQ_1_n.cpp	
	
RMQ_succinct.o: RMQ_succinct.cpp RMQ_succinct.hpp RMQ.hpp
	g++ $(FLAG) -c RMQ_succinct.cpp
	
RMQ.a: $(OBJECTS)
	ar rcs RMQ.a $(OBJECTS)	
	
clean:
	rm *.a *.o	