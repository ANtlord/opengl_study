#include <fstream>
#include <cassert>
#include <string>
#include <map>
#include <tuple>
#include <vector>

using std::map;
using std::tuple;
using std::ifstream;
using std::string;
using std::vector;

vector<string> split(const string &value, char delimeter)
{
    vector<string> result;

    string::size_type oldPos = 0;
    string::size_type newPos = 0;

    int i = 0;
    bool flag = true;
    while ((newPos = value.find(delimeter, oldPos)) != string::npos) {
        result.push_back( value.substr(oldPos, (newPos - oldPos)) );
        oldPos = newPos+1;
    }
    result.push_back( value.substr(oldPos, (value.size() - oldPos)) );
    return result;
}

class OptionReader
{
public:
    static OptionReader * getSingleton()
    {
        if (_self == nullptr)
            _self = new OptionReader();
        return _self;
    }

    map<string, string> &getOptions()
    {
        return this->_options;
    }
private:
    map<string, string> _options;
    OptionReader()
    {
        ifstream file("config.txt");
        if (file.good()) {
            string sbuffer;
            vector<string> vbuffer;
            while(getline(file, sbuffer)) {
                vbuffer = split(sbuffer, ' ');
                assert(vbuffer.size() == 2);
                _options[vbuffer[0]] = vbuffer[1];
            }
        }
        
    }
    virtual ~OptionReader()
    {
    }
    static OptionReader * _self;
};
