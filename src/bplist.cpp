
#include "listwithheadandtail.h"
#include "node.h"

#include <cstddef>

// constructor

// initializes the list to empty
BpList::BpList(BpNode a, int b, int c)
{
  head = a;
  last = a;
  parentList = NULL;
  maxsize = b*2;
  minsize = b;
  size = 1;
  level = c;

  prevList = NULL;
  nextList = NULL;
}


BpList::BpList(int b, int c)
{
  head = NULL;
  last = NULL;
  parentList = NULL;
  maxsize = b*2;
  minsize = b;
  size = 0;
  level = c;

  prevList = NULL;
  nextList = NULL;
}


// destructor

// removes any remaining items properly from the list
BpList::~BpList()
{

  // this will result in memory leaks if the list is non-empty
  // and if the objects stored in this list are not stored elsewhere
  // to be deleted, but there's really no way around this
  while(!isEmpty())
  {
    temp = head;  
    head = head -> getNext();
    delete temp;

    size --;

  }

}


// I do not keep track of left, right parent nodes. 
// Insert node into leaf or branch.
void BpList::insertInOrder(BpNode* newNode)
{
  BpNode *curr = head;
  BpNode *prev = NULL;

  while( curr != NULL ){
    if( newNode->getData() < curr->getData() ){
      if( curr == head )
	head = newNode;
      newNode->setNext(curr->getNext);
      curr->setNext(newNode);
      break;
    } else {
      prev = curr;
      curr = curr->getNext;
    }
  }

  if( curr == NULL )
  {
    prev->setNext(newNode);
    last = newNode;
  }

  size++;
}

/*void BpList::insertAtFront(BpNode* newNode)*/
//{
  //if( head == NULL )
      //head = newNode;
  //else {
      //newNode->setNext(head);
      //head = newNode;
  //}  
  //size++;
//}

//void BpList::dequeue(BpNode* newNode)
//{
  //BpNode* data = NULL;
  //if( !isEmpty() ){
    //data = last;
    
  //size--;
  //}
//}


//Search for which branch to branch, left or right?
BpList* BpList::traverse(int data)
{
  BpNode *curr = head;
  BpNode *prev = NULL;
  BpList *nextBranch = NULL;

  while( curr != NULL) {

    if( data < curr->getData() ){
      nextBranch = curr->left;
    } else {
      prev = curr;
      curr = curr->getNext;
    }

  }

  if(curr == NULL)
    nextBranch = prev->right;

  return nextBranch;
}

void BpList::setParent(BpList* newParent){
  this -> parentList = newParent;
}

void BpList::getParent() {
  return parentList;
}

int BpList::getSize() {
  return size;
}

int BpList::getLevel() {
  return level;
}

BpList* BpList::getPrevList() {
  return prevList;
}

BpList* BpList::getNextList() {
  return nextList;
}

void BpList::setPrevList(BpList* a) {
  this -> prevList = a;
}


void BpList::setNextList(BpList* a) {
  this -> nextList = a;
}


bool BpList::tooFull() {
  return size > maxsize;
}

bool BpList::tooEmpty() {
  return size < minsize;
}

bool isEmpty() {
  return size == 0;
}

