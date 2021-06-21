#include "reader.h"

int main()
{
    Grammar reader("13");

    // cout<<reader.NT;
    // cout<<reader.T<<endl;

    // for (auto x : reader.rules)
    //   cout << x.first << ": " << x.second ;

    auto f = reader.first();
    cout<<"first: ";
    cout<<endl;
    for(const auto &  i : reader.NT)
    {
      cout<< setw(8) << i << " : " <<f[i]<<endl;
    }

    cout<<endl;
    cout<<"second: ";
    cout<<endl;
    auto fo = reader.follow(f);

    for(const auto &  i : reader.NT)
    {
      cout<< setw(8)<< i << " : " <<fo[i]<<endl;
    }

    cout<<endl;
    cout<<"Table LL1: ";
    cout<<endl;

    auto table = reader.table_ll1(f,fo);

    reader.T.push_back(reader.special);
    for(const auto &  i : reader.NT)
    {
      cout<< i << " : " <<endl;
      for(const auto &  j : reader.T)
      {
        cout<<j<<" = ";
        cout<<table[i][j]<<" "<<endl;
      
      }cout<<endl;
    }
    reader.T.pop_back();
    return 0;
}