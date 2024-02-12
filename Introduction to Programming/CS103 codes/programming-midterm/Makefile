CXX = g++ -g
	
all: split banner

split: split.cpp
	$(CXX) split.cpp -o split
	
check_split: FORCE
	$(CXX) check_split.o split.cpp -DTEST -o check_split
	./check_split 0 1 2 3 4 5 6 7 8

check_split_c: FORCE
	$(CXX) check_split.o split.cpp -DTEST -o check_split
	
clean:
	touch split.cpp
	touch banner.cpp
	
check_read_font: banner.cpp
	$(CXX) check_read_font.o -DRF banner.cpp -o check_read_font
	./check_read_font big.font
	
check_make_banner: banner.cpp
	$(CXX) check_make_banner.o -DMB banner.cpp -o check_make_banner
	./check_make_banner big.font
	
check_banner_main: banner.cpp
	$(CXX) check_banner_main.o -DMAIN banner.cpp -o banner
	bash check_banner_main.sh
	@rm -rf sol.txt stu.txt
	
banner: banner.cpp
	$(CXX) -DRF -DMB -DPB -DMAIN banner.cpp -o banner
	
FORCE:
