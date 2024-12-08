#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string n_line(ifstream &file, unsigned int n, char shield, char delim);
string plus_plus_line(ifstream &file, char shield, char delim);
vector<string> split(const string &string, char shield, char delim);
