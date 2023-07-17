#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdio>

// из файлов сначала russian names затем foreigin names
// считать в свою програму все:
//  - имена, 
//  - количество носителй,
//  - и информацию о половой принадлежности имени

#include <fstream>
#include <sstream>
#include <deque>
namespace {
    struct Record {
        std::wstring name;
        bool sex;
        int peopleCount;
    };

    std::deque<Record> ReadDB() {
        std::deque<Record> result;
        std::wifstream inf("russian_names.csv");
        //std::ofstream iof("", std::ios::in);
        //FILE file = fopen("", "r+");
        // варианты решения мене важны чем следование алгоритму

        if (!inf.is_open()) {
            throw 1;
        }
        else {
            std::wstring tmp;
            std::getline(inf, tmp, L'\n');
            //inf >> tmp;
            while (!inf.eof()) {
                Record temp{};

                std::getline(inf, tmp, L';');

                std::getline(inf, temp.name, L';');

                std::getline(inf, tmp, L';');
                temp.sex = (tmp == L"М")/*?true:false*/;

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
    //bool has0counted{true};
    //while (has0counted) {
    //    for (auto& el:DB) {
    //        if (el.peopleCount == 0) {
    //            DB.erase(el);
    //        }
    //    }
    //    has0counted = false;
    //}
}

// Даны файлы csv содержащие данные о статистике распространённости имён
// необходимо:
//  1. Считать данные об имени, поле, количестве носителей
//  2. Сообщить об общем количестве имён
//  3. Выкинуть из коллекции имена без ностителей
//  4. и далее это задачи статичтического рода
//  4.1 Вывести все имена начинающиеся на определённый слог
//  4.2 к предыдущей задаче добавить ограничение на 
//      указанный пользователем пол
//  4.3 Поиск имён с указанным количеством носителей(вывод 
//      как первого подходящего так и всех подходящих)
//  4.4 Поиск имён с нибильным и наименьшим количеством носителей
//  4.5 Удаление имён по заданному параметру одному из(имя, пол, 
//      количество носителей)
// 
// YAGNI you aren't gonna need it
// любое предположение по составу функций и требований
// программы которое не высказал сам заказчик мы не делаем 
// пока не уточним у заказчика
//

// 1 содать структуру Запись для хранения нужной информации
// 2 создать коллекцию(бинарное дерево) для хранния объектов структуры
// 3 открыть первый файл и считать из него данные в коллекцию
// 3.1 открыть файл росийских имён
// 3.2 считать и проигнорировать первую строку
// 3.3 Создать пустой временный объект типа Запись
// 3.4 Считать первое поле, и проигнорировать его значение
// 3.5 Считать значение поля имени и поместить его
//       во временный объект типа Запись
// 3.6 Считать значение поля Пол и поместить его
//       во временный объект типа Запись
// 3.7 Считать значение поля Соличество носителей и поместить его
//       во временный объект типа Запись
// 3.8 Считать оставшуюся часть значений в строке и проигнорировать их
// 3.9 Добавить структуру сформированную при чтении в коллекцию Записей
// 3.10 Если записи в файле не закончились перейти к пункту 3.3
// 3.11 Закрыйть файл росийских имён
// 4 открыть первый файл и считать из него данные в коллекцию
//