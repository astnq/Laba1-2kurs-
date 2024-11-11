#include "../include/includes.h"
#include "../include/array.h"
#include "../include/list.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/hashtable.h"
#include "../include/tree.h"

void printUsage( char* programName) {
    cerr << "Использование: " << programName << " --file <filename> --query 'command'" << endl;
}
string Futext(string& filenm, string& nameStruct) { // Функция сохранения фулл текста файла без нужной структуры
    string str, text;
    ifstream fin;
    fin.open(filenm);

    while (getline(fin, str)) { // Сохранение фулл текста в переменную
        stringstream ss(str);
        string tokens;
        getline(ss, tokens, ' ');
        if (tokens != nameStruct)
        {
            text += str + "\n";
        }
    }

    fin.close();
    return text;
}

void writefl(string& filenm, string& text) {
    ofstream fout(filenm);
    if (!fout.is_open()) {
        cout << " Ошибка открытия файла для записи " << endl;
        return;
    }
    fout << text;
    fout.close();
}

// Массив
Array hReadFile(string& filenm, string& nameStruct) {
    Array arr;
    string str;
    ifstream fine;
    fine.open(filenm);
    while (getline(fine, str)) {
        stringstream ss(str);
        string tokens;
        getline(ss, tokens, ' ');
        if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
            while (getline(ss, tokens, ' ')) {
                arr.addToEnd(tokens); // Добавляем элементы в массив
            }
        }
    }
    fine.close();
    return arr;
}

void MPUSH(string& data, string& filenm, string& value) {
    string futext = Futext(filenm, data);
    Array arr = hReadFile(filenm, data);

    string str;
    if (arr.getSize() != 0) {
        arr.addToEnd(value);
        str = data + ' ';
        for (size_t i = 0; i < arr.getSize(); ++i) {
            str += arr.getIndex(i) + ' ';
        }
        futext += str;
        writefl(filenm, futext);
    } else {
        str = data + ' ' + value;
        futext += str;
        writefl(filenm, futext);
    }
}

void MPUSHIND(string& name, string& value, size_t index, string& filenm) {
    string futext = Futext(filenm, name);
    Array arr = hReadFile(filenm, name);

    string str;
    if (arr.getSize() != 0 && index < arr.getSize()) {
        arr.add(index, value);
        str = name + ' ';
        for (int i = 0; i < arr.getSize(); ++i) {
            str += arr.getIndex(i) + ' ';
        }
        futext += str;
        writefl(filenm, futext);
    } else if (arr.getSize() == 0 && index == 0) {
        str = name + ' ' + value;
        futext += str;
        writefl(filenm, futext);
    } else {
        cout << " Ошибка, индекс выходит за размеры массива! " << endl;
        exit(1);
    }
}

void MREMOVE(string& name, size_t index, string& filenm) {
    string textfull = Futext(filenm, name);
    Array arr = hReadFile(filenm, name);
    if (index >= arr.getSize()) {
        cout << " Ошибка, индекс выходит за пределы массива! " << endl;
        return;
    }
    arr.remove(index);

    string str;
    str = name + ' ';
    for (size_t i = 0; i < arr.getSize(); ++i) {
        str += arr.getIndex(i) + ' ';
    }
    textfull += str;
    writefl(filenm, textfull);
}

void MREPLACE(string &name, string &value, size_t index, string &filenm) {
    string textfull = Futext(filenm, name);
    Array arr = hReadFile(filenm, name);
    if (index >= arr.getSize()) {
        cout << " Ошибка, индекс выходит за предела массива! " << endl;
        return;
    }
    arr.replace(index, value);

    string str;
    str = name + ' ';
    if (arr.getSize() != 0 && index < arr.getSize()) {
        for (size_t i = 0; i < arr.getSize(); ++i) {
            str += arr.getIndex(i) + ' ';
        }
        textfull += str;
        writefl(filenm, textfull);
    }
}

