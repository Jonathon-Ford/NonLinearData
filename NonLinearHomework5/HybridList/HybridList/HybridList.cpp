#include <iostream>
#include <string>
#include <stdexcept>
#include "HybridList.h"
using namespace std;

HybridList::HybridList() {}

HybridList::HybridList(int blockSize) {
	if (blockSize <= 0)
		throw out_of_range("Invalid block size " + to_string(blockSize));
	this->blockSize = blockSize;
}

HybridList::~HybridList() {
	clear();
}

HybridList::HybridList(const HybridList& h) {
	*this = h;
}

int HybridList::size() const {
	return numElements;
}

int HybridList::capacity() const {
	return numBlocks * blockSize;
}

int HybridList::block_size() const {
	return blockSize;
}

HybridListNode* HybridList::front() const {
	return head;
}

HybridListNode* HybridList::back() const {
	return tail;
}

double& HybridList::at(int index) const {
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			return curNode->at(index - elementsSearched);
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}

	// Iterator went beyond last block so something went horribly wrong
	abort();
}

HybridList& HybridList:: operator=(const HybridList& h) {
	clear();
	blockSize = h.blockSize;
	numElements = h.numElements;
	numBlocks = 0;

	HybridListNode* currentNode = new HybridListNode(blockSize);
	head = currentNode;
	
	HybridListNode* currentToBeCopiedNode = h.head;
	for (int j = 0; j < h.numBlocks;j++) {
		for (int i = 0; i < currentToBeCopiedNode->size(); i++) {
			currentNode->push_back(currentToBeCopiedNode->at(i));
		}
		tail = currentNode;
		HybridListNode* nextNode = new HybridListNode(blockSize);
		currentNode->next = nextNode;
		currentNode = nextNode;
		currentToBeCopiedNode = currentToBeCopiedNode->next;
		numBlocks++;
	}
	currentNode = nullptr;

	return *this;
}

void HybridList::push_back(double value) {
	if (numBlocks == 0) {
		// Hybrid list is empty so creating a new node that will be both the head
		// and tail and append the element to it
		HybridListNode* newTail = new HybridListNode(blockSize);
		newTail->push_back(value);
		tail = newTail;
		head = newTail;
		numBlocks = 1;
	}
	else if (tail->size() == blockSize) {
		// Tail node is full so create a new tail node and copy the back half of
		// the old tail node to the new tail node
		HybridListNode* newTail = new HybridListNode(blockSize);

		// Copy just under half of elements from old tail to new tail
		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newTail->push_back(tail->at(i));
		tail->resize(blockSize / 2 + 1);
		//cout << tail->size() << endl;
		// Append new item to new tail
		newTail->push_back(value);
		tail->next = newTail;
		//cout << newTail->size() << endl;
		//cout << "Tail: " << tail << endl;
		//cout << "New tail: " << newTail << endl;
		tail = newTail;
		numBlocks++;
	}
	else
		tail->push_back(value);	// Tail isn't full so just append to tail

	numElements++;
}

void HybridList::pop_back() {
	if (numElements == 0) {
		throw out_of_range("Its empty dummy");
	}
	else {
		if (tail->size() == 1) {
			numBlocks--;
			HybridListNode* currentNode = head;
			for (int i = 0; i < numBlocks; i++) {
				currentNode = currentNode->next;
			}
			delete tail;
			tail = currentNode;
		}
		else
			tail->pop_back();
	}
	numElements--;
}

void HybridList::insert(int index, double value) {
	if(index > numElements || index < 0)
		throw out_of_range("That is too far, stinky");

	int indexCheck = 0;
	HybridListNode* toInsert = head;
	while (true) {
		indexCheck += toInsert->size();
		if (indexCheck < index)
			toInsert = toInsert->next;
		else
			break;
	}
	int indexPrevious = indexCheck - toInsert->size();
	if (toInsert->size() == blockSize) {

		HybridListNode* newNode = new HybridListNode(blockSize);
		HybridListNode* prevNextNode = toInsert->next;
		newNode->next = prevNextNode;
		toInsert->next = newNode;

		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newNode->push_back(toInsert->at(i));
		toInsert->resize(blockSize / 2 + 2);
		toInsert->insert(index - indexPrevious, value);
	}
	else {
		toInsert->insert(index - indexPrevious, value);
	}
	numElements++;
}

void HybridList::erase(int index) {
	if (index > numElements || index < 0)
		throw out_of_range("That is too far, stinky");

	int indexCheck = 0;
	HybridListNode* toRemove = head;
	HybridListNode* previous = nullptr;
	while (true) {
		indexCheck += toRemove->size();
		if (indexCheck < index) {
			previous = toRemove;
			toRemove = toRemove->next;
		}
		else
			break;
	}
	int indexPrevious = indexCheck - toRemove->size();
	if (toRemove->size() == 1) {
		previous->next = toRemove->next;
		delete toRemove;
	}
	else {
		toRemove->erase(index - indexPrevious);
	}
	numElements--;
}

void HybridList::clear() {
	HybridListNode* curNode = head, * nextNode = nullptr;
	// Iterate through each node starting from the head and delete it
	while (curNode != nullptr) {
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	head = tail = nullptr;
	numElements = numBlocks = 0;
}

int main() {
	HybridList* test = new HybridList(3);
	test->push_back(1);
	test->push_back(2);
	test->push_back(3);
	test->push_back(4);
	test->push_back(5);
	HybridList* test2 = new HybridList(*test);
	cout << test2->at(0) << test2->at(1) << test2->at(2) << test2->at(3) << endl;
	test2->insert(2, 2.9);
	cout << test2->at(0) << test2->at(1) << test2->at(2) << test2->at(3) << endl;
	test2->pop_back();
	test2->erase(1);
	cout << test2->at(0) << test2->at(1) << test2->at(2);
}