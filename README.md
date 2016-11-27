# analysisSimpleASM

only knwon composition of ASM by using llvm pass

### Requirements

* Ubuntu 16.04
* LLVM 3.8
* Clang 3.8


### Install

* Install clang

```
$ sudo apt-get update
$ sudo apt-get install clang
```

* Install llvm

```
$ sudo apt-get update
$ sudo apt-get install llvm
```
### Usage:

* Compile the exploit code with the pointer guard pass

Need to check where llvm-config is:

```
$ whereis llvm-config
llvm-config: /usr/bin/llvm-config
```

```
$ cd llvm-pass
$ make LLVM_CONFIG='/usr/bin/llvm-config'
```

You should see:

```
IR: 
	 call void asm sideeffect "sidt $0", "=*m,~{dirflag},~{fpsr},~{flags}"(i32* %4) #1, !srcloc !1
CallInst.getNumArgOperands: 
	1
CallInst.getCalledValue: 
	void (i32*)* asm sideeffect "sidt $0", "=*m,~{dirflag},~{fpsr},~{flags}"
CallInst.getOperand(0): 
	  %4 = load i32*, i32** %dtr, align 8
CallInst.getOperand(0).type: 
	i32*
InlineAsm.getAsmString: 
	sidt $0
InlineAsm.getConstraintString:
	=*m,~{dirflag},~{fpsr},~{flags}
```

