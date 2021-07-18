//
// Created by Oshri on 19/05/2019.
//

#include "Simulation.h"

Simulation::Simulation(vector<string> &allArgs) {
    int flag = 0;
    for (unsigned i = 1; i < allArgs.size(); ++i) {
        if (allArgs[i] == "[-p]" || allArgs[i] == "-p") {
            NameOutFile = allArgs[i + 1];
            flag = 1;
            i++;
            continue;
        }
        if (allArgs[i] == "-f" || allArgs[i] == "[" || allArgs[i] == "]")
            continue;
        Input(allArgs[i], true);
    }
    if (flag == 0)
        NameOutFile = "output.dat";
}

Simulation::~Simulation() {

}

void Simulation::run() {
    vector<string> inputVec;
    string input;
    getline(cin, input);
    tokenize(input, inputVec);
    while (inputVec[0] != "exit") {
        try {
            int flagInput = 0;
            if (inputVec.size() == 2 && inputVec[0] == "open") {
                Input(inputVec[1], false);
                flagInput = 1;
            }
            if (inputVec.size() == 2 && inputVec[1] == "outbound") {
                int numOfWH = SearchWarehouse(inputVec[0]);
                if (numOfWH != -1) {
                    outbound(numOfWH);
                    flagInput = 1;
                } else {
                    string error;
                    error = inputVec[0] + " does not exist in the database.";
                    throw invalid_argument(error);
                }
            }

            if (inputVec.size() == 2 && inputVec[1] == "inbound") {
                int numOfWH = SearchWarehouse(inputVec[0]);
                if (numOfWH != -1) {
                    inbound(numOfWH);
                    flagInput = 1;
                } else {
                    string error;
                    error = inputVec[0] + " does not exist in the database.";
                    throw invalid_argument(error);
                }
            }
            if (inputVec.size() == 3 && inputVec[1] == "inventory") {
                int numOfWH = SearchWarehouse(inputVec[0]);
                if ((numOfWH != -1) && (check_dateAtime(inputVec[2]) == false)) {
                    inventory(numOfWH, createDateAndTime(inputVec[2]));
                    flagInput = 1;
                }
                if (numOfWH == -1) {
                    string error;
                    error = inputVec[0] + " does not exist in the database.";
                    throw invalid_argument(error);
                }
            }
            if (inputVec.size() == 3 && inputVec[2] == "shortest") {
                int numOfWHfrom = SearchWarehouse(inputVec[0]);
                int numOfWHto = SearchWarehouse(inputVec[1]);
                if (numOfWHfrom != -1 && numOfWHto != -1) {
                    shortest(numOfWHfrom, numOfWHto);
                    flagInput = 1;
                } else {
                    string error;
                    error = inputVec[0] + " or " + inputVec[1] + " does not exist in the database.";
                    throw invalid_argument(error);
                }
            }
            if (inputVec.size() == 1 && inputVec[0] == "print") {
                print();
                flagInput = 1;
            }
            if (flagInput == 0) {
                string error;
                error = "USAGE:  'open',<file> *or*\n"
                        "<node>,'outbound'/'inbound' *or*\n"
                        "<node>,'inventory',dd/mm HH:mm *or*\n"
                        "<node>,<node>,'shortest' *or*\n"
                        "'exit' *to terminate*";
                throw invalid_argument(error);
            }
        }
        catch (const invalid_argument &e) {
            cerr << e.what() << endl;
        }
        getline(cin, input);
        inputVec.clear();
        tokenize(input, inputVec);
    }
}

void Simulation::tokenize(std::string const &str, vector<string> &out,
                          char delim)//split the string to vector According delimiter.
{
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim))
    {
        if(s[s.size()-1]==13)//ascii of '/n'
            s.pop_back();
        out.push_back(s);
    }
}

int Simulation::SearchWarehouse(string Warehouse) const//return index of Warehouse if Exists else return -1.
{
    for (unsigned i = 0; i < Warehouses.size(); ++i) {
        if (Warehouse == Warehouses[i].getName())
            return i;
    }
    return -1;
}

