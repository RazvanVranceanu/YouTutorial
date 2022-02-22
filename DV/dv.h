//
// Created by Razvan Vranceanu on 22.03.2021.
//

#ifndef A45_RAZVANVRANCEANU21_DV_H
#define A45_RAZVANVRANCEANU21_DV_H

#include "../domain/tutorial.h"
#include <stdexcept>

typedef Tutorial TElem;
template <typename TElem>

class Dv{
private:
    TElem* elems;
    int size;
    int capacity;

public:
    explicit Dv(int capacity = 5);
    ~Dv();
    void resize_dv();
    int search(const TElem& element);
    void append(TElem element);
    void remove(const TElem& element);
    void update(const TElem& old_element, const TElem& new_element);
    TElem& operator[](int position);
    int size_dv();
    int capacity_dv();
};


template<typename TElem>
Dv<TElem>::Dv(int cap) {
    capacity = cap;
    size = 0;
    elems = new TElem[capacity];
}

template<typename TElem>
Dv<TElem>::~Dv() {
    delete[] elems;
}

template<typename TElem>
void Dv<TElem>::resize_dv() {

    auto* new_list = new TElem[capacity*2];
    for (int i = 0; i < size; i++)
        new_list[i] = elems[i];

    capacity *= 2;
    delete[] elems;
    elems = new_list;
}

template<typename TElem>
int Dv<TElem>::search(const TElem &element) {
    for (int i = 0; i < size; i++) {
        if (elems[i] == element)
            return i;
    }
    return -1;
}

template<typename TElem>
void Dv<TElem>::append(TElem element) {
    if (size == capacity)
        resize_dv();
    elems[size++] = element;
}

template<typename TElem>
void Dv<TElem>::remove(const TElem &element) {

    int position = search_element(element);
    if (position != -1) {
        for (int i = position; i < size - 1; ++i) {
            elems[i] = elems[i + 1];
        }
        --size;
    }
}

template<typename TElem>
void Dv<TElem>::update(const TElem &old_element, const TElem &new_element) {
    int position = search_element(old_element);
    if (position != -1) {
        elems[position] = new_element;
    }
}

template<typename TElem>
TElem &Dv<TElem>::operator[](int position) {
    if (position < 0 || position >= size)
        throw std::runtime_error("Invalid position");
    return elems[position];
}

template<typename TElem>
inline int Dv<TElem>::size_dv() {
    return size;
}

template<typename TElem>
inline int Dv<TElem>::capacity_dv() {
    return capacity;
}


#endif //A45_RAZVANVRANCEANU21_DV_H
