#include "reader.h"

int main()
{
    Reader reader("grammar.txt");

    cout<<reader.NT;
    cout<<reader.T<<endl;

    for (auto x : reader.rules)
      cout << x.first << ": " << x.second ;
    return 0;
}