int Simulation::CalculateInMinutes(DateAndTime a, DateAndTime b) const//Calculate the ship time in Minutes.
{
    int long_month;
    if (a.getMonth() == 2)
        long_month = 28;
    if (a.getMonth() == 4 || a.getMonth() == 6 || a.getMonth() == 9 || a.getMonth() == 11)
        long_month = 30;
    if (a.getMonth() == 1 || a.getMonth() == 3 || a.getMonth() == 5 || a.getMonth() == 7 || a.getMonth() == 8 ||
        a.getMonth() == 10 || a.getMonth() == 12)
        long_month = 31;

    int month = (b.getMonth() - a.getMonth()) * (long_month);
    int day = ((b.getDay() + month) - a.getDay()) * (24);
    int min_a = a.getHour() * 60 + a.getMin();
    int min_b = (b.getHour() + day) * 60 + b.getMin();

    return min_b - min_a;
}

void Simulation::addToGraphBox(int from, int to, int w) {
    int indexEdge = EdgeExists(from, to, GraphBox);
    if (indexEdge == -1) {
        Edge temp(from, to, w);
        GraphBox.push_back(temp);
    } else {
        updateGraphBox(indexEdge, w);
    }
}

void Simulation::addToGraphShip(int from, int to, int w) {
    int indexEdge = EdgeExists(from, to, GraphShip);
    if (indexEdge == -1) {
        Edge temp(from, to, w);
        GraphShip.push_back(temp);
    } else {
        updateGraphShip(indexEdge, w);
    }
}

int Simulation::addToWarehouses(string W) {
    if (SearchWarehouse(W) == -1) {
        Warehouse temp(W);
        Warehouses.push_back(temp);
    }
    return SearchWarehouse(W);
}

int
Simulation::EdgeExists(int f, int t, vector<Edge> &Graph) const//return index of edge in graph if Exists else return -1.
{
    for (unsigned i = 0; i < Graph.size(); ++i) {
        if (f == Graph[i].getFrom() && t == Graph[i].getTo())
            return i;
    }
    return -1;
}

void Simulation::updateGraphBox(int index, int w) {
    GraphBox[index].setWeight(GraphBox[index].getWeight() + w);
}

void Simulation::updateGraphShip(int index, int w) {
    GraphShip[index].setWeight((GraphShip[index].getWeight() + w) / (2));
}

void Simulation::outbound(int indexWarehouse) const {
    int flag = 0;
    for (unsigned i = 0; i < GraphShip.size(); ++i) {
        if (GraphShip[i].getFrom() == indexWarehouse) {
            flag = 1;
            cout << Warehouses[GraphShip[i].getTo()].getName() << "," << GraphShip[i].getWeight() << endl;
        }
    }
    if (flag == 0)
        cout << Warehouses[indexWarehouse].getName() << ": no outbound nodes" << endl;
}

void Simulation::inbound(int indexWarehouse) const {
    int flag = 0;
    for (unsigned i = 0; i < GraphShip.size(); ++i) {
        if (GraphShip[i].getTo() == indexWarehouse) {
            flag = 1;
            cout << Warehouses[GraphShip[i].getFrom()].getName() << "," << GraphShip[i].getWeight() << endl;
        }
    }
    if (flag == 0)
        cout << Warehouses[indexWarehouse].getName() << ": no outbound nodes" << endl;
}

void Simulation::inventory(int indexWarehouse, DateAndTime DT) const {

    unsigned i = 0;
    int sumInventory = 0;
    for (i = 0; i < Warehouses[indexWarehouse].getInventoryVector().size(); ++i) {
        if (DT >= Warehouses[indexWarehouse][i].getDT()) {
            sumInventory += Warehouses[indexWarehouse][i].getBox();
            continue;
        }
        if (DT < Warehouses[indexWarehouse][i].getDT()) {
            cout << sumInventory << endl;
            return;
        }
    }
    cout << sumInventory << endl;
}

