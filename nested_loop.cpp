#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
    vector<string> registerLabels = {"s1", "s2", "s3", "s4", "s5"};
    vector<uint32_t> countLines = {5, 4, 3, 2, 1};

    vector<string>::iterator j;
    vector<uint32_t>::iterator i;

    j = registerLabels.begin();
    map<uint32_t, string> mapRegisterLabelsWithCountLines;

    for ( i = countLines.begin(); i != countLines.end(); ++i) {
        int index = (i - countLines.begin());
        mapRegisterLabelsWithCountLines[*i] = j[index];
        cout << *i << " " << j[index] << endl;
    }

    for (auto x: mapRegisterLabelsWithCountLines) {
          cout << x.first << " : " << x.second << endl;
    }

    return 0;
}