void MGET(string &data, size_t &index, string &filenm)
{
    Array arr = hReadFile(filenm, data);

    if (arr.getSize() != 0 && index < arr.getSize()) {
        cout << arr.getIndex(index) << endl;
    } else {
        throw out_of_range("Ошибка: Нет такого массива или индекс выходи за его размеры ");
    }
}

void MSIZE(string &name, string &filenm) {
    Array arr = hReadFile(filenm, name);

    if (arr.getSize() != 0) {
        cout << arr.getSize() << endl;
    } else {
        throw out_of_range(" Ошибка. Нет такого массива или он пуст ");
    }
}

void MPRINT(string &name, string &filenm) {
    Array arr = hReadFile(filenm, name);

    if (arr.getSize() != 0) {
        arr.ShowArray();
    } else {
        throw out_of_range(" Ошибка. Нет такого массива или он пуст ");
    }
}

void aMenu(string &command, string &filenm) {
    string name, value;
    size_t index;

    if (command.substr(0, 6) == "MPUSH ") {
        string cons = command.substr(6);
        stringstream stream(cons);
        stream >> name >> value;
        MPUSH(name, filenm, value);
    } else if (command.substr(0, 9) == "MPUSHIND ") {
        stringstream stream(command.substr(9));
        stream >> name >> value >> index;
        MPUSHIND(name, value, index, filenm);
    } else if (command.substr(0, 8) == "MREMOVE ") {
        string cons(command.substr(8));
        stringstream stream(cons);
        stream >> name >> index;
        MREMOVE(name, index, filenm);
    } else if (command.substr(0, 9) == "MREPLACE ") {
        string cons(command.substr(9));
        stringstream stream(cons);
        stream >> name >> value >> index;
        MREPLACE(name, value, index, filenm);
    } else if (command.substr(0, 5) == "MGET ") {
        string cons(command.substr(5));
        stringstream stream(cons);
        stream >> name >> index;
        MGET(name, index, filenm);
    } else if (command.substr(0, 6) == "MSIZE ") {
        string cons(command.substr(6));
        stringstream stream(cons);
        stream >> name;
        MSIZE(name, filenm);
    } else if (command.substr(0, 7) == "MPRINT ") {
        string cons(command.substr(7));
        stringstream stream(cons);
        stream >> name;
        MPRINT(name, filenm);
    } else {
        throw out_of_range(" Ошибка. Нет такой команды ");
    }
}

// Список
SinglyLinkedList alReadyFile(string &filenm, string &nameStruct) {
    SinglyLinkedList data;
    string str;
    ifstream fin;
    fin.open(filenm);

    while (getline(fin, str)) {
        stringstream ss(str);
        string tokens;
        getline(ss, tokens, ' ');
        if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
            while (getline(ss, tokens, ' ')) {
                data.pushBack(tokens); // Добавляем элементы в массив
            }
        }
    }
    fin.close();
    return data;
}

void LPUSH(string &name, string &value, string filenm, string check) {
    string textfull = Futext(filenm, name);
    SinglyLinkedList data = alReadyFile(filenm, name);

    if (!data.isEmpty()) {
        (check == "back") ? data.pushBack(value) : data.pushFront(value);
        string str = name + ' ';
        Node* current = data.getHead(); // Значение текущего элемента
        while (current) {
            str += current->data + ' ';
            current = current->next;
        }
        textfull += str;
        writefl(filenm, textfull);
        } else {
        string str = name + ' ' + value;
        writefl(filenm, str); // перезаписываем новый элемент
    }
}

void LPOP(string &name, string &filenm, string check) {
    SinglyLinkedList data = alReadyFile(filenm, name);
    string textfull = Futext(filenm, name);

    if (!data.isEmpty()) {
        (check == "back") ? data.popBack() : data.popFront();
        string str = name + ' ';
        Node *current = data.getHead(); // Значение текущего элемента
        while (current) {
            str += current->data + ' ';
            current = current->next;
        }
        textfull += str;
        writefl(filenm, textfull);
    } else {
        throw out_of_range(" Ошибка. Нет такого списка или он пуст ");
    }
}