void Simulation::Input(string file_name, bool IsMainInput)//Handles input
{
    try {
        vector<string> lines;
        checkInput(file_name, IsMainInput, lines);
        vector<string> splitLine;

        tokenize(lines[0], splitLine);
        int mainWaIndex = addToWarehouses(splitLine[0]);
        DateAndTime mainOut = createDateAndTime(splitLine[1]);

        int sum_box = 0;
        DateAndTime out = mainOut;
        int wb = mainWaIndex;
        for (unsigned i = 1; i < lines.size(); ++i) {
            splitLine.clear();
            tokenize(lines[i], splitLine);
            int WaIndex = addToWarehouses(splitLine[0]);
            DateAndTime in = createDateAndTime(splitLine[1]);
            int box = stoi(splitLine[2]);
            sum_box += box;
            updateInventoryWarehouse(WaIndex, in, box);
            Warehouses[WaIndex].sortInventory();
            addToGraphShip(wb, WaIndex, CalculateInMinutes(out, in));
            addToGraphBox(mainWaIndex, WaIndex, box);
            out = createDateAndTime(splitLine[3]);
            wb = WaIndex;
        }
        updateInventoryWarehouse(mainWaIndex, mainOut, -sum_box);
        Warehouses[mainWaIndex].sortInventory();
        if (IsMainInput == false)cout << "Update was successful" << endl;
    }
    catch (const domain_error &d) {
        if (IsMainInput == false) { cerr << d.what() << endl; }
        else {
            cerr << "Invalid input in file " << file_name << " at line " << d.what() << "." << endl;
            exit(1);
        }
    }
    catch (const invalid_argument &e) {
        if (IsMainInput == false) { cerr << "Invalid input at line " << e.what() << "." << endl; }
        if (IsMainInput == true) {
            cerr << "Invalid input in file " << file_name << " at line " << e.what() << "." << endl;
            exit(1);
        }
    }
}

void Simulation::checkInput(string file_name, bool IsMainInput, vector<std::string> &lines)//verifying input.
{
    ifstream input_file1(file_name);
    if (!input_file1) {
        string error;
        if (IsMainInput == true) { error = "0"; }
        else { error = "ERROR openinig/reading the specifed file"; }
        throw domain_error(error);
    }
    vector<string> split_line;
    string line;
    string error;
    int count_line = 1;
    DateAndTime out(01, 01, 00, 00);
    while (getline(input_file1, line)) {
        split_line.clear();
        tokenize(line, split_line);
        if (count_line == 1) {
            if (split_line.size() != 2) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            if (check_dateAtime(split_line[1])) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            out = createDateAndTime(split_line[1]);
        } else {
            if (split_line.size() != 4) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            if (!(std::all_of(split_line[2].begin(), split_line[2].end(),
                              [](unsigned char c) { return std::isdigit(c); }))) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            if (stoi(split_line[2]) < 0 || (stod(split_line[2]) - stoi(split_line[2])) != 0) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            if (check_dateAtime(split_line[1]) || check_dateAtime(split_line[3])) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            if (createDateAndTime(split_line[1]) >= createDateAndTime(split_line[3])) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            if (out >= createDateAndTime(split_line[1])) {
                error = to_string(count_line);
                throw invalid_argument(error);
            }
            out = createDateAndTime(split_line[3]);
        }
        if ((split_line[0].size() > 16 || split_line[0].size() < 1) ||
            !(std::all_of(split_line[0].begin(), split_line[0].end(),
                          [](unsigned char c) { return (std::isalpha(c)) || (std::isspace(c)); })) ||
            (split_line[0].size() == 1 && split_line[0] == " ")) {

            error = to_string(count_line);
            throw invalid_argument(error);
        }
        lines.push_back(line);
        count_line++;
    }
    input_file1.close();
}

void Simulation::updateInventoryWarehouse(int Warehouse, DateAndTime &in, int box)//add Inventory to Warehouse.
{
    Inventory temp(box, in);
    Warehouses[Warehouse].addInventory(temp);
}

DateAndTime Simulation::createDateAndTime(string DT)//create object DateAndTime from string.
{
    int day;
    int month;
    int hour;
    int min;
    findAndReplaceAll(DT, "/", " ");
    findAndReplaceAll(DT, ":", " ");
    stringstream ss(DT);
    ss >> day >> month >> hour >> min;
    DateAndTime temp(day, month, hour, min);
    return temp;
}

