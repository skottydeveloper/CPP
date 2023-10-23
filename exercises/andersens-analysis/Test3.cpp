#include "Assignment-3.h"

#include "SVF-LLVM/LLVMUtil.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "WPA/Andersen.h"
#include "Util/Options.h"
#include "Util/CommandLine.h"

void Test1() {
    SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./Assignment-3/testcase/bc/no_alias.ll"});
    
    // Build Program Assignment Graph (SVFIR).
    SVF::SVFIRBuilder builder(svfModule);
    SVF::SVFIR *pag = builder.build();

    pag->dump("./Assignment-3/testcase/dot/no_alias_init");
    
    AndersenPTA *andersenPTA = new AndersenPTA(pag);
    andersenPTA->analyze();
    andersenPTA->dump_consCG("./Assignment-3/testcase/dot/no_alias_final");
    delete andersenPTA; 
    
    SVF::LLVMModuleSet::releaseLLVMModuleSet();
    SVF::SVFIR::releaseSVFIR();
}

void Test2() {
    SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./Assignment-3/testcase/bc/CI-global.ll"});
    
    // Build Program Assignment Graph (SVFIR).
    SVF::SVFIRBuilder builder(svfModule);
    SVF::SVFIR *pag = builder.build();
    
    pag->dump("./Assignment-3/testcase/dot/CI-global_init");
    
    AndersenPTA *andersenPTA = new AndersenPTA(pag);
    andersenPTA->analyze();
    andersenPTA->dump_consCG("./Assignment-3/testcase/dot/CI-global_final");
    delete andersenPTA; 
    
    SVF::SVFIR::releaseSVFIR();
    SVF::LLVMModuleSet::releaseLLVMModuleSet();
}

void Test3() {
    SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./Assignment-3/testcase/bc/CI-local.ll"});
    
    // Build Program Assignment Graph (SVFIR).
    SVF::SVFIRBuilder builder(svfModule);
    SVF::SVFIR *pag = builder.build();
    
    pag->dump ("./Assignment-3/testcase/dot/CI-local_init");
    
    AndersenPTA *andersenPTA = new AndersenPTA(pag);
    andersenPTA->analyze();
    andersenPTA->dump_consCG("./Assignment-3/testcase/dot/CI-local_final");
    
    SVF::LLVMModuleSet::releaseLLVMModuleSet();
    SVF::SVFIR::releaseSVFIR();
    
    delete andersenPTA; 
}
void Test() {
    Test1();
    Test2();
    Test3();
}

int main(int argc, char ** argv) {
    int arg_num = 0;
    int extraArgc = 1;

    char **arg_value = new char *[argc + extraArgc];
    
    for (; arg_num < argc; ++arg_num) {
        arg_value[arg_num] = argv[arg_num];
    }

    // You may comment it to see the details of the analysis.
    arg_value[arg_num++] = (char*) "-stat=false";

    std::vector<std::string> moduleNameVec;

    moduleNameVec = OptionBase::parseOptions(arg_num, arg_value, "Teaching-Software-Analysis Assignment 3", "[options]");
    
    Test();

    return 0;
}