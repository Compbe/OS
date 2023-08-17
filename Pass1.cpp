#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class assembler
{
    map<string, pair<string, int>> mot;
    map<string, int> c;
    map<string, int> r;
    ifstream f;
    int lc;
    int sc;

   map <string,pair<int,int>> st;
    ofstream fout;


public:
    assembler()
    {
        lc = 0;
        sc=0;
        fout.open("target.txt",ios::out);
    }
    void IS(string la, string me, string op1, string op2)
    {
        if(me!="BC")
        {
            if(r.count(op1)!=0)
            {
                if(st.count(op2)!=0)
                {
                    st[op2]=make_pair(-1,-1);
                }
            }
        }
    }
    void AD (string la, string me, string op1, string op2)
    {
        if(me=="START")
        {
            if(op1 =="")
            {
                lc=0;
                fout<<"(AD,"<<mot[la].second<<")";

            }
            else{
                lc=stoi(op1);
                fout<<"(AD, "<<mot[la].second<<")"<<" (C,"<<lc<<")";
            }
        }
        else if(me=="EQU")
        {
            if(st.count(la)==0)
            {
                sc++;
                st[la]=st[op1];
            }
            else
            {
                st[la]=st[op1];
            }
        }
      
        
    }
    void read(string fname)
    {
        f.open(fname);
        string l, b;
        string la = "", me, op1, op2;
        while (!f.eof())
        {
            getline(f, l);
            l += " ";
            int i = 0;
            int wc = 1;
            while (l[i] != '\0')
            {
                while (l[i] != ' ')
                {
                    b += l[i];
                    i++;
                }

                if (wc == 1 && mot.count(b) == 0)
                {
                    la = b;
                }
                else if (((wc == 1 && la == "") || (wc == 2 && la != "")) && mot.count(b) != 0)
                {
                    me = b;
                }
                else if (((wc == 2 && la == "") || (wc == 3 && la != "")) && mot.count(b) == 0)
                {
                    op1 = b;
                }
                else if (((wc == 3 && la == "") || (wc == 4 && la != "")) && mot.count(b) == 0)
                {
                    op2 = b;
                }

                wc++;
                b = "";
                i++;
            }

            
            if(mot[me].first=="AD")
            {
                AD(la,me,op1,op2);
            }
            else if(mot[me].first=="IS")
            {
                IS(la,me,op1,op2);
            }
           
            la = me = op1 = op2 = "";
        }
        fout.close();
    }
    void display()
    {
        for(auto i:st)
        {
            cout<<i.first<<endl;
        }
    }
    void createmot()
    {

        string s[18] = {"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT", "START", "END", "ORIGIN", "EQU", "LTORG", "DC", "DS"};
        string cs[6] = {"LT", "LE", "EQ", "GT", "GE", "ANY"};
        string rs[4] = {"AREG", "BREG", "CREG", "DREG"};
        for (int i = 0; i < 11; i++)
        {
            mot[s[i]] = make_pair("IS", i);
        }
        for (int i = 11; i < 16; i++)
        {

            mot[s[i]] = make_pair("AD", i - 10);
        }
        for (int i = 16; i < 18; i++)
        {

            mot[s[i]] = make_pair("DS", i - 15);
        }
        for (int i = 0; i < 6; i++)
        {
            c[cs[i]] = i + 1;
        }

        for (int i = 0; i < 4; i++)
        {
            r[rs[i]] = i + 1;
        }
    }
};

int main()
{
    assembler s;
    string fname;
    s.createmot();
    cout << "Enter file name" << endl;
    cin >> fname;
    s.read(fname);
    s.display();

    return 0;
}