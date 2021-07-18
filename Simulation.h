//
// Created by Oshri on 19/05/2019.
//

#ifndef HW2_SIMULATION_H
#define HW2_SIMULATION_H

#include <fstream>
#include <exception>
#include <sstream>
#include <bits/stdc++.h>
#include <ctype.h>
#include <cctype>

#include"Warehouse.h"
#include "Edge.h"

class Simulation {
public:
    Simulation(vector<string> &allArgs);
    ~Simulation();
    Simulation(const Simulation&) = delete;//Unable to create a copy
    Simulation& operator=(const Simulation&) = delete;//Unable to create a copy
    Simulation(Simulation&& rhs) = delete;//Unable to move
    Simulation& operator=(Simulation&& rhs) = delete;//Unable to move
    void run();
private:
    vector<Warehouse> Warehouses;
    vector<Edge> GraphBox;
    vector<Edge> GraphShip;
    string NameOutFile;

    int SearchWarehouse(string Warehouse)const;//return index of Warehouse if Exists else return -1.
    int CalculateInMinutes(DateAndTime a,DateAndTime b)const;//Calculate the ship time in Minutes.
    void addToGraphBox(int from,int to,int w);
    void addToGraphShip(int from,int to,int w);
    int addToWarehouses(string W);
    int EdgeExists(int f,int t,vector<Edge>&Graph)const;//return index of edge in graph if Exists else return -1.
    void updateGraphBox(int index,int w);
    void updateGraphShip(int index,int w);
    void outbound(int indexWarehouse)const;
    void inbound(int indexWarehouse)const;
    void inventory(int indexWarehouse,DateAndTime DT)const;
    void shortest(int indexWarehouseFrom,int indexWarehouseTo);
    vector<float > dijkstra(int n, int source, vector<vector<pair<int,float > >>&G);//algorithm dijkstra to find shortest path.
    void print()const;
    void tokenize(string const &str,vector<std::string> &out,char delim = ',');//split the string to vector According delimiter.
    void Input(string file_name,bool IsMainInput);//Handles input
    void checkInput(string file_name,bool IsMainInput,vector<std::string> &lines);//verifying input.
    void updateInventoryWarehouse(int Warehouse,DateAndTime &in, int box);//add Inventory to Warehouse.
    DateAndTime createDateAndTime(string DT);//create object DateAndTime from string.
    void findAndReplaceAll(string & data, string toSearch,string replaceStr);//find and replace all occurrence in string.
    bool check_dateAtime(string DT);//verifying data and time format.
};


#endif //HW2_SIMULATION_H
