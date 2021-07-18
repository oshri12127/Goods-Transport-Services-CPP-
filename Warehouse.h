//
// Created by Oshri on 19/05/2019.
//

#ifndef HW2_WAREHOUSE_H
#define HW2_WAREHOUSE_H

#include <vector>
#include <algorithm>

#include "Inventory.h"

class Warehouse {
public:
    Warehouse(const string &Name);
    ~Warehouse();
    Warehouse(const Warehouse&);
    Warehouse& operator=(const Warehouse&);
    Warehouse(Warehouse&& rhs) : Name{move(rhs.Name)}, inventory{move(rhs.inventory)} { }
    Warehouse& operator=(Warehouse&& rhs){ Name = std::move(rhs.Name); inventory = std::move(rhs.inventory); return *this; }
    const vector<Inventory> &getInventoryVector() const;
    const string &getName() const;
    void addInventory(const Inventory &add);//add Inventory to Warehouse
    const Inventory& operator[](int i) const;
    void sortInventory();//sort Inventory According to date and time.
    int getInventory();//return num of all Inventory in Warehouse.
private:
    string Name;
    vector<Inventory>inventory;
};


#endif //HW2_WAREHOUSE_H
