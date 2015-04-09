#pragma once

#include <cstdint>

#include <memory>
#include <vector>

namespace Q1 {

	class BPTreeNode;
	class BPTreeIndexNode;
	class BPTree;

	class BPTreeNode {
		friend class BPTree;
		typedef std::vector<int32_t> dataBuffer_t;
	protected:
		dataBuffer_t m_data;
		std::shared_ptr<BPTreeNode> m_parent;
	public:
		BPTreeNode( std::shared_ptr<BPTreeNode> parent );
		~BPTreeNode();
		virtual bool isLeaf();
	
	};

	class BPTreeIndexNode : public BPTreeNode {
		friend class BPTree;
		typedef std::vector<std::shared_ptr<BPTreeNode> > indexBuffer_t;
	private:
		indexBuffer_t m_indexes;
	public:
		BPTreeIndexNode( std::shared_ptr<BPTreeNode> parent );
		~BPTreeIndexNode();
		bool isLeaf();
	};

	class BPTree {
	public:
		typedef std::shared_ptr<BPTreeNode> nodePtr_t;
	private:
		uint32_t m_d;
		std::shared_ptr<BPTreeNode> m_root;
	public:
		BPTree( uint32_t d );
		~BPTree();
		void insert( int32_t data );
		void del( int32_t data );
		void printTree();
	};

}

