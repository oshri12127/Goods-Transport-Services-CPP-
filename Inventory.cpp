//
// Created by Oshri on 20/05/2019.
//

#include "Inventory.h"

Inventory::Inventory(int box, const DateAndTime &DT) : box(box), DT(DT) {}

Inventory::~Inventory() {

}

Inventory::Inventory(const Inventory &I) : box(I.box), DT(I.DT) {
}

Inventory &Inventory::operator=(const Inventory &I) {
    if (this == &I)
        return (*this);
    this->box = I.box;
    this->DT = I.DT;
    return *this;
}

int Inventory::getBox() const {
    return box;
}

const DateAndTime &Inventory::getDT() const //get date and time
{
    return DT;
}

bool Inventory::operator==(const Inventory &rhs) const {
    return DT == rhs.DT;
}

void Inventory::setBox(int box) {
    Inventory::box = box;
}


