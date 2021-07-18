//
// Created by Oshri on 20/05/2019.
//

#ifndef HW2_INVENTORY_H
#define HW2_INVENTORY_H

#include "DateAndTime.h"

class Inventory {
public:
    Inventory(int box, const DateAndTime &DT);
    ~Inventory();
    Inventory(const Inventory&);
    Inventory& operator=(const Inventory&);
    Inventory(Inventory&& rhs) : box{move(rhs.box)}, DT{move(rhs.DT)} { }
    Inventory& operator=(Inventory&& rhs){ box = std::move(rhs.box); DT = std::move(rhs.DT); return *this; }
    int getBox() const;
    const DateAndTime &getDT() const;//get date and time
    bool operator==(const Inventory &rhs) const;
    void setBox(int box);

private:
    int box;
    DateAndTime DT;

};


#endif //HW2_INVENTORY_H
