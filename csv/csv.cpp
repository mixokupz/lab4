#include "csv.h"
#include <iostream>
using namespace std;
string n_line(ifstream &file, unsigned int n, char shield, char delim) {
    string buf;
    //доходим до n-ой строки

    for (unsigned int i = 0; i <= n; i++) {
        //если конец файла
        if (!getline(file, buf, delim)) {
            throw(string("eof"));
        }
        string cont= buf;
        //случай экранирования
        while (buf.length() >= 2 && cont.back() == shield && cont[buf.length() - 2] != shield && getline(file, cont, delim)) {
            buf.back() = delim;
            buf += cont;
        }
    }
    // проверка на пустые строки
    if (buf.empty()) {
        return plus_plus_line(file, shield, delim);  // пропускаем пустые строки
    }
    return buf;
}
string plus_plus_line(ifstream &file, char shield, char delim) {
    string buf;
    if (!getline(file, buf, delim)) {
            throw(string("eof"));
        }
        string cont= buf;
        //случай экранирования
    while (buf.length() >= 2 && cont.back() == shield && cont[buf.length() - 2] != shield && getline(file, cont, delim)) {
        buf.back() = delim;
        buf += cont;
    }
    if (buf.empty()) {
        return plus_plus_line(file, shield, delim);  // Пропустить пустые строки
    }

     
    return buf;
}

vector<string> split(const string &str, char shield, char delim) {
    stringstream ss(str);
    string elem;
    vector<string> elems;
    while (getline(ss, elem, delim)) {
        if(!elem.empty()){
            elems.push_back(elem);
        }
        
    }
    //тоже случай с skibidi_dop_dop",йылйыл => skibidi_dop_dop,йылйыл
    for (unsigned int i = 0; i < elems.size() - 1; i++) {
        size_t eli_lth = elems[i].length();
        if (eli_lth >= 2 && elems[i].back() == shield && elems[i][eli_lth - 2] != shield) {
            elems[i].back() = delim;
            elems[i] += elems[i + 1];
            elems.erase(elems.begin() + i + 1);
        }
    }
    return elems;
}