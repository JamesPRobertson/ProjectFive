#include <iostream>
#include <memory>
#include "SortedListInterface.h"

template <typename ItemType>
class Node{
private:
	ItemType data;
	Node *nextNode;

public:
	Node(ItemType inputData, Node<ItemType> inputNextNode):data(inputData), nextNode(&inputNextNode){}
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

	/*
	Node<ItemType> * getPreviousNode(ItemType inputData){
		Node<ItemType> * currentNode = head;
		Node<ItemType> * previousNode = head;

		while(currentNode != nullptr && currentNode->getData() != inputData){
			previousNode = currentNode;
			currentNode = currentNode->getNextNode();
		}

		return previousNode;
	}
	 */

	Node<ItemType> * getPreviousNode(Node<ItemType> &inputNode){
		Node<ItemType> * currentNode = head;
		Node<ItemType> * previousNode = head;

		while(currentNode != nullptr && currentNode != &inputNode){
			previousNode = currentNode;
			currentNode = currentNode->getNextNode();
		}

		return previousNode;

	}

public:
	virtual bool insertSorted(const ItemType& newEntry){
		if(head == nullptr){
			head = new Node<ItemType>(newEntry);

			return true;
		}

		Node<ItemType> * traversalNode = head;

        while(traversalNode->getNextNode() != nullptr && traversalNode->getData() > newEntry){
            traversalNode = traversalNode->getNextNode();
        }

		if(traversalNode->getNextNode() == nullptr){
		    traversalNode->setNextNode(new Node<ItemType>(newEntry));
		}
		else{
            Node<ItemType> * tempNode = new Node<ItemType>(newEntry, *traversalNode);
            getPreviousNode(*traversalNode)->setNextNode(tempNode);
		}

        while(traversalNode != nullptr){
            traversalNode = traversalNode->getNextNode();
        }
		/*
		while(traversalNode != nullptr && traversalNode->getData() < newEntry){
			traversalNode = traversalNode->getNextNode();
		}
        */

		//getPreviousNode cannot work on a null pointer


		return true;
	}

	virtual bool removeSorted(const ItemType& anEntry) {}

	virtual int getPosition(const ItemType& anEntry) const {
		return -1;
	}

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

		return true;
	};

	/** Removes all entries from this list. */
	virtual void clear(){}

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


int main() {
	SortedListInterface<int> * myList = new SortedLinkedList<int>();
	std::string inputString = "";

	std::cout << "Please enter a few numbers, ints please" << std::endl;
	for(int i = 0; i < 7; i++){
		std::getline(std::cin, inputString);
		myList->insertSorted(std::atoi(&inputString[0]));
	}

	for(int i = 0; i < 7; i++){
		std::cout << myList->getEntry(i) << std::endl;
	}

	std::cin;
	return 0;
}
