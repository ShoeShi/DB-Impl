
#pragma once

class BpNode;
class int;

class BpTree
{

  private:

    BpNode *first; //first data
    BpList *root; //first root
    int max;
    int min;
    int size;
    std::vector<int> levels;

  public:

    BpTree();
    ~BpTree();
    int getSize();
    bool isEmpty();
    void insertInOrder(int);
    int removeFirst();

};
