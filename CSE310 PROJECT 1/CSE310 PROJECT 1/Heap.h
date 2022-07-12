/*
    Author: Brandan Tyler Lasley
    Date: 2/19/2019
*/
#pragma once
#include "Element.h"
#include <vector>
class Heap
{
public:
    Heap();
    ~Heap();

    void initialize(const size_t n);
    void buildHeap(const std::vector<Element> & array);
    void insert(const int flag, const int k);
    void deleteMin(const int flag);
    void decreaseKey(const int flag, const int index, const int value);
    void printHeap() const;

private:
    size_t      _size;
    size_t      _capacity;
    Element*    _data;

    void        swap(Element& lhs, Element& rhs);
    void        increaseCapacity();

    void        heapifyUp();
    void        heapifyDown();
};