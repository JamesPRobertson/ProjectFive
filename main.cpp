#include <iostream>
#include "SortedListInterface.h"

int main() {

	return 0;
}

template <typename ItemType>
class Node{
private:
	ItemType data;
	Node *nextNode;

public:
	Node(ItemType inputData):data(inputData), nextNode(nullptr){}
	Node():data(nullptr), nextNode(nullptr){};

	char getData() const {
		return data;
	}

	void setData(ItemType inputData) {
		this->data = inputData;
	}

	Node *getNextNode() const {
		return nextNode;
	}

	void setNextNode(Node *inputNextNode) {
		this->nextNode = inputNextNode;
	}

};


template <typename ItemType>
class SortedLinkedList :  public SortedListInterface<ItemType>{
private:
	Node<ItemType> * head;
public:
	virtual bool insertSorted(const ItemType& newEntry) = 0;

	virtual bool removeSorted(const ItemType& anEntry) = 0;

	virtual int getPosition(const ItemType& anEntry) const = 0;

	// The following methods are the same as those given in ListInterface
	// in Listing 8-1 of Chapter 8 and are completely specified there.

	virtual bool isEmpty() const{
		return head == nullptr;
	}

	virtual int getLength() const{
		int count = 0;
		Node<ItemType> * traversalNode = head;

		while(traversalNode != nullptr){
			traversalNode = traversalNode->getNextNode();
			count++;
		}

		return count;
	}

	virtual bool remove(int position){
		Node<ItemType> * curNode = head->getNextNode();
		Node<ItemType> * prevNode = head;

		for(int i = 0; i < position - 1; i++){
			curNode = curNode->getNextNode();
			prevNode = prevNode->getNextNode();
		}

		prevNode->setNextNode(curNode->getNextNode());
		delete curNode;
	};

	/** Removes all entries from this list. */
	virtual void clear() = 0;

	virtual ItemType getEntry(int position) const{
		Node<ItemType> * traversalNode = head;

		for(int i = 0; i < position; i++){
			traversalNode = traversalNode->getNextNode();
		}

		return traversalNode->getData();
	};

	/** Destroys object and frees memory allocated by object. */
	virtual ~SortedLinkedList() { }
};