void LREMOVE(string &name, string &value, string &filenm) {
    string textfull = Futext(filenm, name);
    SinglyLinkedList data = alReadyFile(filenm, name);

    if (!data.isEmpty()) {
        data.removeAt(value); // Удаляем элемент
        string str = name + ' ';
        Node* current = data.getHead(); // Значение текущего элемента
        while (current) {
            str += current->data + ' ';
            current = current->next;
        }
        textfull += str;
        writefl(filenm, textfull);
    } else {
        throw out_of_range(" Ошибка. Нет такого списка или он пуст ");
    }
}

void LGET(string &name, string &value, string &filename) {
    SinglyLinkedList data = alReadyFile(filename, name);

    if (!data.isEmpty()) {
        int index = data.find(value); // Используем метод find
        if (index == -1) {
            throw out_of_range(" Нет такого значения в списке ");
        } else {
            cout << " Индекс значения: " << index << endl;
        }
    } else {
        throw out_of_range(" Ошибка. Нет такого списка ");
    }
}

void LPRINT(string &name, string &filename) {
    SinglyLinkedList data = alReadyFile(filename, name);

    if (!data.isEmpty()) {
        data.print();
    } else {
        throw out_of_range(" Ошибка. Нет такого списка или он пуст ");
    }
}

void lMenu(string &command, string filenm) {
    string name, value;

    if (command.substr(0, 6) == "LPUSH ") {
        string cons = command.substr(6);
        stringstream stream(cons);
        stream >> name >> value;
        LPUSH(name, value, filenm, "back");
    } else if (command.substr(0, 6) == "LPUSH ") {
        string cons = command.substr(6);
        stringstream stream(cons);
        stream >> name >> value;
        LPUSH(name, value, filenm, "front");
    } else if (command.substr(0, 5) == "LPOP ") {
        string cons = command.substr(5);
        stringstream stream(cons);
        stream >> name;
        LPOP(name, filenm, "back");
    } else if (command.substr(0, 5) == "LPOPF ") {
        string cons = command.substr(5);
        stringstream stream(cons);
        stream >> name;
        LPOP(name, filenm, "front");
    } else if (command.substr(0, 8) == "LREMOVE ") {
        string cons = command.substr(8);
        stringstream stream(cons);
        stream >> name >> value;
        LREMOVE(name, value, filenm);
    } else if (command.substr(0, 5) == "LGET ") {
        string cons = command.substr(5);
        stringstream stream(cons);
        stream >> name >> value;
        LGET(name, value, filenm);
    } else if (command.substr(0, 7) == "LPRINT ") {
        string cons = command.substr(7);
        stringstream stream(cons);
        stream >> name;
        LPRINT(name, filenm);
    } else {
        throw out_of_range("Ошибка. Нет такой команды");
    }
}

// Очередь
void zReadFile(string &filenm, string &nameStruct, Queue &data) {
    string str;
    ifstream fin;
    fin.open(filenm);
    while (getline(fin, str)) {
        stringstream ss(str);
        string tokens;
        getline(ss, tokens, ' ');
        if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
            while (getline(ss, tokens, ' ')) {
                data.push(tokens); // Добавляем элементы в очередь
            }
        }
    }
    fin.close();
}

void QPUSH(string &name, string &value, string &filenm) {
    string textfull = Futext(filenm, name);
    Queue data(30);
    zReadFile(filenm, name, data);

    string str;
    if (data.Size() != 0) {
        data.push(value);
        str = name + ' ';
        while (data.Size() != 0) {
            str += data.peek() + ' ';
            data.pop();
        }
        textfull += str;
        writefl(filenm, textfull);
    } else {
        str = name + ' ' + value;
        textfull += str;
        writefl(filenm, textfull);
    }
}

