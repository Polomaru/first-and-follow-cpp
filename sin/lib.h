#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

vector<string> tokenize(string s, string del)
{
    vector<string> temp;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        temp.push_back( s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
        
    }
    temp.push_back( s.substr(start, end - start));
    return temp;
    
}
template <typename T>
ostream& operator<<(ostream& output, std::vector<T> const& values)
{   
    output<<"{ ";
    for (auto const& value : values)
    {
        if(value == values[values.size()-1])
        {
            output << value;
        }
        else{ output << value << " , "; }
        
    }
    output<<" }"<<endl;
    return output;
}
template <typename T>
ostream& operator<<(ostream& output, std::vector<vector<T>> const& valuess)
{
    output<<"{ "<<endl;
    for (auto const& values : valuess)
    {
        output<<"{ ";
        for (auto const& value : values)
        {
            if(value == values[values.size()-1])
            {
                output << value;
            }
            else{ output << value << " , "; }
        }
        output<<" }"<<endl;       
    }
    output<<"}"<<endl<<endl;
    return output;
}

template <typename T>
ostream& operator<<(ostream& output, std::unordered_map<T,vector<T>> const& u_m)
{
    output<<"{ "<<endl;
    for (const auto & v : u_m)
    {
        output<<"{ ";
        output<< v.first <<" : "<< v.second;
        output<<" }"<<endl;       
    }
    output<<"}"<<endl<<endl;
    return output;
}

bool contains(vector<string> v, string x)
{
    return (std::find(v.begin(), v.end(), x) != v.end()); 
}
