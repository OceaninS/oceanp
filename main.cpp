#include <iostream>
#include <string>
#include <vector>
#include <fstream>

template<class T> class Array {
private:
    size_t length;
    T* pointer;
public:
    Array() {
        this->length = 0;
        this->pointer = nullptr;
    }
    Array(const T& data) {
        this->length = 1;
        this->pointer = new T[this->length];
        this->pointer[0] = data;
    }
    Array(T* const pointer, size_t length = 0) {
        this->length = length;
        this->pointer = new T[this->length];
        for (size_t index = 0; index != this->length; index++) {
            this->pointer[index] = pointer[index];
        }
    }
    Array(const Array& array) {
        this->length = array.length;
        this->pointer = new T[this->length];
        for (size_t index = 0; index != this->length; index++) {
            this->pointer[index] = array.pointer[index];
        }
    }
    ~Array(){
        if(this->pointer != nullptr){
            delete[] this->pointer;
            this->pointer = nullptr;
        }
    }
    Array& operator=(const Array& array){
        if(this->pointer != nullptr){
            delete[] this->pointer;
            this->pointer = nullptr;
        }
        this->length = array.length;
        this->pointer = new T[this->length];
        for (size_t index = 0; index < this->length; index++)
        {
            this->pointer[index] = array.pointer[index];
        }
        return *this;
    }
    size_t getLength() {
        return this->length;
    }
    T* getPointer() {
        return this->pointer;
    }
    T& operator[](size_t index) {
        if (index >= this->length) throw "undefine";
        return this->pointer[index];
    }
    Array& push(const T& item) {
        const Array temp = *this;
        if (this->pointer != nullptr) {
            delete[] pointer;
            this->pointer = nullptr;
        }
        this->length++;
        this->pointer = new T[this->length];
        for (size_t index = 0; index != this->length - 1; index++) {
            this->pointer[index] = temp.pointer[index];
        }
        this->pointer[this->length - 1] = item;
        return *this;
    };
    Array& pop() {
        if (this->length == 0) {
            this->pointer = nullptr;
            return *this;
        }
        const Array temp = *this;
        if (this->pointer != nullptr) {
            delete[] pointer;
            this->pointer = nullptr;
        }
        this->length--;
        this->pointer = new T[this->length];
        for (size_t index = 0; index != this->length; index++) {
            this->pointer[index] = temp.pointer[index];
        }
        return *this;
    };
    Array& clear() {
        this->length = 0;
        if (this->pointer != nullptr) {
            delete[] this->pointer;
            this->pointer = nullptr;
        }
        return *this;
    }
};

