#include <string>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

class Shortener {
    const int ASCII_MAX = 128;
    const int SHORT_KEY_MIN = 8;
    const int SHORT_KEY_MAX = 12;
    unordered_map<string, string> shortToLongMap;

    public:

    string generateShortKey(){
        int keyLength = rand() % (SHORT_KEY_MAX + 1 - SHORT_KEY_MIN);
        string shortKey = string(keyLength, '0');
        for (int i = 0; i < keyLength; i++){
            char charAtI = static_cast<char>(rand() % (ASCII_MAX));
            shortKey[i] = charAtI;
        }
        return shortKey;
    }

    string createEntry(string shortKey, string longUrl){
        shortToLongMap[shortKey] = longUrl;
        ofstream fileWriter;
        fileWriter.open("keyMap.txt", ios_base::app);
        fileWriter << shortKey << endl;
        fileWriter << longUrl << endl;
        return shortKey;
    }

    string getLongUrlFor(string shortKey){
        return shortToLongMap[shortKey];
    }

    Shortener(){
        addKeysFromFile();
    }

    void addKeysFromFile(){
        ifstream fileReader("keyMap.txt");
        string shortKey;
        string longKey;
        while (getline(fileReader, shortKey)){
            getline(fileReader, longKey);
                shortToLongMap[shortKey] = longKey;
        }
    }

    

};

int main(){
    Shortener s = Shortener();
    string key = s.generateShortKey();
    string betterKey = s.generateShortKey();
    cout << "KEY :" << key << endl;
    cout << "BETTER :" << betterKey << endl;
    s.createEntry(key, "shop.ify/DUSDHUASUIND");
    s.createEntry(betterKey, "shop.ify/BETTERKEY");
    cout << "LONG URL: " << s.getLongUrlFor(key) << endl;
    cout << "LONG URL: " << s.getLongUrlFor(betterKey) << endl;
}