void Simulation::findAndReplaceAll(string &data, string toSearch,
                                   string replaceStr) //find and replace all occurrence in string.
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
// Repeat till end is reached
    while (pos != string::npos) {
// Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
// Get the next occurrence from the current position
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

void Simulation::print() const {
    ofstream myfile(NameOutFile);
    myfile << "Graph Boxes:" << endl;
    for (unsigned i = 0; i < GraphBox.size(); ++i) {
        myfile << Warehouses[GraphBox[i].getFrom()].getName() + "-->" + Warehouses[GraphBox[i].getTo()].getName() +
                  ",box:" << GraphBox[i].getWeight() << endl;
    }
    myfile << endl;
    myfile << "Graph Shipping:" << endl;
    for (unsigned i = 0; i < GraphShip.size(); ++i) {
        myfile << Warehouses[GraphShip[i].getFrom()].getName() + "-->" + Warehouses[GraphShip[i].getTo()].getName() +
                  ",Shipping time:" << GraphShip[i].getWeight() << endl;
    }
    myfile.close();
}

void Simulation::shortest(int indexWarehouseFrom, int indexWarehouseTo) {
    vector<vector<pair<int, float> >> G;
    G.resize(Warehouses.size());
    for (unsigned i = 0; i < GraphShip.size(); ++i) {
        G[GraphShip[i].getFrom()].push_back(make_pair(GraphShip[i].getTo(), GraphShip[i].getWeight()));
    }
    vector<float> ans;
    ans = dijkstra(Warehouses.size(), indexWarehouseFrom, G);
    if (ans[indexWarehouseTo] == (int) 1e9)
        cout << "route unavailable" << endl;
    else {
        cout << Warehouses[indexWarehouseFrom].getName() + "-->" + Warehouses[indexWarehouseTo].getName() << endl;
        cout << ans[indexWarehouseTo] + abs(Warehouses[indexWarehouseFrom].getInventory()) << endl;
    }
}

vector<float>
Simulation::dijkstra(int n, int source, vector<vector<pair<int, float> >> &G)//algorithm dijkstra to find shortest path.
{
    int INF = (int) 1e9;
    vector<float> D(n, INF);
    D[source] = 0;
    set<pair<int, float> > Q;
    Q.insert({0, source});
    while (!Q.empty()) {
        auto top = Q.begin();
        int u = top->second;
        Q.erase(top);
        for (auto next: G[u]) {
            int v = next.first;
            float weight = next.second +
                           (abs(Warehouses[v].getInventory()));
            if (D[u] + weight < D[v]) {
                if (Q.find({D[v], v}) != Q.end())
                    Q.erase(Q.find({D[v], v}));
                D[v] = D[u] + weight;
                Q.insert({D[v], v});
            }
        }
    }
    return D;
}

bool Simulation::check_dateAtime(string DT)//verifying data and time format.
{
    vector<string> split;
    tokenize(DT, split, ' ');
    if (split.size() != 2)
        return true;
    size_t date = std::count(split[0].begin(), split[0].end(), '/');
    size_t time = std::count(split[1].begin(), split[1].end(), ':');
    if (date != 1 || time != 1)
        return true;
    if ((split[0].size() != 5) || (!(std::all_of(split[0].begin(), split[0].end(),
                                                 [](unsigned char c) { return (std::isdigit(c)) || (c == '/'); }))))
        return true;
    if ((split[1].size() != 5) || (!(std::all_of(split[1].begin(), split[1].end(),
                                                 [](unsigned char c) { return (std::isdigit(c)) || (c == ':'); }))))
        return true;
    int day;
    int month;
    int hour;
    int min;
    findAndReplaceAll(DT, "/", " ");
    findAndReplaceAll(DT, ":", " ");
    stringstream ss(DT);
    ss >> day >> month >> hour >> min;
    if (month < 1 || month > 12)
        return true;
    if ((month == 2) && (day < 1 || day > 28))
        return true;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && (day < 1 || day > 30))
        return true;
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) &&
        (day < 1 || day > 31))
        return true;
    if (hour < 0 || hour > 23)
        return true;
    if (min < 0 || min > 59)
        return true;
    return false;
}