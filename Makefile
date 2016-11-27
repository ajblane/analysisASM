LLVM_CONFIG=/usr/bin/llvm-config
CC = clang
CXX = g++
SRC_DIR?=$(PWD)/llvm-pass
TESTS_SRC_DIR?=$(PWD)/asmsample

COMMON_FLAGS= -Wall -Wextra

CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)

LDFLAGS=`$(LLVM_CONFIG) --ldflags`
ASMFILE = text

all: hello.so $(ASMFILE).bc analyze transform_and_link

%.so: %.o	
	@$(CXX) -shared $< -o $@ $(LDFLAGS)  

%.o: $(SRC_DIR)/%.cpp
	@$(CXX) -c $< -o $@ $(CXXFLAGS) 

%.bc: $(TESTS_SRC_DIR)/%.c
	@$(CC) -c -emit-llvm $< -o $@ 

analyze:
	@echo Analyzing $(ASMFILE).bc by using the Hello pass
	opt -load ./hello.so -hello $(ASMFILE).bc -o $(ASMFILE)_pass.bc 
	@llvm-dis $(ASMFILE)_pass.bc
	@llvm-dis $(ASMFILE).bc
	@llc $(ASMFILE)_pass.bc
transform_and_link:
	@echo Transforming and Link analysis results
	@llc -filetype=obj $(ASMFILE)_pass.bc
	@llvm-objdump -d $(ASMFILE)_pass.o > objdump_$(ASMFILE)_pass
	$(CC) $(ASMFILE)_pass.o 



clean:
	rm -f *.o *.so *.bc *.cpp *.out *.ll *.s objdump_$(ASMFILE)_pass
