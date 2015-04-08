#pragma once


class BpNode
{
  private:
    Object *data;
    BpNode *next;
    BpNode *left;
    BpNode *right;
    BpNode *pleft;
    BpNode *pright;


  public:
    BpNode();
    BpNode(Object *d);
    BpNode* getNext();
    int getData();
    void setNext(BpNode *next);
    void setPleft(BpNode *pleft);
    void setPright(BpNode *pright);
    void setLeft(BpNode *left);
    void setRight(BpNode *right);
}

