#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <string>
#include "Functions.h"
using namespace std;


void delete_save() {
    remove("C:\\Users\\baran\\Desktop\\game files\\save_data.txt");
    remove("C:\\Users\\baran\\Desktop\\game files\\held_items.txt");
}
float reel_price(float earn, short int mult) {
    return mult * 50 + (earn / 3.0);
}
bool fif() {
    const short int random = rand() % 2;
    if (random) return true;
    else return false;
}
float roundoff(float value, unsigned char prec)
{
    float pow_10 = pow(10.0f, (float)prec);
    return round(value * pow_10) / pow_10;
}

int line_count(const string* inp) {
    ifstream aFile(*inp);
    std::size_t lines_count = 0;
    std::string line;
    while (std::getline(aFile, line)) ++lines_count;
    return  lines_count;
}
string write_line(const string* path, const short int n) {
    fstream file;
    file.open(*path, ios::in);
    string str;
    for (int i = 0; i < n + 1; ++i) {
        getline(file, str);
    }
    file.close();
    return str;
}
int value(string path, const short int n) {
    path = write_line(&path, n);
    return stoi(path.substr(path.find(':') + 1));
}
string write(const string path, const short int n) {
    return write_line(&path, n).substr(0, write_line(&path, n).find(':'));
}
void delete_line_held(short int n) {
    fstream file;
    file.open("C:\\Users\\baran\\Desktop\\game files\\held_items.txt", ios::in);
    fstream file2;
    file2.open("C:\\Users\\baran\\Desktop\\game files\\temp.txt", ios::out);
    string s;
    for (int i = 0; i < line_count(&held_items); ++i) {
        getline(file, s);
        if (i != n) {

            file2 << s << endl;
        }
    }
    file.close();
    file2.close();
    remove("C:\\Users\\baran\\Desktop\\game files\\held_items.txt");
    rename("C:\\Users\\baran\\Desktop\\game files\\temp.txt", "C:\\Users\\baran\\Desktop\\game files\\held_items.txt");

}
int value_held(string path, const short int n) {
    path = write_line(&path, n);
    return stoi(path.substr(path.find(':') + 1, path.find('-')));
}

