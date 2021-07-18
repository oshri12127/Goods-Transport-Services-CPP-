//
// Created by Oshri on 19/05/2019.
//

#ifndef HW2_EDGE_H
#define HW2_EDGE_H
#include <iostream>
using  namespace std;

class Edge {
public:
    Edge(int from, int to, int Weight);
    ~Edge();
    Edge(const Edge&);
    Edge& operator=(const Edge&);
    Edge(Edge&& rhs) = default;
    Edge& operator=(Edge&& rhs)= default;
    int getFrom() const;
    int getTo() const;
    float getWeight() const;
    void setWeight(float Weight);

private:
    int from;
    int to;
    float Weight;

};


#endif //HW2_EDGE_H
