
#include "bptree.h"
#include "linkedlist.h"
#include "node.h"

#include <iostream>
#include <cstddef>
using namespace std;

BpTree::BpTree(int d)
{
  root = new BpList(d, 0);
  first = root;
  maxsize = d*2;
  minsize = d;
  leaflevel = 0; //=numlevels
}

BpTree::~BpTree()
{
  delete();
}

void BpTree::insertBranch(BpNode pushUpNode, BpList currList){
  //restructure tree
  currList -> insertInOrder(pushUpNode);

  if( currList -> tooFull() ) {
    BpNode* curr = currList->head;
    BpNode* prev = NULL;
    BpList *leftList = NULL;
    BpList *rightList = NULL;


    //find middle node to push up
    for(int i = 0; i < minsize/2; i++){
      prev = curr;
      curr = curr->next;
    }
    //curr should be at the middle.
    

    //If its leaf level then 5 elements: 3 on right, 2 on left.
    //If not: 4 elements, 1 pushed up: 2 on right 2 on left.

    //old
    //BpList *rightList = new BpList( d, currList->getLevel() ); 
    //for(int i = 0; i < loopmax; i++)
    //  rightList->insertAtFront( currList-> dequeueList()); 
    //BpList *leftList = currList();

    prev->next = NULL;
    leftList = currList;
    if( currList->getLevel() == leaflevel )
      rightList = newBpList(curr, d, currList->getLevel(), minsize+1);
    else
      rightList = newBpList(curr->getNext(), d, currList->getLevel(), minsize);

    leftList->setNextList(rightList);
    rightList->setPrevList(leftList);

    if( currList == root ) {
      root = new BpList(curr, d, 0);
      rightList -> setParent(root);
      leftList -> setParent(root);
    } else {
      rightList -> setParent(currList->parentList);
      leftList -> setParent(currList->parentList);
    }

    insertBranch(curr, currList->parentList);
  }// end if full

}// end method


void BpTree::insert(int data)
{
  //BpNode* newNode = new BpNode(data, d, NULL);
  insertRec(data, root, 0);
}

void BpTree::insertRec(int data, BpList currList, int currlevel)
{
  if( currlevel = leafLevel ){
    BpNode* newNode = new BpNode(data, d, NULL);
    //bad naming, reusing method though.
    insertBranch( newNode, currList );
  } else {
    BpList* nextBranch = NULL;
    nextBranch = currList->traverse(data);
    insertRec( newNode, nextBranch, currlevel+1);
  }
  //return success
}


void BpTree::remove(int data)
{
  removeRec(data, root, 0);
}

void BpTree::removeRec(int data, BpList currList, int currlevel)
{
  if( currlevel = leafLevel ){
    currList->remove(data);
    
    if( currList->tooEmpty() ){
      if(
	  //
    }
  } else {
    BpList* nextBranch = NULL;
    nextBranch = currList->traverse(data);
    removeRec( newNode, nextBranch, currlevel+1);
  }
  //return success
}
bool BpList::tooFull() {
  return size > maxsize;
}

bool isEmpty() {
  return ;
}

