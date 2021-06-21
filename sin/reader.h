#include "lib.h"

class Grammar
{
    public:
    vector<string> NT;
    vector<string> T;
    unordered_map <string , string> u_mtemp;
    unordered_map<string,vector<vector<string>>> rules;
    string del1 =" -> ";
    string del2 =" | ";
    string special = "$";
    Grammar(string file)
    {
        
        ifstream Gfile("../grammars/"+file+".txt");
        string temp1,temp2;
        int pos1,pos2;
        while(getline(Gfile,temp1))
        {
            pos1 = temp1.find(del1);
            string ft = temp1.substr(0,pos1);
            if(u_mtemp [ft] == "")
            {
                u_mtemp [ft] = "NT";
                NT.push_back(ft);
            }   
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
                rules[temp1].push_back(vtemp1);
            }
            // rules[temp1] = mtemp;
        }
        Gfile.close();  
    }

    unordered_map<string,vector<string>> first()
    {
        unordered_map<string,vector<string>> firsts;
        for(const auto & i : NT) // inicializo los no terminales
        {
            firsts[i] = {};
        }

        bool change = false;

        do
        {
            change = false;
            for(const auto & i : NT) // recorro los no terminales
            {
                auto mtemp = rules[i]; // obtengo las reglas de los no terminales vector of vector str

                for(const auto & j : mtemp) // recorro cada regla
                {
                    
                    if(u_mtemp[j[0]]== "T" || j[0]=="_e") // si el primero es un terminal o si solo es epsilon
                    {
                        if(!contains(firsts[i],j[0]))
                        {
                            firsts[i].push_back(j[0]); // si no esta en los first del no terminal i, lo añado.
                            change = true;
                        }
                        
                    }
                    else if (u_mtemp[j[0]]=="NT") // si el primero es un no terminal.
                    {
                        for(const auto & l : firsts[j[0]]) // recorro los primeros de ese no terminal
                        {
                            if(!contains(firsts[i],l))  // si es que no esta.
                            {
                                if(l!="_e")           // si es que no es epsilon, los añado.
                                {
                                    firsts[i].push_back(l);
                                    change = true; 
                                }
                                else                    // si es epsilon
                                {   
                                    int cont = 1;
                                    bool flag2 = true;
                                    if(j.size()==1) 
                                    { 
                                        if(!contains(firsts[i],"_e"))
                                        {
                                            firsts[i].push_back("_e");
                                            change = true; 
                                        }
                                    }
                                    while (cont < j.size() && flag2)  // recorro toda lo demas de la regla.
                                    {
                                        if( u_mtemp[j[cont]]=="T") // si es que el siguiente es terminal, y no esta en los primeros, lo añado  
                                        {
                                            if(!contains(firsts[i],j[cont]))
                                            {
                                                firsts[i].push_back(j[cont]);
                                                change = true; 
                                            }
                                            flag2 = false; //termina el while.
                                        }
                                        else if (u_mtemp[j[cont]]=="NT") // si es terminal.
                                        {
                                            for(const auto & m : firsts[j[cont]]) // recorro todos los primeros de este terminal.
                                            {
                                                if( m == "_e" && cont == j.size()-1) // 
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
        follows[NT[0]].push_back(special);
        
        bool change = true;
        do
        {
            change = false;
            for(const auto & i : NT) // recorre todos los terminales
            {
                for(const auto & h : NT) // tambien recorre todos los terminales
                {
                    for(const auto & rule : rules[h]) // recorre as reglas del no terminal h y busca alguna coincidencia de i.
                    {
                        for ( int cont = 0; cont < rule.size() ; cont++ ) // recorre toda la regla buscando alguna coincidencia de i.
                        {
                            if(rule[cont] == i)  // si es que la regla es igual al no terminal i.
                            {
                                
                                if(cont == rule.size()-1) // si es que es el ultimo en ese conjunto de una regla.
                                {
                                    for(const auto & j : follows[h]) // busca los siguientes de h.
                                    {
                                        if(!(contains(follows[i], j))) // si es que no estan en los siguientes de i
                                        {
                                            follows[i].push_back(j); // añadir
                                            change = true;
                                        }
                                    }
                                }
                                else // si es que no es el ultimo, ve si su siguiente es un terminal o no terminal
                                {
                                    if(u_mtemp[rule[cont + 1]] == "T") // si es terminal
                                    {
                                        if(!(contains(follows[i], rule[cont + 1]))) // lo añado y sigo.
                                        {
                                            follows[i].push_back(rule[cont + 1]);
                                            change = true;
                                        }
                                    }
                                    else if (u_mtemp[rule[cont + 1]] == "NT") // si es no terminal.
                                    {
                                        int cont1 = cont + 1; 
                                        bool flag = true;
                                        while(cont1 <= rule.size() && flag) //mientras recorro lo siguiente de la regla.
                                        {
                                            if(cont1 == rule.size()) //si me pase al ultimo
                                            {
                                                for(const auto & j : follows[h]) // añado los siguientes de h si es que no estan.
                                                {
                                                    if(!(contains(follows[i], j)))
                                                    {
                                                        follows[i].push_back(j);
                                                        change = true;
                                                    }
                                                }
                                                flag = false;
                                            }
                                            else if(u_mtemp[rule[cont1]] == "NT") // si es no terminal
                                            {
                                                for(const auto & j : first[rule[cont1]]) //añado sus primeros al siguiente de i.
                                                {
                                                    if(!(contains(follows[i], j)) && j!= "_e")
                                                    {
                                                        follows[i].push_back(j);
                                                        change = true;
                                                    }
                                                }
                                            
                                                if(!contains(first[rule[cont1]], "_e")) {flag = false;} //si es que no tiene epsilon, break
                                                cont1++;
                                            }
                                            else if (u_mtemp[rule[cont1]] == "T") //si es terminal.
                                            {
                                                if(!(contains(follows[i], rule[cont1]))) // lo añado.
                                                {
                                                    follows[i].push_back(rule[cont1]);
                                                    change = true;
                                                }
                                                flag = false;
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


    unordered_map<string,unordered_map<string,vector<string>>> table_ll1 ( unordered_map<string,vector<string>> firsts , unordered_map<string,vector<string>> follows)
    {
        unordered_map<string,unordered_map<string,vector<string>>> table_ll;
        unordered_map<string,vector<string>> u_mtemp1;
        for(const auto & j : T)
        {
            u_mtemp1[j] = {};   
        }
        for(const auto & i : NT)
        {
            table_ll[i] = u_mtemp1;
        }

        for(const auto & i : firsts) // recorro los primeros
        {   
            // cout<<(rules[i.first]);
            for(const auto & j : i.second) // recorro el vector de cada primero
            {
                for(const auto & h : rules [i.first]) // recorro cada regla para cada elemento de los primeros
                {
                    if(j == h[0])
                    {
                        table_ll[i.first][j] = h;
                    }
                    else if (u_mtemp[h[0]] == "NT")
                    {
                        table_ll[i.first][j] = h;
                    }
                    if(j == "_e")
                    {
                        for(const auto & k : follows[i.first])
                        {
                            table_ll[i.first][k] = {"_e"};
                        }
                    }
                }   
            }   
        }
        return table_ll;
    }
};