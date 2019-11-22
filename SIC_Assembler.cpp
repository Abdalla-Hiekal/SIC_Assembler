/******************************************************************************
Abdalla Mahmoud Hiekal
16101137

*******************************************************************************/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll location_counter[1000];
string label[1000], opcode[1000],data[1000],objcode[1000];
vector<string> vec;
ll stringToLL(string s)
{
    stringstream num(s);
    ll res;
    num >> std::hex >>res;
    return res;
}

vector<vector<string>> OPTAB (59);

void initialize()
{
	  OPTAB[0] = vector<string> {"FIX", "1", "C4"};
	  OPTAB[1] = vector<string> {"FLOAT", "1", "C0"};
	  OPTAB[2] = vector<string> {"HIO", "1", "F4"};
	  OPTAB[3] = vector<string>{"NORM", "1", "C8"};
	  OPTAB[4] = vector<string> {"SIO", "1", "F0"};
	  OPTAB[5] = vector<string> {"TIO", "1", "F8"};
	  OPTAB[6] = vector<string> {"ADDR", "2", "90"};
	  OPTAB[7] = vector<string> {"CLEAR", "2", "B4"};
	  OPTAB[8] = vector<string> {"COMPR", "2", "A0"};
	  OPTAB[9] = vector<string> {"DIVR", "2", "9C"};
	  OPTAB[10] = vector<string> {"MULR", "2", "98"};
	  OPTAB[11] = vector<string> {"RMO", "2", "AC"};
	  OPTAB[12] = vector<string> {"SHIFTL", "2", "A4"};
	  OPTAB[13] = vector<string> {"SHIFTR", "2", "A8"};
	  OPTAB[14] = vector<string> {"SUBR", "2", "94"};
	  OPTAB[15] = vector<string> {"SVC", "2", "B0"};
	  OPTAB[16] = vector<string> {"TIXR", "2", "B8"};
	  OPTAB[17] = vector<string> {"ADD", "3", "18"};
	  OPTAB[18] = vector<string> {"ADDF", "3", "58"};
	  OPTAB[19] = vector<string> {"AND", "3", "40"};
	  OPTAB[20] = vector<string> {"COMP", "3", "28"};
	  OPTAB[21] = vector<string> {"COMPF", "3", "88"};
	  OPTAB[22] = vector<string> {"DIV", "3", "24"};
	  OPTAB[23] = vector<string> {"DIVF", "3", "64"};
	  OPTAB[24] = vector<string> {"J", "3", "3C"};
	  OPTAB[25] = vector<string> {"JEQ", "3", "30"};
	  OPTAB[26] = vector<string> {"JGT", "3", "34"};
	  OPTAB[27] = vector<string> {"JLT", "3", "38"};
	  OPTAB[28] = vector<string> {"JSUB", "3", "48"};
	  OPTAB[29] = vector<string> {"LDA", "3", "00"};
	  OPTAB[30] = vector<string> {"LDB", "3", "68"};
	  OPTAB[31] = vector<string> {"LDCH", "3", "50"};
	  OPTAB[32] = vector<string> {"LDF", "3", "70"};
	  OPTAB[33] = vector<string> {"LDL", "3", "08"};
	  OPTAB[34] = vector<string> {"LDS", "3", "6C"};
	  OPTAB[35] = vector<string> {"LDT", "3", "74"};
	  OPTAB[36] = vector<string> {"LDX", "3", "04"};
	  OPTAB[37] = vector<string> {"LPS", "3", "D0"};
	  OPTAB[38] = vector<string> {"MUL", "3", "20"};
	  OPTAB[39] = vector<string> {"MULF", "3", "60"};
	  OPTAB[40] = vector<string> {"OR", "3", "44"};
	  OPTAB[41] = vector<string> {"RD", "3", "D8"};
	  OPTAB[42] = vector<string> {"RSUB", "3", "4C"};
	  OPTAB[43] = std::vector<string> {"SSK", "3", "EC"};
	  OPTAB[44] = std::vector<string> {"STA", "3", "0C"};
	  OPTAB[45] = std::vector<string> {"STB", "3", "78"};
	  OPTAB[46] = std::vector<string> {"STCH", "3", "54"};
	  OPTAB[47] = std::vector<string> {"STF", "3", "80"};
	  OPTAB[48] = std::vector<string> {"STI", "3", "D4"};
	  OPTAB[49] = std::vector<string> {"STL", "3", "14"};
	  OPTAB[50] = std::vector<string> {"STS", "3", "7C"};
	  OPTAB[51] = std::vector<string> {"STSW", "3", "E8"};
	  OPTAB[52] = std::vector<string> {"STT", "3", "84"};
	  OPTAB[53] = std::vector<string> {"STX", "3", "10"};
	  OPTAB[54] = std::vector<string> {"SUB", "3", "1C"};
	  OPTAB[55] = std::vector<string> {"SUBF", "3", "5C"};
	  OPTAB[56] = std::vector<string> {"TD", "3", "E0"};
	  OPTAB[57] = std::vector<string> {"TIX", "3", "2C"};
	  OPTAB[58] = std::vector<string> {"WD", "3", "DC"};
}

