#include <BPTree.hpp>

#include <exception>

using namespace A4;

BPTree::BPTree( uint32_t d ): m_d( d ) {

}

BPTree::~BPTree() {

}

void BPTree::insert( int32_t data ) {
	auto desiredLeafNode = m_root;

	if( ! desiredLeafNode ) {
		m_root = nodePtr_t( new BPTreeNode( nodePtr_t() ) );
		m_root->m_data.push_back( data );
		return;
	}

	//Find the leaf node where the new entry 'belongs'
	while( ! desiredLeafNode->isLeaf() ) {
		BPTreeIndexNode *currentIndexNode = dynamic_cast<BPTreeIndexNode *>( desiredLeafNode.get() );
		if ( ! currentIndexNode ) {
			throw std::exception( "Failed to cast node into index node" );
		}

		auto it = currentIndexNode->m_indexes.begin();
		auto end = currentIndexNode->m_indexes.end();
		std::size_t currentIndex = 0;
		for( it; it != end && currentIndexNode->m_data[currentIndex] < data; ++it, ++currentIndex );

		desiredLeafNode = currentIndexNode->m_indexes[currentIndex];
	}

	desiredLeafNode->m_data.push_back( data );

	uint32_t twoD = 2 * m_d;

	if( desiredLeafNode->m_data.size() > twoD ) {

		auto currentNode = desiredLeafNode;

		//Loop until the current node is either the root, or has 2 * m_d or less entries
		while( currentNode->m_data.size() >= twoD && !currentNode->m_parent ) {
			BPTreeIndexNode *currentIndexNode = dynamic_cast< BPTreeIndexNode * >( currentNode.get() );
			auto parentUncast = currentNode->m_parent;
			BPTreeIndexNode *parent = dynamic_cast< BPTreeIndexNode * >( parentUncast.get() );

			if( currentIndexNode ) {
				//The current node is not a leaf

				std::shared_ptr<BPTreeIndexNode> newSiblingIndex;
				nodePtr_t newSibling = newSiblingIndex;

				uint32_t copyUp = currentNode->m_data[m_d];

				for( std::size_t i = m_d + 1; i < currentNode->m_data.size(); ++i ) {
					newSibling->m_data.push_back( currentNode->m_data[i] );
				}
				currentNode->m_data.erase( currentNode->m_data.begin() + m_d, currentNode->m_data.end() );

				for( std::size_t i = m_d; i < currentIndexNode->m_indexes.size(); ++i ) {
					newSiblingIndex->m_indexes.push_back( currentIndexNode->m_indexes[i] );
				}
				currentIndexNode->m_indexes.erase( currentIndexNode->m_indexes.begin() + m_d, currentIndexNode->m_indexes.end() );

				std::size_t locInParent = 0;

				for( ; locInParent < parent->m_data.size() && parent->m_data[locInParent] < data; ++locInParent );

				parent->m_indexes.insert( parent->m_indexes.begin() + locInParent + 1, newSibling );

				parent->m_data.insert( parent->m_data.begin() + locInParent, copyUp );
			} else {
				//The current node is a leaf

				nodePtr_t newSibling;
				for( std::size_t i = m_d; i < currentNode->m_data.size(); ++i ) {
					newSibling->m_data.push_back( currentNode->m_data[i] );
				}
				currentNode->m_data.erase( currentNode->m_data.begin() + m_d, currentNode->m_data.end() );

				std::size_t locInParent = 0;

				for( ; locInParent < parent->m_data.size() && parent->m_data[locInParent] < data; ++locInParent );

				parent->m_indexes.insert( parent->m_indexes.begin() + locInParent + 1, newSibling );

				parent->m_data.insert( parent->m_data.begin() + locInParent, newSibling->m_data[0] );
			}

			currentNode = parentUncast;
		}

		if( !currentNode->m_parent && currentNode->m_data.size() > twoD ) {
			//It appears we must split the root
			BPTreeIndexNode *currentIndexNode = dynamic_cast< BPTreeIndexNode * >(currentNode.get());

			if( currentIndexNode ) {
				//The root is not a leaf node
				std::shared_ptr<BPTreeIndexNode> newRoot;
				newRoot->m_data.push_back( currentNode->m_data[m_d] );
				newRoot->m_indexes.push_back( currentNode );
				std::shared_ptr<BPTreeIndexNode> newSibling;

				for( std::size_t i = m_d + 1; i < currentNode->m_data.size(); ++i ) {
					newSibling->m_data.push_back( currentNode->m_data[i] );
				}
				currentNode->m_data.erase( currentNode->m_data.begin() + m_d, currentNode->m_data.end() );
				newRoot->m_indexes.push_back( newSibling );
				m_root = newRoot;
			} else {
				//The root is a leaf node
				std::shared_ptr<BPTreeIndexNode> newRoot;
				newRoot->m_data.push_back( currentNode->m_data[m_d] );
				newRoot->m_indexes.push_back( currentNode );
				auto newSibling = nodePtr_t();

				for( std::size_t i = m_d; i < currentNode->m_data.size(); ++i ) {
					newSibling->m_data.push_back( currentNode->m_data[i] );
				}
				currentNode->m_data.erase( currentNode->m_data.begin() + m_d, currentNode->m_data.end() );
				newRoot->m_indexes.push_back( newSibling );
				m_root = newRoot;
			}
		}
	}

}

BPTreeNode::BPTreeNode( BPTree::nodePtr_t parent ): m_parent( parent ) {

}

BPTreeNode::~BPTreeNode() {

}

bool BPTreeNode::isLeaf() {
	return true;
}

BPTreeIndexNode::BPTreeIndexNode( BPTree::nodePtr_t parent ) : BPTreeNode( parent ) {

}

BPTreeIndexNode::~BPTreeIndexNode() {

}

bool BPTreeIndexNode::isLeaf() {
	return false;
}