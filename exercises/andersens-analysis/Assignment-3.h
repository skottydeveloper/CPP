#ifndef ASSIGNMENT_3_H_
#define ASSIGNMENT_3_H_
#include "SVF-LLVM/LLVMUtil.h"
#include "WPA/Andersen.h"

class AndersenPTA: public SVF::AndersenBase {
public:
    // Constructor.
    AndersenPTA(SVF::SVFIR* _pag) : AndersenBase(_pag){};

    // Dump constraint graph.
    void dump_consCG(std::string name) {
        consCG->dump(name);
    };

private:
    // Process all the address constraint edges.
    void processAllAddr();

    virtual void solveWorklist();

    // Add copy edge on constraint graph.
    virtual bool addCopyEdge(SVF::NodeID src, SVF::NodeID dst) {
        if (consCG->addCopyCGEdge(src, dst)) {
            return true;
        } else {
            return false;
        }
    }
};

#endif