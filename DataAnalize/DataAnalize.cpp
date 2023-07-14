#include <iostream>
#include <string>
#include <thread>
#include <chrono>


// из файлов сначала russian names затем foreigin names
// считать в свою програму все:
//  - имена, 
//  - количество носителй,
//  - и информацию о половой принадлежности имени

#include <fstream>
#include <sstream>
#include <vector>
namespace {
    struct Record {
        std::wstring name;
        bool sex;
        int peopleCount;
    };

    std::vector<Record> ReadDB() {
        std::vector<Record> result;
        std::wifstream inf("russian_names.csv");
        if (!inf.is_open()) {
            throw 1;
        }
        else {
            std::wstring tmp;
            std::getline(inf, tmp, L'\n');
            while (!inf.eof()) {
                Record temp{};
                std::getline(inf, tmp, L';');
                std::getline(inf, temp.name, L';');
                std::getline(inf, tmp, L';');
                temp.sex = (tmp == L"М")?true:false;
                std::getline(inf, tmp, L';');
                temp.peopleCount = std::stoi(tmp);
                std::getline(inf, tmp, L'\n');
                result.push_back(temp);
            }
        }
        inf.close();
        return std::move(result);
    }

}


int main()
{

    auto startPoint = std::chrono::high_resolution_clock().now();
    auto DB = ReadDB();
    auto endPoint = std::chrono::high_resolution_clock().now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endPoint - startPoint).count();
    std::cout << DB.size() <<" lines " << duration << " nanoseconds";
}