#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main ()
{
    vector<string> v;
    v.push_back("Hello, ");
    v.push_back("World!");
    for (auto i : v)
    {
        cout << i;
    }
    cout << endl;
    return 0;
}