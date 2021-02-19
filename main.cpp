#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Prepare(std::string& data)
{
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c){ return std::tolower(c); }); //converting to lower case

    while (!std::isalpha(data.back()))
            data.pop_back();
}

int main(int argc, char const *argv[])
{
    int k = 0;

    std::ifstream file("map_text.txt");
    std::map <std::string, int> m;
    std::vector<std::pair<std::string, int>> vec;

    if (file.is_open())
    {
        std::string word;
        while (!file.eof())
        {
            file >> word;
            Prepare(word);
            m[word]++;
            k++;
        }
        file.close();
    }

    for (auto pair : m) {
        vec.push_back(pair);
    }

    std::sort(vec.begin(), vec.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) { return a.second > b.second; });
    for (auto pair : vec){
        std::cout << "Word: " << pair.first << ", ";
        std::cout << "Count: " << pair.second << "." << std::endl;
    }

    return 0;
}