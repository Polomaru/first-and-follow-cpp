#include "lib.h"

class Reader
{
    public:
    vector<string> NT;
    vector<string> T;
    unordered_map<string,vector<vector<string>>> rules;
    string del1 =" -> ";
    string del2 =" | ";
    Reader(string file) 
    {
        unordered_map <string , string> u_mtemp;
        ifstream Gfile(file);
        string temp1,temp2;
        int pos1,pos2;
        while(getline(Gfile,temp1))
        {
            pos1 = temp1.find(del1);
            string ft = temp1.substr(0,pos1);
            u_mtemp [ft] = "NT";
            NT.push_back(ft);
        }
        Gfile.clear();
        Gfile.seekg(0,ios::beg);
        
        while(getline(Gfile,temp2))
        {
            vector<vector<string>> mtemp  = {};
            vector<string> vtemp = {}, vtemp1 = {};
            pos1 = temp2.find(del1);
            pos2 = temp2.find(del1);
            temp1 = temp2.substr(0,pos1);
            temp2 = temp2.substr(pos2 + del1.length());
            vtemp = tokenize (temp2, del2);
            // cout<<vtemp;
            for(auto &i : vtemp)
            {
                vtemp1 = tokenize(i," ");
                for(auto &j : vtemp1)
                {
                    if (u_mtemp[j]=="") 
                    {
                        u_mtemp[j]="T";
                        T.push_back(j);
                    }
                }                
                mtemp.push_back(vtemp1);
            }
            rules[temp1] = mtemp;
        }
        Gfile.close();  
    }

};