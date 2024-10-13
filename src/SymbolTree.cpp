#include "MathScript/SymbolTree.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

namespace MathScript
{
    SymbolTree::SymbolTree(std::string script)
    {
        _root = new SymbolNode(script);
    }

    SymbolTree::~SymbolTree()
    {
        delete _root;
    }

    SymbolNode* SymbolTree::GetRoot()
    {
        return _root;
    }

    void SymbolTree::SetRoot(SymbolNode* root)
    {
        _root = root;
    }

    void SymbolTree::SpliceLeafNode(SymbolNode* node)
    {
        if (node == _root)
        {
            return;
        }

        SymbolNode* parent = node->_parent;
        SymbolNode* grandparent = parent->_parent;
        SymbolNode* compNode = parent->_arg1 == node ? parent->_arg2 : parent->_arg1;

        if (grandparent != nullptr)
        {
            if (grandparent->_arg1 == parent)
            {
                grandparent->_arg1 = compNode;
            }
            else
            {
                grandparent->_arg2 = compNode;
            }
            
            compNode->_parent = grandparent;
        }
        else
        {
            _root = compNode;
            compNode->_parent = nullptr;
        }

        parent->_arg1 = nullptr;
        parent->_arg2 = nullptr;

        delete node;
        delete parent;
    }

    void SymbolTree::Print(SymbolNode* node, int indent)
    {
        std::string whitespace = "";

        for (int i = 0; i < indent; ++i)
        {
            whitespace += " ";
        }

        std::cout << whitespace << node->_symbol << " (" << node << "): splitting by: " << node->_operation << std::endl;

        if (node->_arg1 != nullptr)
        {
            Print(node->_arg1, indent + 2);
        }
        else
        {
            std::cout << whitespace << "  nullptr" << std::endl;
        }

        if (node->_arg2 != nullptr)
        {
            Print(node->_arg2, indent + 2);
        }
        else
        {
            std::cout << whitespace << "  nullptr" << std::endl;
        }
    }

    SymbolNode::SymbolNode(std::string symbol)
    {
        _symbol = symbol;
        _arg1 = nullptr;
        _arg2 = nullptr;
        _parent = nullptr;
    }

    SymbolNode::~SymbolNode()
    {
        delete _arg1;
        delete _arg2;
    }

    void SymbolNode::Diverge(Operation operation, SymbolNode* arg1, SymbolNode* arg2)
    {
        _operation = operation;
        _arg1 = arg1;
        _arg2 = arg2;
        
        if (_arg1 != nullptr)
        {
            _arg1->_parent = this;
        }

        if (_arg2 != nullptr)
        {
            _arg2->_parent = this;
        }
    }
}