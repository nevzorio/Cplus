#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

int chis(int a){
    int ans = 0;
    while (a != 0){
        ans++;
        a /= 10;
    }
    return ans;
}

class Node{
public:
    Node *next;
    string name;
    string short_name;
    double mass;
    int energ;
    Node (string name = "", string short_name = "", double mass = 0.0, int energ = 0, Node *next = nullptr){
        this->next = next;
        this->name = name;
        this->short_name = short_name;
        this->mass = mass;
        this->energ = energ;

    }
};

class List{
private:
    Node *head;
    int size;
    Node* find(string short_name, string name);
public:
    List();
    ~List();
    void print_list();
    void push(string name = "", string short_name = "", double mass = 0.0, int energ = 0);
    void find(string short_name = "");
    void pop(string short_name = "");
    void print_max();
    void save(string name = "");
    void load(string text = "");
    void clear();
};

List::List(){
    head = nullptr;
    size = 0;
}

List::~List(){
    clear();
}

void List::clear(){
    size = 0;
    if(head != nullptr){
        Node *cur = head;
        while (head != nullptr){
            head = head->next;
            delete cur;
            cur = head;
        }
    }
}

void List::print_max(){
    if(head == nullptr){
        cout << "Список пуст" << endl;
        return;
    }
    Node *cur = head;
    while(true){
        cout << cur->name << " " << cur->short_name << " " << cur->energ << " " << cur->mass << endl;
        if(cur->next == nullptr){
            break;
        }
        if(cur->mass > cur->next->mass){
            break;
        }
        cur = cur->next;
    }
}

Node* List::find(string short_name, string name){
    Node *cur = head;
    while (cur != nullptr && cur->short_name != short_name && cur->name != name){
        cur = cur->next;
    }
    return cur;
}

void List::find(string short_name){
    Node *cur = find(short_name, "");
    if(cur == nullptr){
        cout << "Такого элемента не:(" << endl;
        return;
    }
    cout << cur->name << " " << cur->short_name << " " << cur->energ << " " << cur->mass << endl;
}

void List::push(string name, string short_name, double mass, int energ){
    if (find(short_name, name) != nullptr){
        cout << "Элемент с таким названием или символическим значением существует"  <<  endl;
        return;
    }
    Node *new_elements;
    new_elements = new Node(name, short_name, mass, energ, nullptr);
    if (head == nullptr){
        head = new_elements;
        size++;
        return;
    }
    Node *cur = head;
    Node *last = nullptr;
    while(cur != nullptr && cur->mass > mass){
        last = cur;
        cur = cur->next;
    }
    if(last == nullptr){
        new_elements->next = head;
        head = new_elements;
        return;
    }
    new_elements->next = cur;
    last->next = new_elements;
    size++;
}

void List::print_list(){
    int max_name = 8;
    int max_shart = 25;
    int max_energ = 5;
    Node* cur = head;
    while(cur != nullptr){
        max_name = max(max_name, int(cur->name.size()));
        max_shart = max(max_shart, int(cur->short_name.size()));
        max_energ = max(max_energ, chis(cur->energ));
        cur = cur->next;
    }
    cout << "Название";
    for(int i = 8; i <= max_name; i++){
        cout << " ";
    }
    cout << "символическое обозначение";
    for(int i = 25; i <= max_shart; i++){
        cout << " ";
    }
    cout << "Заряд";
    for(int i = 5; i <= max_energ; i++){
        cout << " ";
    }
    cout << "Масса" << endl;
    cur = head;
    while(cur != nullptr){
        cout << cur->name;
        for(int i = int(cur->name.size()); i <= max_name; i++){
            cout << " ";
        }
        cout << cur->short_name;
        for(int i = int(cur->short_name.size()); i <= max_shart; i++){
            cout << " ";
        }
        cout << cur->energ;
        for(int i = chis(cur->energ); i <= max_energ; i++){
            cout << " ";
        }
        cout << cur->mass << endl;
        cur = cur->next;
    }
}

void List::pop(string short_name){
    Node *last = nullptr;
    Node *cur = head;
    while(cur != nullptr && cur->short_name != short_name){
        last= cur;
        cur = cur->next;
    }
    if(cur == nullptr){
        cout << "Такого элемента нет, как и смасла твоей жизни!" << endl;
        return;
    }
    if(last == nullptr){
        head = cur->next;
        size--;
        delete cur;
        return;
    }
    last->next = cur->next;
    delete cur;
    size--;
}

