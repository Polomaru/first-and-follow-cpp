#include "lib.h"

class Reader
{
    public:
    vector<string> NT;
    vector<string> T;
    unordered_map <string , string> u_mtemp;
    unordered_map<string,vector<vector<string>>> rules;
    vector<vector<string>> allrules;
    string del1 =" -> ";
    string del2 =" | ";
    Reader(string file)
    {
        
        ifstream Gfile("../grammars/"+file+".txt");
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
                    if (u_mtemp[j]=="" && j!="_e") 
                    {
                        u_mtemp[j]="T";
                        T.push_back(j);
                    }
                }
                allrules.push_back(vtemp1);                
                mtemp.push_back(vtemp1);
            }
            rules[temp1] = mtemp;
        }
        Gfile.close();  
    }

    unordered_map<string,vector<string>> first()
    {
        unordered_map<string,vector<string>> firsts;
        for(const auto & i : NT)
        {
            firsts[i] = {};
        }

        bool change = false;

        do
        {
            change = false;
            for(const auto & i : NT)
            {
                auto mtemp = rules[i]; // gets the rules vector of vector

                for(const auto & j : mtemp)
                {
                    
                    if(u_mtemp[j[0]]== "T" || j[0]=="_e")
                    {
                        if(!contains(firsts[i],j[0]))
                        {
                            firsts[i].push_back(j[0]);
                            change = true;
                        }
                        
                    }
                    else if (u_mtemp[j[0]]=="NT")
                    {
                        for(const auto & l : firsts[j[0]])
                        {
                            if(!contains(firsts[i],l)) 
                            {
                                if(l!="_e")
                                {
                                    firsts[i].push_back(l);
                                    change = true; 
                                }
                                else
                                {
                                    int cont = 1;
                                    bool flag2 = true;
                                    while (cont < j.size() && flag2)
                                    {
                                        if( u_mtemp[j[cont]]=="T")
                                        {
                                            if(!contains(firsts[i],j[cont]))
                                            {
                                                firsts[i].push_back(j[cont]);
                                                change = true; 
                                            }
                                            flag2 = false;
                                        }
                                        else if (u_mtemp[j[cont]]=="NT")
                                        {
                                            for(const auto & m : firsts[j[cont]])
                                            {
                                                if( m == "_e" && cont == j.size()-1)
                                                {
                                                    firsts[i].push_back(m);
                                                    change = true;
                                                }
                                                else if(!contains(firsts[i], m) && m != "_e")
                                                {
                                                    firsts[i].push_back(m);
                                                    change = true;
                                                } 
                                            }
                                            if(!contains(firsts[j[cont]], "_e")) flag2 = false;
                                        }
                                        cont++;
                                    }
                                }                                
                            }                            
                        }                                               
                    }
                }
            }
        }while(change);
        return firsts;
    }

    unordered_map<string,vector<string>> follow(unordered_map<string,vector<string>> first)
    {
        unordered_map<string,vector<string>> follows;
        for(const auto & i : NT)
        {
            follows[i] = {};
        }
        follows[NT[0]].push_back("$");
        
        bool change = false;
        do
        {
            change = false;
            for(const auto & i : NT)
            {
                for(const auto & h : NT)
                {
                    for(const auto & rule : rules[h])
                    {
                        for ( int cont = 0; cont < rule.size() ; cont++ )
                        {
                            if(rule[cont] == i) 
                            {
                                
                                if(cont == rule.size()-1)
                                {
                                    for(const auto & j : follows[h])
                                    {
                                        if(!(contains(follows[i], j)))
                                        {
                                            follows[i].push_back(j);
                                            change = true;
                                        }
                                    }
                                }
                                else 
                                {
                                    if(u_mtemp[rule[cont + 1]] == "T")
                                    {
                                        if(!(contains(follows[i], rule[cont + 1])))
                                        {
                                            follows[i].push_back(rule[cont + 1]);
                                            change = true;
                                        }
                                    }
                                    else if (u_mtemp[rule[cont + 1]] == "NT")
                                    {
                                        int cont1 = cont + 1; 
                                        while(cont1 <= rule.size())
                                        {
                                            if(cont1 == rule.size())
                                            {
                                                for(const auto & j : follows[h])
                                                {
                                                    if(!(contains(follows[i], j)))
                                                    {
                                                        follows[i].push_back(j);
                                                        change = true;
                                                    }
                                                }
                                                break;
                                            }
                                            if(u_mtemp[rule[cont1]] == "NT")
                                            {
                                                for(const auto & j : first[rule[cont1]])
                                                {
                                                    if(!(contains(follows[i], j)) && j!= "_e")
                                                    {
                                                        follows[i].push_back(j);
                                                        change = true;
                                                    }
                                                }
                                            
                                                if(!contains(first[rule[cont1]], "_e")) {break;}
                                                cont1++;
                                            }
                                            else if (u_mtemp[rule[cont1]] == "T")
                                            {
                                                if(!(contains(follows[i], rule[cont1])))
                                                {
                                                    follows[i].push_back(rule[cont1]);
                                                    change = true;
                                                }
                                                break;
                                            }
                                            
                                        }   
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }while(change);

    return follows;
    }
};