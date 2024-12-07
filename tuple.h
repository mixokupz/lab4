#include <tuple>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

template <typename T>
typename enable_if<is_floating_point<T>::value, bool>::type righ_str(string &str) {
    int points = 0;

    for (auto w : str) {
        if (w == '.') {
            points++;
        }
        else if (w > '9' || w < '0') {
            return false;
        }
        if (points > 1) {
            return false;
        }
    }

    return true;
}
template <typename T>
typename enable_if<is_integral<T>::value, bool>::type righ_str(string &str) {
    for (auto w : str) {
        if (w > '9' || w < '0') {
            return false;
        }
    }
    return true;
}

template <typename T>
void str_conv(string &str, T &elem) {
    if (!righ_str<T>(str)) {
        throw(string("Can't convert '") + str + "'");
    }
    stringstream convert(str);
    convert >> elem;
}
void str_conv(string &str, string &elem) {
    elem = str;
}
template<typename Tuple, unsigned N, unsigned Size> 
class TuplePrinter {
    public:
        static void print(ostream& out, const Tuple& tuple) {
            out << get<N>(tuple) << " ";
            TuplePrinter<Tuple, N + 1, Size>::print(out, tuple);

        }
};

template<typename Tuple, unsigned N> 
class TuplePrinter<Tuple, N, N> {
    public:
        static void print(ostream& out, const Tuple& tuple) {
            out << get<N>(tuple) << " ";
        }
};

template<typename Tuple, unsigned N> 
class TuplePrinter<Tuple, N, 0> {
    public:
        static void print(ostream& out, const Tuple& tuple) {
        }
};

template<typename... Args> 
ostream & operator<<(ostream& out, const tuple<Args...>& arg) {
    TuplePrinter<tuple<Args...>, 0, sizeof...(Args) - 1>::print(out, arg);
    return out;
};
template<unsigned int I, unsigned int S,typename Tuple,typename Vec>
class TupleAdder{
    public:
        static void add_to_tuple(Tuple&t,Vec&v){
            str_conv(v[I],get<I>(t));
            TupleAdder<I+1,S,Tuple,Vec>::add_to_tuple(t,v);
        }

};
template<unsigned int I,typename Tuple,typename Vec> 
class TupleAdder<I,I,Tuple,Vec> {
    public:
        static void add_to_tuple(Tuple&t,Vec&v){
            str_conv(v[I],get<I>(t));
        }
};
template<unsigned int I,typename Tuple,typename Vec> 
class TupleAdder<I, 0,Tuple,Vec> {
    public:
        static void add_to_tuple(Tuple&t,Vec&v){
         
        }
};
