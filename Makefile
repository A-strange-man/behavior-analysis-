test: test.cpp
	g++ behavior_analysis.cc behavior_analysis.h test.cpp -o test -std=c++11

clean:
	rm -f test