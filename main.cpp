//
//  main.cpp
//  Graph
//
//  Created by Сергей Пиденко on 03.05.2022.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

vector<vector<int>> Read_graph(const string& name_file, vector<pair<int, int>>& list_edges, vector<int>& Edges_cnt)

{
    ifstream fin;
    fin.open(name_file);
    vector<vector<int>> Graph_;
    int Vertex_, Edges_;
    vector<pair<int, int>> pairs;
    list_edges.clear();
    Edges_cnt.clear();
    if (fin.is_open())
    {
        fin >> Vertex_ >> Edges_;
        vector <int> v(Vertex_, 0);
        Graph_.resize(Vertex_, v);
        auto zero = make_pair(0, 0);
        pairs.resize(Graph_.size(), zero);
        for (int k = 0; k < Edges_; k++)
        {
            int start, end;
            fin >> start >> end;
            auto p1 = make_pair(start, end);
            list_edges.push_back(p1);
            Graph_[start][end] = 1;
            Graph_[end][start] = 1;
            pairs[start].first += 1;
            pairs[end].first += 1;
            pairs[start].second = start;
            pairs[end].second = end;
        }
    
    }
    else
    {
        cout << "file not read" << endl;
    }
    sort(pairs.begin(), pairs.end());
    for(int i = pairs.size()-1;i >= 0; i--)
    {
        Edges_cnt.push_back(pairs[i].second);
    }
    return Graph_;
}

vector<int> solve(vector<vector<int>>& Graph_, const vector<int>& edges_counter) {
    vector<int> vColors(Graph_.size(), -1);
    for(auto iter : edges_counter) {
        int i = iter;
        vector<bool> colored(Graph_.size(), false);
        for (int j = 0; j < Graph_.size(); j++) {
            if (Graph_[i][j] == 1) {
                if(vColors[j] > -1){
                    colored[vColors[j]] = true;
                }
            }
        }
        for (int k = 0; k < Graph_.size(); k++)
        {
            if (!colored[k])
            {
                vColors[i] = k;
                break;
            }
        }
    }
    return vColors;
}

int main ()
{
    
    string path = "/Users/Sergej/data1";
    auto it = fs::directory_iterator(path);
    vector<fs::path> array_path;
    copy_if(fs::begin(it), fs::end(it), std::back_inserter(array_path),
        [](const auto& entry)
            {
            return fs::is_regular_file(entry);
    });
    

    
    for (auto & p : array_path)
    {
        vector<int> Edges_cnt;
        vector<pair<int, int>> Edges_;
        vector<vector<int>> Graph_ = Read_graph(p.string(), Edges_, Edges_cnt);
        vector<int> colored2 = solve(Graph_, Edges_cnt);
        int max = -1;
        for (int i = 0; i < colored2.size(); i++)
        {
            if (colored2[i] > max)
            {
                max = colored2[i];
            }
        }
        cout << p.string() << " " << max + 1 << endl;
       
        cout << endl;
        for (auto i : Edges_)
        {
            if (colored2[i.first] == colored2[i.second])
            {
                cout << "Error, colored Test: " << p.string() << endl;
                cout << i.first << " " << i.second << endl;
                break;
            }
        }
    }
    return 0;
}
