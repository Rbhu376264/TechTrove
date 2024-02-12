CXX = g++ -g
	
colchart: colchart.cpp
	$(CXX) colchart.cpp -o colchart
	
test: colchart
	bash ./test.sh 1
	bash ./test.sh
	
clean:
	rm -f colchart
	