void QPOP(string &name, string &filenm) {
    string textfull = Futext(filenm, name);
    Queue data(30);
    zReadFile(filenm, name, data);

    string str;
    if (data.Size() != 0) {
        data.pop();
        str = name + ' ';
        while (data.Size() != 0) {
            str += data.peek() + ' ';
            data.pop();
        }
        textfull += str;
        writefl(filenm, textfull);
    } else {
        cout << " Ошибка. Нет такой очереди или она пуста " << endl;
        exit(1);
    }
}

void QPRINT(string &name, string &filenm) {
    Queue data(30);
    zReadFile(filenm, name, data);

    if (data.isEmpty()) {
        throw out_of_range(" Нет такой очереди или она пуста ");
    }

    
    while (!data.isEmpty()) {
        cout << data.peek() << " ";
        data.pop();
    }
    cout << endl;
}

void qMenu(string &command, string &filenm) {
    string name, value;

    if (command.substr(0, 6) == "QPUSH ") {
        string cons = command.substr(6);
        stringstream stream(cons);
        stream >> name >> value;
        QPUSH(name, value, filenm);
    } else if (command.substr(0, 5) == "QPOP ") {
        string cons = command.substr(5);
        stringstream stream(cons);
        stream >> name;
        QPOP(name, filenm);
    } else if (command.substr(0, 7) == "QPRINT ") {
        string cons = command.substr(7);
        stringstream stream(cons);
        stream >> name;
        QPRINT(name, filenm);
    } else {
        throw out_of_range("Ошибка. Нет такой команды");
    }
}

void sReadFile(string &filenm, string &nameStruct, Stack &data) {
    Stack doubly(30);
    string str;
    ifstream fin;
    fin.open(filenm);

    while (getline(fin, str)) {
        stringstream ss(str);
        string tokens;
        getline(ss, tokens, ' ');
        if (tokens == nameStruct) { // Проверяем на совпадение с нужной структурой
            while (getline(ss, tokens, ' ')) {
                doubly.push(tokens);
            } 
            while (doubly.size() != 0) {
                data.push(doubly.peek());
                doubly.pop();
            }
        }
    }
    fin.close();
}

void SPUSH(string &name, string &value, string &filenm) {
    string textfull = Futext(filenm, name);
    Stack data(30);                // Создаем стек
    sReadFile(filenm, name, data); // Передаем стек в функцию

    string str;
    if (data.size() != 0) {
        data.push(value);
        str = name + ' ';
        while (data.size() != 0) {
                str += data.peek() + ' ';
                data.pop();
            }
        textfull += str;
        writefl(filenm, textfull);
    } else {
        str = name + ' ' + value;
        textfull += str;
        writefl(filenm, textfull);
    }
}

void SPOP(string &name, string &filenm) {
    string textfull = Futext(filenm, name);
    Stack data(30);
    sReadFile(filenm, name, data); // Исправлено имя функции

    string str;
    if (data.size() != 0) {
        data.pop();
        str = name + ' ';
        while (data.size() != 0) {
            str += data.peek() + ' ';
            data.pop();
        }
        textfull += str;
        writefl(filenm, textfull);
    } else {
        cout << " Ошибка. Нет такого стека или он пуст " << endl;
        exit(1);
    }
}

void SPRINT(string &name, string &filenm) {
    Stack data(30);
    sReadFile(filenm, name, data); // Исправлено имя функции

    if (!data.isEmpty()) {
        while (!data.isEmpty()) {
            cout << data.peek() << " ";
            data.pop();
        }
        cout << endl;
    } else {
        throw out_of_range(" Ошибка. Нет такого стека или он пуст");
    }
}

