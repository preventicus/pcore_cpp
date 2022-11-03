format:
		find src/ | grep ".*/.*\.\(c\|cpp\|h\)$$"| xargs clang-format -i
		find test/ | grep ".*/.*\.\(c\|cpp\|h\)$$"| xargs clang-format -i
		find include/ | grep ".*/.*\.\(c\|cpp\|h\)$$"| xargs clang-format -i
		
