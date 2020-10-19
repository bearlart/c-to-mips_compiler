#include "TreeNode.h"
#include "visitor.h"

#ifndef ASAPRINT
#define ASAPRINT

class asaPrint: Visitor {
public:
    void visit(programNode *node, int indent);

    void visit(structNode *node, int indent);

    void visit(declarationsList *list, int indent);

    void visit(breakNode *node, int indent);
};

#endif

