#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Use three parameters...";
        return 5;
    }
    const string mode(argv[1]);
    const string file_name(argv[2]);
    if (mode == "encryption") {
        string str;
        string key;
        cout << "Enter a string: ";
        getline(cin, str);
        cout << "Enter a key: ";
        getline(cin, key);
        unsigned int s_key = 0;
        for (char j: key) s_key += static_cast<unsigned int>(j);
        srand(s_key);
        vector<unsigned char> bytes;
        for (char i: str) bytes.push_back(i);
        ofstream fout;
        fout.open(file_name, ios::binary);
        for (unsigned char i: bytes) {
            unsigned int x = (static_cast<unsigned int>(i) ^ rand()) & 0xFF;
            x = ((x >> 3) & 0xFF | (x << 5) & 0xFF);
            char z = static_cast<char>(x);
            fout.write(&z, sizeof(z));
        }
        fout.close();
    } else if (mode == "decryption") {
        string key;
        cout << "Enter a key: ";
        getline(cin, key);
        unsigned int s_key = 0;
        for (char j: key) s_key += static_cast<unsigned int>(j);
        srand(s_key);
        cout << "Decrypted string: ";
        ifstream out;
        out.open(file_name, ios::binary);
        vector<unsigned char> encryptedData((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
        out.close();
        for (unsigned char i: encryptedData) {
            auto r = static_cast<unsigned int>(i);
            r = (((r << 3) & 0xFF | (r >> 5) & 0xFF) ^ rand()) & 0xFF;
            cout << static_cast<char>(r);
        }
        out.close();
    } else {
        cerr << "Error: enter wrong operation...";
        return 11;
    }
    return 0;
}
