#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <string>



using namespace std;

#define delay 0
const static string held_items = R"(data\\held_items.txt)";
const static string items = R"(data\\items.txt)";

float reel_price(float, short int);
bool fif();
void delete_save();
int line_count(const string*);
string write_line(const string*, const short int);
int value(const string, const short int);
string write(const string, const short int);
float roundoff(float, unsigned char);
void delete_line_held(short int n);
int value_held(string path, const short int n);

class player {
public:
    float gain = 0, m_earned = 0, money_p = -1;
    unsigned short int level = 1, day = 1;
    string name_p = "unspecified", difficulty = "unspecified";



    void money(const float n, const char l) {
        if (l == '+') {
            money_p += n;
            m_earned += n;
            gain += n;
        }
        else if (l == '-') {
            money_p -= n;
            gain -= n;
        }
        if (gain >= (money_p - gain) * pow(2, level - 1) && level <= 10) {
            level++;
        }
    }
    float guess(const unsigned short int mult) {
        if (fif()) return reel_price(gain, mult) - (reel_price(gain, mult) * (level / 10.0));
        else return reel_price(gain, mult) + (reel_price(gain, mult) * (level / 10.0));
    }
    string find_price(string path, const short int n) {
        path = write_line(&path, n);
        return path.substr(path.find('-') + 1);
    }

};

class customer {
public:
    customer() {}
    const unsigned short int knowledge = rand() % 3 + 1;
    const unsigned short int richness = rand() % 100 + 1;

    float guess(const unsigned short int mult, float gain) {
        if (richness >= 75) return reel_price(gain, mult) + (reel_price(gain, mult) * (knowledge / 2.5));
        if (fif() && richness >= 50) return reel_price(gain, mult) + (reel_price(gain, mult) * (knowledge / 2.5));
        if (richness <= 50 && fif()) return reel_price(gain, mult) + (reel_price(gain, mult) * (knowledge / 2.5));
        if (richness <= 50 && !fif()) return reel_price(gain, mult) - (reel_price(gain, mult) * (knowledge / 2.5));
        if (richness <= 25) return reel_price(gain, mult) - (reel_price(gain, mult) * (knowledge / 2.5));
    }
    string name() {
        string* ptr = new string;
        *ptr = "data\\names.txt";
        short int random = rand() % line_count(ptr);
        return write_line(ptr, random);
    }
};

void save_game(player*);
void load_game(player*);