void sMenu(string &command, string &filenm) { // Функция обработки команд стека
    string name, value;

    if (command.substr(0, 6) == "SPUSH ") {
        string cons = command.substr(6);
        stringstream stream(cons);
        stream >> name >> value;
        SPUSH(name, value, filenm);
    } else if (command.substr(0, 5) == "SPOP ") {
        stringstream stream(command.substr(5));
        stream >> name;
        SPOP(name, filenm);
    } else if (command.substr(0, 7) == "SPRINT ") {
        string cons = command.substr(7);
        stringstream stream(cons);
        stream >> name;
        SPRINT(name, filenm);
    } else {
        throw out_of_range(" Ошибка. Нет такой команды ");
    }
}

// Хеш-таблицы
Hash_table fReadFile(string &filenm, string &name) { // ф-ия чтения Хеш-таблицы из файла
    Hash_table nums;
    string str;
    ifstream fin;
    fin.open(filenm);
    while (getline(fin, str)) {
        stringstream ss(str);
        string token;
        getline(ss, token, ' ');
        if (token == name) {
            while (getline(ss, token, ' ')) {
                int position = token.find_first_of(':');
                token.replace(position, 1, " ");
                stringstream iss(token);
                string key, value;
                iss >> key >> value;
                nums.insert(key, value);
            }
        }
    }
    fin.close();
    return nums;
}

string printHashTable(Hash_table &ht, string name) { // Функция для перебора всех элементов хеш-таблицы
    string str = name + ' ';
    for (int i = 0; i < SIZE; ++i) {
        Hinfo* current = ht.table[i];
        while (current) {
            str += current->key + ':' + current->value + ' ';
            current = current->next;
        }
    }
    return str;
}

void HPUSH(string &name, string &key, string &value, string &filenm) {
    string textfull = Futext(filenm,name);
    Hash_table nums = fReadFile(filenm, name);

    string str;
    if(nums.sizetable != 0) {
        nums.insert(key, value);
    str = printHashTable(nums, name);
    textfull += str;
    writefl(filenm, textfull);
  } else {
    str = name + ' ' + key + ':' + value;
    textfull += str;
    writefl(filenm, textfull);
    }
}

void HPOP(string name, string &key, string &filenm) {
    string textfull = Futext(filenm, name);
    Hash_table nums = fReadFile(filenm, name);

    string str;
    if (nums.sizetable != 0) {
        if (nums.remove(key)) {
            str = printHashTable(nums, name);
            textfull += str;
            writefl(filenm, textfull);
        } else {
            throw out_of_range(" Ошибка. Нет такого ключа ");
        }
    } else {
        throw out_of_range(" Ошибка. Нет такой таблицы или она пуста ");
    }
}

    void HGET(string & name, string & key, string & filenm) {
        Hash_table data = fReadFile(filenm, name);

        string str;
        if (data.sizetable != 0) {
            string value;
            if (!data.get(key, value)) {
                throw out_of_range(" Ошибка. Нет такого ключа ");
            }
        } else {
            throw out_of_range(" Ошибка. Нет такой таблицы или она пуста ");
        }
    }

    void hMenu(string & command, string & filenm) { // ф-ия обработки команд Хеш-таблицы
        string name, key, value;

        if (command.substr(0, 6) == "HPUSH ") {
            string cons = command.substr(6);
            stringstream stream(cons);
            stream >> name >> key >> value;
            HPUSH(name, key, value, filenm);
        } else if (command.substr(0, 5) == "HPOP ") {
            string cons = command.substr(5);
            stringstream stream(cons);
            stream >> name >> key;
            HPOP(name, key, filenm);
        } else if (command.substr(0, 5) == "HGET ") {
            string cons = command.substr(5);
            stringstream stream(cons);
            stream >> name >> key;
            HGET(name, key, filenm);
        } else {
            throw out_of_range("Ошибка, нет такой команды");
        }
    }