class HandleStr {
public:
    size_t length;
    char* chars;
    Array<Array<char>> array;
public:
    HandleStr() {
        this->length = 0;
        this->chars = nullptr;
    }
    HandleStr(const char chars[]) {
        this->length = 0;
        for (size_t index = 0; chars[index] != '\0'; index++) {
            this->length++;
        }
        this->length++;
        this->chars = new char[this->length];
        for (size_t index = 0; index != this->length; index++) {
            this->chars[index] = chars[index];
        }
    }
    HandleStr(const HandleStr& str) {
        this->length = str.length;
        this->chars = new char[this->length];
        for (size_t index = 0; index != this->length; index++) {
            this->chars[index] = str.chars[index];
        }
    }
    ~HandleStr() {
        if (this->chars != nullptr) {
            delete[] this->chars;
            this->chars = nullptr;
            this->length = 0;
        }
    }
    HandleStr& operator=(const HandleStr& str) {
        if (this->chars != nullptr) {
            delete[] this->chars;
            this->chars = nullptr;
        }
        this->length = str.length;
        this->chars = new char[this->length];
        for (size_t index = 0; index != this->length; index++) {
            this->chars[index] = str.chars[index];
        }
    }
    void print(bool handle = false) {
        if (!handle) {
            std::cout << "处理前：\n";
            std::cout << "\t\t字符串长度=" << this->length << "\t";
            if (this->length == 0) {
                std::cout << "__NULL__" << std::endl;
                return;
            }
            for (size_t index = 0; index != this->length; index++) {
                std::cout << this->chars[index];
            }
            std::cout << std::endl;
        } else {
            this->extract();
            std::cout << "处理后：\n" << "\t\t提取字符个数=" << this->array.getLength() << std::endl;
            if (this->array.getLength() == 0) {
                std::cout << "__NULL__" << std::endl;
                return;
            }
            for (size_t index_x = 0; index_x != this->array.getLength(); index_x++) {
                std::cout << "\t\t";
                for (size_t index_y = 0; index_y != this->array[index_x].getLength(); index_y++) {
                    std::cout << this->array[index_x][index_y];
                }
                std::cout << std::endl;
            }
        }
    }
    char operator[](size_t index) {
        if (index > this->length) {
            throw "Illegel index";
        }
        return this->chars[index];
    }
    Array<Array<char>> extract() {
        Array<Array<char>> array;
        Array<char> word;
        bool isInString = false;
        for (size_t index = 0; index < this->length - 1; index++) {
            if (isInString == false) {
                if (this->chars[index] == '\"') {
                    isInString = true;
                    word.push('\"');
                    continue;
                }
                if (this->isBlank(this->chars[index])) {
                    continue;
                }
                word.push(this->chars[index]);
                if (this->isConnectable(this->chars[index])) {
                    if (this->chars[index] == '<' && (this->chars[index + 1] == '<' || this->chars[index + 1] == '=')) continue;
                    if (this->chars[index] == '>' && (this->chars[index + 1] == '>' || this->chars[index + 1] == '=')) continue;
                    if (this->chars[index] == '+' && (this->chars[index + 1] == '+' || this->chars[index + 1] == '=')) continue;
                    if (this->chars[index] == '-' && (this->chars[index + 1] == '-' || this->chars[index + 1] == '=')) continue;
                    if (this->chars[index] == '*' && (this->chars[index + 1] == '*' || this->chars[index + 1] == '=')) continue;
                    if (this->chars[index] == '/' && (this->chars[index + 1] == '/' || this->chars[index + 1] == '=')) continue;
                    if (this->chars[index] == ':' && this->chars[index + 1] == ':') continue;
                    if (this->chars[index + 1] == '=') continue;
                    array.push(word);
                    word.clear();
                    continue;
                }
                if (this->isIndependent(this->chars[index]) || this->isSpecial(this->chars[index + 1])) {
                    array.push(word);
                    word.clear();
                    continue;
                }
            }
            else {
                if (this->chars[index] == '\"') {
                    isInString = false;
                    word.push('\"');
                    array.push(word);
                    word.clear();
                    continue;
                }
                word.push(this->chars[index]);
                continue;
            }
        }
        if (word.getLength() != 0) {
            array.push(word);
        }
        this->array = array;
        return this->array;
    }
private:
    //判断 空格=32，换行符=10，左圆括号(=40，右圆括号)=41，结构体左括号{=123，结构体右括号}=125，叹号！=33，问号?=63
    bool isSpecial(const char ch) {
        return (this->isBlank(ch) || this->isConnectable(ch) || this->isIndependent(ch));
    }
    bool isBlank(const char ch) {
        return (ch == ' ' || ch == '\n' || ch == '\t') ? true : false;
    }
    bool isConnectable(const char ch) {
        return (ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == ':' || ch == '*' || ch == '+' || ch == '-' || ch == '*' || ch == '/') ? true : false;
    }
    bool isIndependent(const char ch) {
        return (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == '#' || ch == '[' || ch == ']' || ch == '?') ? true : false;
    }
};