int main() {
    srand(time(NULL));
    player p;
    cout << "<----------- Oyuna Hos Geldiniz ------------>\n";
    cout << " | 1-) Yeni oyuna basla(Eski kayit silinir)|\n";
    cout << " | 2-) Oyuna devam et                      |\n";
    cout << " | 3-) Kayitli veriyi sil                  |\n";
    cout << " | 4-) Oyunu sonlandir.                    |\n";
    cout << "<------------------------------------------->\n";
    short inp;
    fstream held;

    while (true) {
        cout << "Islem secin:";
        cin >> inp;
        if (inp == 1) {
            held.open(held_items, ios::out);
            held.close();
            cout << "------------------------\n";
            //Sleep       (delay);
            cout << "Sehre yeni geldin ve al-sat dukkanini yeni actin, kar etmek icin yapman gereken cok basit.\n";
            //Sleep       (delay);
            cout << "Gelen mallari musterilerden teklif ettigin ucrete al ve onlari yeni musterilere sat.\n";
            //Sleep       (delay);
            cout << "Seviyen arttikca musterilere mallarini istedigin fiyattan almak ve satmak kolaylasacak.\n<-->\n";
            //Sleep       (delay);

            cout << "Bir ad belirleyin:";
            cin >> p.name_p;

            bool test;
            do {
                cout << "Zorluk secin(Kolay, Normal, Zor):";
                cin >> p.difficulty;
                transform(p.difficulty.begin(), p.difficulty.end(), p.difficulty.begin(), ::tolower);
                test = false;
                if (p.difficulty == "kolay") p.money_p = 2000;
                else if (p.difficulty == "normal") p.money_p = 1000;
                else if (p.difficulty == "zor") p.money_p = 500;
                else {
                    test = true;
                    cout << "Gecerli bir zorluk girin.\n";
                }
            } while (test);

            cout << "\nHer gun dukkani 8'de acip 5'de kapatirsin. Makul fiyattan urunleri al ve sat.\n";
            cout << "*****************************************\n";
            //Sleep       (delay);
            break;
        }
        else if (inp == 2) {
            load_game(&p);
            cout << "Yuklenme tamamlandi." << endl;
            //Sleep       (delay);
            break;
        }
        else if (inp == 3) {
            delete_save();
            cout << "Verileriniz silindi." << endl;
            continue;
        }
        else if (inp == 4) {
            cout << "Oyun sonlandiriliyor...";
            //Sleep       (1);
            return 0;
        }
        else {
            cout << "Yanlis girdi.\n";
            continue;
        }
    } //Oyun baþlangýç menüsü.

    char in;
    short time, random, random_held;
    float price;

    cout << "Gelen teklifleri kabul etmek icin = 'K'" << endl;
    cout << " Gelen teklifleri reddetmek icin  = 'R'" << endl;
    cout << "         Gunu bitirmek icin       = 'B'" << endl;
    cout << "-----------------------------------------" << endl;
    //Sleep       (delay);

    held.open(held_items, ios::app);

    while (true) {   // Ana while döngüsü kullanýcý isteyene kadar oyunun devamýný saðlar
        cout << p.day << ". gun basladi---\n";
        time = 0;
        //Sleep       (delay);
        cout << "Guncel paraniz: " << p.money_p << " | Guncel seviyeniz: " << p.level << " | Toplam ettiginiz kar: " << p.gain << endl << endl;
        held.seekg(0, ios::end);

        while (time <= 240) { // Günlerin geçmesini saðlayan döngü
            chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            customer cus;
            random = rand() % line_count(&items);
            price = roundoff(abs(cus.guess(value(items, random), p.gain)), 2);

            if (fif()) {
                cout << cus.name() << ", " << write(items, random) << "'i " << price << "'a $ satmak istiyor." << " Tahmin ettigin ucret: " << p.guess(
                    value(items, random)) << endl;
                cout << "Islem: ";
                cin >> in;

                if (in == 'K' || in == 'k') {
                    if (p.money_p >= price) {
                        p.money(price, '-');
                        held << write_line(&items, random) << "-" << price << endl;
                        cout << "Satin alim basarili, yeni bakiye: " << p.money_p << endl;
                    }
                    else cout << "Paraniz yeterli degil.\n";
                }
                else if (in == 'R' || in == 'r');
                else if (in == 'B' || in == 'b') break;
                else cout << "Yanlis giridi." << endl;
            }

            else if (!held.tellg() == 0) {
                random_held = rand() % line_count(&held_items);
                cout << cus.name() << ", " << write(held_items, random_held) << "'i " << p.find_price(held_items, random_held) << "'a $ almak istiyor."
                    << " Tahmin ettigin ucret: " << p.guess(value_held(held_items, random_held)) << endl;
                cout << "Islem: ";
                cin >> in;

                if (in == 'K' || in == 'k') {
                    p.money(stoi(p.find_price(held_items, random_held)), '+');
                    held.close();
                    delete_line_held(random_held);
                    cout << "Satim basarili, yeni bakiye: " << p.money_p << endl;
                    held.open(held_items, ios::app);
                }
                else if (in == 'R' || in == 'r');
                else if (in == 'B' || in == 'b') break;
                else cout << "Yanlis giridi." << endl;
            }

            chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            time += chrono::duration_cast<std::chrono::seconds>(end - begin).count();
            //Sleep       (delay);
        }


        cout << p.day << ". gun bitti.---\n";
        //Sleep       (2 / 3);
        cout << "Devam etmek icin = 'D', Kaydetip cikmak icin = 'Q':";
        cin >> in;
        ++p.day;
        while (true) {
            if (in == 'D' || in == 'd') break;
            else if (in == 'q' || in == 'Q') {
                save_game(&p);
                held.close();
                cout << "Kayit basarili, cikis yapiliyor...";
                //Sleep       (2 / 3);
                return 0;
            }
            else {
                cout << "Yanlis girdi.\n";
                cout << "Devam etmek icin = 'D', Kaydetip cikmak icin = 'Q':";
                cin >> in;
            }
        } // Oyun devamlýlýðýný saðlayan girdi
        //Sleep       (delay);

    }

}
//-----------------------------------------------------------------------
void save_game(player* cname) {
    fstream save;
    save.open(R"(data\\save_data.txt)", ios::out);
    save << "Money:" << cname->money_p << endl;
    save << "Name:" << cname->name_p << endl;
    save << "Difficulty:" << cname->difficulty << endl;
    save << "Gain:" << cname->gain << endl;
    save << "Total_Earned:" << cname->m_earned << endl;
    save << "Day:" << cname->day;
    save.close();
}
void load_game(player* cname) {
    fstream load;
    load.open("data\\save_data.txt", ios::in);
    if (load.is_open()) {
        string data[6];
        for (int i = 0; i < 6; ++i) {
            getline(load, data[i]);
        }
        cname->money_p = stof(data[0].substr(data[0].find(':') + 1));
        cname->name_p = data[1].substr(data[1].find(':') + 1);
        cname->difficulty = data[2].substr(data[2].find(':') + 1);
        cname->gain = stof(data[3].substr(data[3].find(':') + 1));
        cname->m_earned = stof(data[4].substr(data[4].find(':') + 1));
        cname->day = stof(data[5].substr(data[5].find(':') + 1));
        load.close();
    }
}
void delete_save() {
    remove("data\\save_data.txt");
    remove("data\\held_items.txt");
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
    file.open("data\\held_items.txt", ios::in);
    fstream file2;
    file2.open("data\\temp.txt", ios::out);
    string s;
    for (int i = 0; i < line_count(&held_items); ++i) {
        getline(file, s);
        if (i != n) {

            file2 << s << endl;
        }
    }
    file.close();
    file2.close();
    remove("data\\held_items.txt");
    rename("data\\temp.txt", "data\\held_items.txt");

}
int value_held(string path, const short int n) {
    path = write_line(&path, n);
    return stoi(path.substr(path.find(':') + 1, path.find('-')));
}
