#pragma once

class BpNode;
class Object;

class BpList
{

	private:
	
		BpNode *head;
		BpNode *tail;
		int size;
	
	public:
	
		BpList();
		~BpList();
		
		void insertAtEnd(Object*);
		Object *removeFromFront();
		Object *getFront();
		
		int getSize();
		bool isEmpty();

};
