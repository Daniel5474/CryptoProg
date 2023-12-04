#include <iostream>
#include <fstream>
#include <cryptopp/md4.h> // Изменяем на md4.h
#include <cryptopp/hex.h>

using namespace CryptoPP;
using namespace std;

// Функция для вычисления хэша md4 из файла
string calculateMD4(const string& filename) // Изменяем на calculatemd4
{
    MD4 hash; // Изменяем на md4

    // Открываем файл для бинарного чтения
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла" << endl;
        exit(EXIT_FAILURE);
    }

    // Устанавливаем буфер для чтения файла
    const size_t bufferSize = 8192;
    byte buffer[bufferSize];

    // Инициализация хэша
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(buffer), bufferSize);
        hash.Update(buffer, file.gcount());
    }

    // Завершение вычисления хэша
    file.close();
    byte hashResult[MD4::DIGESTSIZE]; // Изменяем на md4::DIGESTSIZE
    hash.Final(hashResult);

    // Преобразование бинарного хэша в строку шестнадцатеричных цифр
    string hexResult;
    StringSource(hashResult, sizeof(hashResult), true, new HexEncoder(new StringSink(hexResult)));

    return hexResult;
}

int main()
{
    // Замените "example.txt" на имя вашего файла
    const string filename = "text.txt";

    string hashResult = calculateMD4(filename); // Изменяем на calculatemd4

    cout << "(MD4): " << hashResult << endl; // Изменяем на md4

    return 0;
}