void printDoc(Array<Array<Array<char>>>& document) {
    if (document.getLength() == 0) {
        std::cout << "Document is empty!" << std::endl;
        return;
    }
    std::cout << "C风格" << std::endl;
    for (size_t i = 0; i < document.getLength(); i++) {
        std::cout << "第" << i + 1 << "行\t词组个数=" << document[i].getLength() << "\t\t";
        for (size_t j = 0; j < document[i].getLength(); j++) {
            for (size_t k = 0; k < document[i][j].getLength(); k++) {
                std::cout << document[i][j][k];
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void read() {
    std::fstream infile;
    infile.open("string.cpp", std::ios::in);
    if (!infile.is_open()) {
        std::cout << "读取文件失败！！！" << std::endl;
        return;
    }
    char buf[1024] = { 0 };
    Array<Array<Array<char>>> document;
    while (infile.getline(buf, sizeof(buf))) {
        HandleStr line = buf;
        document.push(line.extract());
    }
    printDoc(document);
    infile.close();
}


//  引用标准库
std::vector<std::string> handle_line(std::string str) {
    std::string word;
    std::vector<std::string> line;
    bool isInString = false;
    for (auto it = str.begin(); it != str.end() - 1; it++) {
        if (isInString == false) {
            if (*it == '\"') {
                isInString = true;
                word.push_back('\"');
                continue;
            }
            if (*it == ' ' || *it == '\n' || *it == '\t') continue;
            word.push_back(*it);
            if (*it == '<' && (*(it + 1) == '<' || *(it + 1) == '=')) continue;
            if (*it == '>' && (*(it + 1) == '>' || *(it + 1) == '=')) continue;
            if (*it == '=' && *(it + 1) == '=') continue;
            if (*it == '+' && (*(it + 1) == '=' || *(it + 1) == '+')) continue;
            if (*it == '-' && (*(it + 1) == '=' || *(it + 1) == '-')) continue;
            if (*it == '*' && *(it + 1) == '=') continue;
            if (*it == '/' && *(it + 1) == '=') continue;
            if (*it == ':' && *(it + 1) == ':') continue;
            if ((*it == '!' || *it == '=') && *(it + 1) == '=') continue;
            if (*it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '<' || *it == '>' || *it == '=' || *it == ':' || *it == '(' || *it == ')' || *it == '{' || *it == '}' || *it == '[' || *it == ']' || *it == ';' || *it == '#') {
                line.push_back(word);
                word = "";
                continue;
            }
            if (*(it + 1) == '\"' || *(it + 1) == '+' || *(it + 1) == '-' || *(it + 1) == '*' || *(it + 1) == '/' || *(it + 1) == ' ' || *(it + 1) == '\n' || *(it + 1) == '\t' || *(it + 1) == '<' || *(it + 1) == '>' || *(it + 1) == ':' || *(it + 1) == '!' || *(it + 1) == '=' || *(it + 1) == '(' || *(it + 1) == ')' || *(it + 1) == '{' || *(it + 1) == '}' || *(it + 1) == '[' || *(it + 1) == ']' || *(it + 1) == ';' || *(it + 1) == '#' || *(it + 1) == '?') {
                line.push_back(word);
                word = "";
            }
        }
        else
        {
            if (*it == '\"') {
                isInString = false;
                word.push_back('\"');
                line.push_back(word);
                word = "";
                continue;
            }
            word.push_back(*it);
        }
    }
    if (word != "") {
        line.push_back(word);
    }
    return line;
}

std::vector<std::vector<std::string>> handle_document(std::string filename) {
    std::fstream infile;
    std::vector<std::vector<std::string>> document;
    infile.open(filename, std::ios::in);
    if (!infile.is_open()) {
        std::cout << "读取文件失败！！！" << std::endl;
        return document;
    }
    std::string buffer;
    uint32_t i = 0;
    while (getline(infile, buffer)) {
        std::cout << "第" << ++i << "行\t\t\t" << buffer << std::endl;
        buffer.push_back('\0');
        document.push_back(handle_line(buffer));
    }
    std::cout << std::endl << std::endl;
    return document;
}
void print_vector(const std::vector<std::vector<std::string>>& document){
    if (document.begin() == document.end()) {
        std::cout << "Document is empty!" << std::endl;
        return;
    }
    std::cout << "C++风格" << std::endl;
    for (auto it = document.begin(); it != document.end(); it++) {
        std::cout << "第" << it - document.begin() + 1 << "行\t词组个数=" << (*it).size() << "\t\t";
        for (auto po = (*it).begin(); po != (*it).end(); po++) {
            std::cout << *po << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    print_vector(handle_document("string.cpp"));
    read();

    std::cout << std::endl;
    system("pause");
    return 0;
}