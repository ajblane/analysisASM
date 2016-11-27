#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstIterator.h" //instructions(&Fn)
#include "llvm/IR/Instructions.h" //BinaryOperator
#include "llvm/IR/Type.h" //FunctionTyID
#include "llvm/IR/GlobalValue.h"
#include "llvm/Support/raw_ostream.h" //errs()
#include <time.h> 
#include <algorithm> //rand()
#include <llvm/IR/InlineAsm.h> //InlineAsm
#include <llvm/ADT/SmallVector.h> //SmallVector
#include "llvm/Target/TargetLowering.h"//ImmutableCallSite
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h" //ReplaceInstWithInst
#include "llvm/IR/InlineAsm.h"

//register
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

namespace {
 
	struct PointerGuard : public ModulePass {
		static char ID; 
		PointerGuard() : ModulePass(ID){

		}
		bool runOnModule(Module &M) override;

	
	};
}
bool PointerGuard :: runOnModule(Module &mod){ 

    for(Module::iterator Fn = mod.begin(), E = mod.end(); Fn!= E; ++Fn)
    {
	//errs() << (*Fn).getName() << '\n';
	for (Instruction &I : instructions(&(*Fn))) {
	    if(CallInst* IA = dyn_cast<CallInst>(&I)){
	    	if(IA->isInlineAsm()){ 
		    errs() << "IR: \n\t" << *IA << '\n';
		    errs() << "CallInst.getNumArgOperands: \n\t" <<IA->getNumArgOperands () << '\n';
		    errs() << "CallInst.getCalledValue: \n\t" << *IA->getCalledValue()<< '\n';
		    errs() << "CallInst.getOperand(0): \n\t"<< *IA->getOperand(0) << '\n';
		    errs() << "CallInst.getOperand(0).type: \n\t" << *IA->getOperand(0)->getType()  << '\n';
		    InlineAsm *aa = dyn_cast<InlineAsm>(IA->getCalledValue());
		    errs() << "InlineAsm.getAsmString: \n\t" << aa->getAsmString() << '\n'; 
	            errs() << "InlineAsm.getConstraintString:\n\t" << aa->getConstraintString () << '\n';
		}
            }
	    
	}
    }
    return true;
}



char PointerGuard::ID = 0;

static void registerReplacePass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
    PM.add(new PointerGuard());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerReplacePass);

static RegisterPass<PointerGuard> X("hello", "Hello World Pass",true,true);
