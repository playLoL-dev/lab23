#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstdio>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string f_name,vector<string>& s_name ,vector<int>& score,vector<char>& grade){
    ifstream file(f_name);
    string line;
    while(getline(file,line)){
        char format[999] = "%[^:]:%d %d %d";
        char name[999];
        int s1, s2, s3;
        sscanf(line.c_str(),format,name,&s1,&s2,&s3);
        int sum_score = s1 + s2 + s3;

        s_name.push_back(name);
        score.push_back(sum_score);
        grade.push_back(score2grade(sum_score));
    }
}

void getCommand(string &command,string &key){
    string text;
    char cmd[999], k[999] = "";
    cout << "Please input your command:\n";
    getline(cin,text);
    sscanf(text.c_str(),"%s %s",cmd,k);
    int pos = text.find(' ');
    command = text.substr(0, pos);
    key = text.substr(pos + 1);
}

void searchName(vector<string>& s_name ,vector<int>& score,vector<char>& grade,const string& key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i = 0;i < s_name.size();i++){
        if(key == toUpperStr(s_name[i])){
        cout << s_name[i] << "'s score = " << score[i] << "\n";
        cout << s_name[i] << "'s grade = " << grade[i] << "\n";
        found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }        
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &s_name, vector<int> &score, vector<char> &grade, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i = 0;i < grade.size();i++){
        if(key[0] == grade[i]){
        cout << s_name[i] << " (" << score[i] << ")" << "\n";
        found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}