//
// Created by Oshri on 19/05/2019.
//

#include "Edge.h"

Edge::Edge(int from, int to, int Weight) : from(from), to(to), Weight(Weight) {}

Edge::~Edge() {

}

Edge::Edge(const Edge &e) : from(e.from), to(e.to), Weight(e.Weight) {}

Edge &Edge::operator=(const Edge &e) {
    if (this == &e)
        return (*this);
    this->from = e.from;
    this->to = e.to;
    this->Weight = e.Weight;
    return *this;
}

int Edge::getFrom() const {
    return from;
}

int Edge::getTo() const {
    return to;
}

float Edge::getWeight() const {
    return Weight;
}

void Edge::setWeight(float Weight) {
    Edge::Weight = Weight;
}

