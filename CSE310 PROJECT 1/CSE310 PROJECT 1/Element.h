/*
    Author: Brandan Tyler Lasley
    Date: 2/19/2019
*/
#pragma once
class Element
{
public:
    Element() : key(0) {}
    Element(int _key) : key(_key) {}
    Element(const Element & e) { this->key = e.key; }

    void setKey(const int _key) { this->key = _key; }
    int  getKey() const { return key; }
private:
    int key;
};