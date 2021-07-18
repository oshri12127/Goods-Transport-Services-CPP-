//
// Created by Oshri on 19/05/2019.
//

#include "Warehouse.h"

Warehouse::Warehouse(const string &Name) : Name(Name) {
    Inventory newYear(0, DateAndTime(1, 1, 00, 00));
    inventory.push_back(newYear);
}

Warehouse::~Warehouse() {
}

Warehouse::Warehouse(const Warehouse &w) : Name(w.Name), inventory(w.inventory) {

}

Warehouse &Warehouse::operator=(const Warehouse &w) {
    if (this == &w)
        return (*this);
    this->Name = w.Name;
    this->inventory = w.inventory;
    return *this;
}

const string &Warehouse::getName() const {
    return Name;
}

void Warehouse::addInventory(const Inventory &add)//add Inventory to Warehouse
{
    for (unsigned i = 0; i < inventory.size(); ++i) {
        if (add.getDT() == inventory[i].getDT()) {
            inventory[i].setBox(inventory[i].getBox() + add.getBox());
            return;
        }

    }
    inventory.push_back(add);
}


const Inventory &Warehouse::operator[](int i) const {
    return inventory[i];
}

void Warehouse::sortInventory()//sort Inventory According to date and time.
{
    sort(inventory.begin(), inventory.end(),
         [](Inventory i, Inventory j) -> int { return (i.getDT() < j.getDT()); });
}

const vector<Inventory> &Warehouse::getInventoryVector() const {
    return inventory;
}

int Warehouse::getInventory() //return num of all Inventory in Warehouse.
{
    int sum = 0;
    for (unsigned i = 0; i < inventory.size(); ++i) {
        sum += inventory[i].getBox();
    }
    return sum;
}