void List::save(string name){
    ofstream fout;
    fout.open(name);
    if(!fout.is_open()){
        cout << "Файл не отрыт, как и твой талант" << endl;
        return;
    }
    fout << size << endl;
    Node *cur = head;
    while(cur != nullptr){
        fout << cur->name << " " << cur->short_name << " " << cur->energ << " " << cur->mass << endl;
        cur = cur->next;
    }
    fout.close();
}

void List::load(string text){
    ifstream fin;
    fin.open(text);
    if(!fin.is_open()){
        cout << "Файл не открыт, и не нужно тебе этого" << endl;
        return;
    }
    clear();
    int p;
    fin >> p;
    string name, short_name;
    int energ;
    double mass;
    string e;
    for (int i = 0; i < p; i++){
        fin >> name >> short_name >> energ >> mass;
        push(name, short_name, mass, energ);
    }
    fin.close();
}

void print_menu(){
    cout << "1.Вывод списка" << endl;
    cout << "2.Добавить элемент" << endl;
    cout << "3.Удалить элемент по символическому обозначению" << endl;
    cout << "4.Вывести сведения об элементе по его символическому значению" << endl;
    cout << "5.Найти элемент с самой большой массой" << endl;
    cout << "6.Сохранить" << endl;
    cout << "7.Загрузить" << endl;
    cout << "8.Выход" << endl;
}

int main(int argc, const char * argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    List A;
    string s;
    string name, short_name, mass_string, energi_string, text;
    int energ;
    double mass;
    while (true){
        print_menu();
        cin >> s;
        if(s == "1"){
            A.print_list();
        } else
            if(s == "2"){
                cout << "Имя, не твое, а элемента:";
                cin >> name;
                cout << "Символическое обозначение:";
                cin >> short_name;
                cout << "Заряд ядра(Цифра):";
                cin >> energi_string;
                cout << "Масса атома(Цифра, не отрицательная):";
                cin >> mass_string;
                try{
                    energ = stoi(energi_string);
                    mass = atof(mass_string.c_str());
                    if(mass > 0){
                        A.push(name, short_name, mass, energ);
                    } else {
                        cout << "Ты что делаешь? Масса не может быть отрицательной" << endl;
                    }
                }
                catch(...){
                    cout << "Ты что-то не то ввел, только теперь смотри что печатаешь" << endl;
                }
            } else
                if(s == "3"){
                    cout << "Символическое обозначение:";
                    cin >> short_name;
                    A.pop(short_name);
                } else
                    if(s == "4"){
                        cout << "Символическое обозначение:";
                        cin >> short_name;
                        A.find(short_name);
                    } else
                        if(s == "5"){
                            A.print_max();
                        } else
                            if(s == "6"){
                                cout << "Введите имя файла с .txt:";
                                cin >> text;
                                if(text.size() >= 5){
                                    if(text[text.size() - 1] == 't' && text[text.size() - 2] == 'x' &&text[text.size() - 3] == 't' &&text[text.size() - 4] == '.'){
                                        A.save(text);
                                    } else {
                                        cout << "Нет .txt, ну ты и бандит" << endl;
                                    }
                                } else {
                                    cout << "Ты что-то не то ввел кибуцуджи мудзан" << endl;
                                }
                            } else
                                if(s == "7"){
                                    cout << "Введите имя файла с .txt:";
                                    cin >> text;
                                    if(text.size() >= 5){
                                        if(text[text.size() - 1] == 't' && text[text.size() - 2] == 'x' &&text[text.size() - 3] == 't' &&text[text.size() - 4] == '.'){
                                            A.load(text);
                                        } else {
                                            cout << "Нет .txt, ну ты и бандит" << endl;
                                        }
                                    } else {
                                        cout << "Ты что-то не то ввел кибуцуджи мудзан" << endl;
                                    }
                                } else
                                    if(s == "8"){
                                        cout << "Пока Томиоко"  << endl;
                                        break;
                                    } else {
                                        cout << "Я не понял :(" << endl;
                                    }
    }
    return 0;
}
