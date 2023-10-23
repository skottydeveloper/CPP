// NOTE: Code is referenced from the algorithm and examples provided for this assignment, on Canvas.

#include "SVF-LLVM/LLVMUtil.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "WPA/Andersen.h"
#include "Assignment-3.h"

using namespace SVF;
using namespace llvm;
using namespace std;

void AndersenPTA::solveWorklist() {
    processAllAddr();

    // Keep solving until workList is empty.
    while (!isWorklistEmpty()) {
        NodeID p = popFromWorklist();
        ConstraintNode *cgNode = consCG->getConstraintNode(p);

        // Handling Store Constraints
        for (NodeID o : getPts(p)) {
            for (ConstraintEdge* edge : cgNode->getOutEdges()) {
                if (edge->getEdgeKind() == ConstraintEdge::Store) {
                    NodeID q = edge->getDstID();

                    if (unionPts(q, getPts(o))) {
                        pushIntoWorklist(q);
                    }
                }
            }
        }

        // Handling Load Constraints
        for (ConstraintEdge* edge : cgNode->getOutEdges()) {
            if (edge->getEdgeKind() == ConstraintEdge::Load) {
                NodeID r = edge->getDstID();

                for (NodeID o : getPts(p)) {
                    if (unionPts(r, getPts(o))) {
                        pushIntoWorklist(o);
                    }
                }
            }
        }

        // Handling Copy Constraints
        for (ConstraintEdge* edge : cgNode->getOutEdges()) {
            if (edge->getEdgeKind() == ConstraintEdge::Copy) {
                NodeID x = edge->getDstID();

                if (unionPts(x, getPts(p))) {
                    pushIntoWorklist(x);
                }
            }
        }
        
        // Re-evaluation: Check if the points-to set of any node has changed and if so, re-add to the worklist.
        for (ConstraintEdge* edge : cgNode->getOutEdges()) {
            NodeID nodeId = edge->getDstID();

            if (unionPts(nodeId, getPts(p))) {
                pushIntoWorklist(nodeId);
            }
        }
    }
}

// Process all address constraints to initialise pointers' points-to sets.
void AndersenPTA::processAllAddr() {
    for (ConstraintGraph::const_iterator nodeIt = consCG->begin(), nodeEit = consCG->end(); nodeIt != nodeEit; nodeIt++) {
        ConstraintNode *cgNode = nodeIt->second;

        for (ConstraintEdge* edge : cgNode->getAddrInEdges()) {
            const AddrCGEdge *addr = SVFUtil::cast<AddrCGEdge>(edge);
            
            NodeID dst = addr->getDstID();
            NodeID src = addr->getSrcID();
            
            if (addPts(dst, src)) {
                pushIntoWorklist(dst);
            }
        }
    }
}