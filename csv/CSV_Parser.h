#include <fstream>
#include "csv.h"
#include "tuple.h"
#include <tuple>
#include <string>
#include <iostream>
using namespace std;

template <typename... Args>
class CsvParser {
    private:
        ifstream &p_file;
        unsigned int shift;
        char p_row_delim ='\n';
        char p_col_delim = ',';
        char p_shield = '"';

        class CsvIter {
            private:
                string i_buf;
                CsvParser &i_parser;
                unsigned int i_index;
                bool is_end; // достиг ли конца файла
            public:
                CsvIter(CsvParser &parser, const unsigned int &offset, bool end=false) : i_parser(parser), i_index(offset),is_end(end) {
                    if(!end){
                        try{
                            // получаем n-ю строку, которую указывают в maine (CsvParser<int, string> parser(file, 0);)
                            i_buf = n_line(i_parser.p_file, i_index, i_parser.p_shield, i_parser.p_row_delim);
                        }catch(...){
                            is_end = true; //достигли конца файла
                        }
                        
                    }
                }

                ~CsvIter()=default;

                CsvIter& operator++() {
                    if(!is_end){
                        this->i_index++;
                        //ленивое чтение, т.е. искоренил многократное чтение с 0-ой строки до n+1
                        //plus_plus_line проводит считывание новой строки, основываясь на "прошлом опыте"
                        try{
                            i_buf = plus_plus_line(i_parser.p_file, i_parser.p_shield, i_parser.p_row_delim);
                        }catch(...){
                            is_end=true;//достигли конца файла
                        }
                    }
                    return *this;
                }

                bool operator==(const CsvIter &iterator) {
                    return this->is_end == iterator.is_end;
                }

                bool operator!=(const CsvIter &iterator) {
                    return !(*this == iterator);
                }

                tuple<Args...> operator*() {
                    if (is_end) {
                        //если есть попытка получить строку вне файла
                        throw(string("operator*: is out of range"));
                    }else{
                        return i_parser.parse_line(i_buf);
                    }
                    
                }
        };

    public:
        CsvParser(ifstream &file, const unsigned int &offset) : p_file(file), shift(offset) {}

        ~CsvParser()=default;

        CsvIter begin() {
            return CsvIter(*this, shift,false);
        }
        CsvIter end() {
            //здесь передаем true - означает, что мы достигли последних данных в файле
            return CsvIter(*this, shift,true);
        }

        tuple<Args...> parse_line(string& line) {
            vector<string> items = split(line, p_shield, p_col_delim);
            tuple<Args...> t;
            if (sizeof...(Args) != items.size()) {
                throw("Line '" + line + "' has incorrect quantity of colums");
            }
            try {
                TupleAdder<0,sizeof...(Args)-1,tuple<Args...>,vector<string>>::add_to_tuple(t,items);
            }
            catch (const string &error) {
                throw("Line '" + line + "': " + error);
            }
            return t;
        }
};

