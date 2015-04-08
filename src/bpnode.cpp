#include "BpNode.h"
#include <cstddef>

// constructor

// creates an empty node
BpNode::BpNode()
{
  data = NULL;
  next = NULL;
  left = NULL;
  right = NULL;
}

// constructor

// creates a node with a data item inside of it
  BpNode::BpNode(Object *d)
: data(d)
{
  next = NULL;
  left = NULL;
  right = NULL;
}
// getBpNode
BpNode* BpNode::getNext()
{
  return next;
}

BpNode* BpNode::getRight()
{
  return right;
}

BpNode* BpNode::getLeft()
{
  return left;
}

// getData
int BpNode::getData()
{
  return data;
}

// setNext
void BpNode::setNext(BpNode *next)
{
  this -> next = next;
}

void BpNode::setLeft(BpNode *left)
{
  this -> left = left;
}

void BpNode::setRight(BpNode *right)
{
  this -> right = right;
}