int main()
{
	initialize();
    int t=0;
    freopen("inSIC.txt","r",stdin);
    string s,temp;
    //store Assmbley code
    while(getline(cin,s))
    {
        vec.clear();
        int len = s.length();
        istringstream iss(s);
        copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(vec));

        if(vec.size() == 2)
        {
            opcode[t] = vec[0];
            data[t] = vec[1];
        }else if(vec.size() == 3)
        {
            label[t]  = vec[0];
            opcode[t] = vec[1];
            data[t] = vec[2];
        }
        t++;
    }
    // pass 1
    location_counter[0] = location_counter[1] = stringToLL(data[0]);
    for(int i =2; i<t; i++)
    {
        if(opcode[i-1] == "RESW")
        {
            ll v = stringToLL(data[i-1])*3;
            location_counter[i] = location_counter[i-1]+v;
        }else if(opcode[i-1] == "RESB")
        {
            ll v = stringToLL(data[i-1]);
            location_counter[i] = location_counter[i-1]+v;
        }else if(opcode[i-1] == "BYTE")
        {
            ll v;
            if(data[i-1][0] == 'X')
            v = ((stringToLL(data[i-1])+1)/2);
            else if(data[i-1][0] == 'C')
            v = stringToLL(data[i-1]);

            location_counter[i] = location_counter[i-1]+v;

        }else
        {
         location_counter[i] = location_counter[i-1]+3;
        }
    }
    // print Symbol table
    cout<<"........................ Symbol table ........................"<<endl;
    for(int i =0; i<t; i++)
    {
       if(label[i] != "")
       {
           cout<<label[i]<<"  "<< std::hex <<location_counter[i]<<endl;
       }
    }


    for(int i =1; i<t-1; i++)
    {
       if(opcode[i] == "RESW" || opcode[i] == "RESB")
       {
           continue;
       }
       if(opcode[i] == "WORD")
       {
       		//to Int
		    stringstream num(data[i]);
			ll rr;
			num   >>rr;
			// to hex
            stringstream ss;
            ss << hex << rr;
            string res( ss.str());
            objcode[i] = res;
       }else if(opcode[i] == "BYTE")
       {
            string res = s.substr(2,(data[i].size()-2));
            objcode[i] = res;
       }else
       {

            bool flag=0;
            string res="";
            string search=data[i];
            int pos = data[i].find(",");
            if(pos != string::npos)
            {
                search = data[i].substr(0,pos-1);
                flag=1;
            }

            string opp="";
            for(int k =0; k<59; k++)
            {
                if(opcode[i] == OPTAB[k][0])
                {
                    opp = OPTAB[k][2];
                }
            }

            res= opp;
            int j;
            ll temp;
            for(j=0; j<1000;j++)
            {
                if(data[i] == label[j])
                {
                	temp =location_counter[j];
                    break;
                }
            }

            if(flag) temp+=32000;
            stringstream stream;
            stream << std::hex << temp;
            string addx = stream.str();
            res = res+addx;
            objcode[i] = res;

       }
    }
    cout<<"........................ Table ........................"<<endl;
    for(int i =1; i<t-2; i++)
    {
           cout<< std::hex << location_counter[i]<<" ";
           cout<<label[i]<<"  "<<opcode[i]<<"  "<<data[i]<<"  "<<setfill ('0') <<setw(6) <<objcode[i]<<endl;
    }
    cout<<"........................ HTE Record ........................"<<endl;
    cout<<"H."<< setfill ('0') <<setw(6)<< location_counter[0]<<"."<< setfill ('0') << setw(6)<<location_counter[t-3]-location_counter[0]<<endl;

    vector<int> v;
    for(int i =1; i<t-3; i++)
    {
    	if(opcode[i] != "RESW" && opcode[i] != "RESB")
    	{
    		v.push_back(i);
    		if(v.size() == 10)
    		{
    			int vv = location_counter[v[9]+1] - location_counter[v[0]];
    			cout<<"T."<<setfill ('0') << setw(6)<< location_counter[v[0]] <<"." <<setfill ('0') << setw(2)<< vv;
    			for(int q =0; q<v.size(); q++)
    			{
    			cout<<"."<<setfill ('0') << setw(6)<< objcode[v[q]];
    			}
    			cout<<endl;
    			v.clear();
    		}
    	}
    }
	if(v.size() > 0)
	{
		int vv = location_counter[v[v.size()-1]+1] - location_counter[v[0]];
		cout<<"T."<<setfill ('0') << setw(6)<< location_counter[v[0]] <<"." <<setfill ('0') << setw(2)<< vv;
		for(int q =0; q<v.size(); q++)
		{
		cout<<"."<<setfill ('0') << setw(6)<< objcode[v[q]];
		}
	}
    cout<<endl;
    cout<<"E."<< setfill ('0') <<setw(6)<<location_counter[1]<<endl;
    return 0;
}
