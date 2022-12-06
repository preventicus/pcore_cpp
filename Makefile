make all: format unit 
format:
		find src -not -path "*/protobuf*"| grep ".*/.*\.\(c\|cpp\|h\)$$"| xargs clang-format -i
		find test/ | grep ".*/.*\.\(c\|cpp\|h\)$$"| xargs clang-format -i
		find include -not -path "*/protobuf*"| grep ".*/.*\.\(c\|cpp\|h\)$$"| xargs clang-format -i
		
unit:
		cd build && cmake .. && make && ctest 

build:
		cd build && cmake .. && make 