// Дерево
    CompleteBinaryTree tReadFile(string& filenm, string& name) {
         CompleteBinaryTree data;
         string str;
         ifstream fin;
         fin.open(filenm);

         while(getline(fin, str)) {
            stringstream ss(str);
            string token;
            getline(ss, token, ' ');
            if(token == name) {
                while(getline(ss, token, ' ')) {
                    data.insert(stoi(token));
                }
            }
         }
         fin.close();
         return data;
    }
    
    void TPUSH(string& name, int& value, string& filenm) {
         string textfull = Futext(filenm, name);
         CompleteBinaryTree data = tReadFile(filenm, name);
         string str;

         if(data.size != 0) {
            data.insert(value);
            str = name + ' ' + data.toString();
            textfull += str;
            writefl(filenm,textfull);
       } else {
        str = name + ' ' + to_string(value);
        textfull += str;
        writefl(filenm, textfull);
       }
    }

    void TSEARCH(string& name, int value, string& filenm) {
        CompleteBinaryTree  nums = tReadFile(filenm, name);
        if(nums.size != 0) {
            cout << (nums.search(nums.root, value) ? " True " : " False ") << endl;
        } else { 
            throw out_of_range(" Ошибка. Нет такого дерева или оно пустое ");
        }
    }
    
    void TCHECK(string& name, string& filename) {
        CompleteBinaryTree nums = tReadFile(filename, name);
        if(nums.size != 0) {
        if(nums.isComplete()) cout << "True" << endl;
        else if(!nums.isComplete()) cout << " False" << endl;
        } else {
            throw out_of_range(" Ошибка. Нет такого дерева или оно пустое ");
        }
    }

    void TPRINT(string& name, string& filenm) {
        CompleteBinaryTree nums = tReadFile(filenm, name);
        if(nums.size != 0) {
            nums.print();
        } else {
            throw out_of_range(" Ошибка. Нет такого дерева или оно пустое");
        }
    }

    void tMenu(string& command, string& filenm) {
        string name;
        int value;

        if (command.substr(0, 6) == "TPUSH ") {
    string cons = command.substr(6);
    stringstream stream(cons);
    stream >> name >> value;
    TPUSH(name, value, filenm); 
  } else if (command.substr(0, 8) == "TSEARCH ") {
    string cons = command.substr(8);
    stringstream stream(cons);
    stream >> name >> value;
    TSEARCH(name, value, filenm);
  } else if (command.substr(0, 7) == "TCHECK ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name;
    TCHECK(name, filenm);
  } else if (command.substr(0, 7) == "TPRINT ") {
    string cons = command.substr(7);
    stringstream stream(cons);
    stream >> name;
    TPRINT(name, filenm);
  } else {
    throw out_of_range("Ошибка. Нет такой команды"); 
  }
}

 int main(int argc, char* argv[]) {
    if(argc != 5) {
        printUsage(argv[0]);
        return 1;
    }

    string filename; // Разбор аргументов командной строки
    string query;

    for(int i = 1; i < argc; i++) {
        if(string(argv[i]) == "--file") {
            if(++i < argc) {
                filename = argv[i];
            } else {
                printUsage(argv[0]);
                return 1;
            }
        } else if(string(argv[i]) == "--query") {
            if(++i < argc) {
                query = argv[i];
            } else {
                printUsage(argv[0]);
                return 1;
            }
        }
    }
    if(query.empty()) { // Обработка команды
    cout << " Ошибка. Должна указана быть команда. "  << endl;
    return 1;
    }

    switch(query[0]) {
        case 'M':
          aMenu(query, filename); //Массив
          break;
        case 'L':
          lMenu(query, filename); //Список
          break;
        case 'S':
          sMenu(query, filename); //Стек
          break;
        case 'Q':
          qMenu(query, filename); //Очередь
          break;
        case 'H':
          hMenu(query, filename); //Хеш-таблица
          break;
        case 'T':
          tMenu(query, filename); //Дерево
          break;
        default:
          cout << " Ошибка. Неизвестная структура данных. " << endl;
          return 1;
    }
    return 0;
 }

