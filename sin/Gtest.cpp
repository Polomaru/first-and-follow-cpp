#include "reader.h"

int main()
{
    Reader reader("8");

    // cout<<reader.NT;
    // cout<<reader.T<<endl;

    // for (auto x : reader.rules)
    //   cout << x.first << ": " << x.second ;

    auto f = reader.first();
    cout<<"first: ";
    cout<<endl;
    for(const auto &  i : reader.NT)
    {
      cout<< i << " : " <<f[i];
    }
    cout<<endl;
    cout<<"second: ";
     cout<<endl;
    auto fo = reader.follow(f);
    for(const auto &  i : reader.NT)
    {
      cout<< i << " : " <<fo[i];
    }
    return 0;
}