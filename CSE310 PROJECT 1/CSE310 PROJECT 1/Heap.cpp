/*
    Author: Brandan Tyler Lasley
    Date: 2/19/2019
*/
#include "Heap.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <exception>

// https://www2.cs.duke.edu/courses/cps130/fall98/lectures/lect08/node17.html
// https://www.cse.psu.edu/~ads22/courses/cmpsc465/S12/lec-notes/CMPSC465-S12-Lec-20-21-heaps.pptx.pdf
#define GET_LEFT_CHILD(i)       (2 * i + 1)
#define GET_RIGHT_CHILD(i)      (2 * i + 2)
#define GET_PARENT(i)           ((i - 1) / 2)

#define HAS_LEFT_CHILD(i)       (GET_LEFT_CHILD(i) < _size)
#define HAS_RIGHT_CHILD(i)      (GET_RIGHT_CHILD(i) < _size)
#define HAS_PARENT(i)           (GET_PARENT(i) >= 0)

#define LEFT_CHILD(i)           (GET_LEFT_CHILD(_data[i]))
#define RIGHT_CHILD(i)          (GET_RIGHT_CHILD(_data[i]))
#define PARENT(i)               (GET_PARENT(_data[i]))

Heap::Heap() : _size(0), _capacity(0), _data(nullptr)
{

}

Heap::~Heap()
{
    if (_data)
        delete _data;
}

void Heap::initialize(const size_t n)
{
    try
    {
        if (_data)
            delete _data;
        _size = 0;
        _capacity = n;
        _data = new Element[n];
    }
    catch (const std::bad_alloc & e)
    {
        _capacity = 0;
        std::cout << "Error initializing heap: " << e.what() << '\n';
    }
}

void Heap::buildHeap(const std::vector<Element>& Array)
{
    initialize(Array.size());

}

void Heap::insert(const int flag, const int k)
{
    if (_data)
    {
        if (flag == 2)
            this->printHeap();
        increaseCapacity();
        _data[_size] = k;
        heapifyUp();
    }
    else
        std::cout << "Error heap not initialized\n";
}

void Heap::deleteMin(const int flag)
{
    // Pop top essentially. 
    if (_data)
    {
        _data[0] = _data[_size - 1];
        _size--;
        heapifyDown();
    }
    else
        std::cout << "Error heap not initialized\n";
}

void Heap::decreaseKey(const int flag, const int index, const int value)
{
    if (_data)
    {

    }
    else
        std::cout << "Error heap not initialized\n";
}

void Heap::printHeap() const
{
    if (_data)
    {

    }
    else
        std::cout << "Error heap not initialized\n";
}

void Heap::swap(Element & lhs, Element & rhs)
{
    Element tmp = lhs;
    lhs = rhs;
    rhs = lhs;
}

void Heap::increaseCapacity()
{
    if (_size == _capacity)
    {
        assert(_data);

        try
        {
            _capacity *= 2;

            // realloc isn't C++ therefore cannot be used with my new/delete.
            // so we have to copy.
            Element * d = new Element[_capacity];

            // If size > 0, copy data over.
            if (_size)
                std::memcpy(d, _data, sizeof(Element)*_size);

            // Memory clean up
            delete _data;

            // Change pointer of data to d, which we created above.
            _data = d;
        }
        catch (const std::bad_alloc & e)
        {
            _capacity /= 2;
            std::cout << "Error increasing capacity: " << e.what() << '\n';
        }
    }
}

void Heap::heapifyUp()
{
    for (int i = _size - 1; 1;)
    {

    }
}

void Heap::heapifyDown()
{

}
