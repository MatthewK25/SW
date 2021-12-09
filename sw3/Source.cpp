#include <iostream>;
#include <fstream>;
#include <iomanip>;
#include <sstream>;
using namespace std;
long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int size = stat(filename.c_str(), &stat_buf);
    return size == 0 ? stat_buf.st_size : -1;
}
int main() {
    setlocale(LC_ALL, "RUS");
    int countLine = 0;
    string line;
    string fileName = "sw3.txt";
    ifstream file(fileName);
    struct TrpoStudent {
        string studentName;
        int trpoMark;
        double averagemarkLabs;
        int rating;
    };
    while (getline(file, line))
        ++countLine;
    file.clear();
    file.seekg(0, ios_base::beg);
    TrpoStudent* student = new TrpoStudent[countLine];

    int i = 0;
    while (file)
    {
        file >> student[i].studentName >> student[i].trpoMark >> student[i].averagemarkLabs >> student[i].rating;
        i++;
    }
    file.close();
    cout << "Data from source file: " << endl;
    for (i = 0; i < countLine; i++) {
        cout << student[i].studentName << " " << student[i].trpoMark << " " << student[i].averagemarkLabs << " " << student[i].rating;
        cout << endl;
    }
    long fileSize;
    fileSize = GetFileSize(fileName);
    std::ofstream out;
    out.open(fileName, std::ios::app);
    for (i = 0; i < countLine; i++) {
        out << endl << student[i].studentName << " " << student[i].trpoMark << " " << student[i].averagemarkLabs << " " << student[i].rating;
    }
    //cортировка по рейтингу по убыванию
    int ind;
    for (i = 0; i < countLine; i++) {
        for (int j = 0; j < countLine; j++) {
            if (student[j].rating < student[i].rating) {
                swap(student[i].rating, student[j].rating);
                swap(student[i].studentName, student[j].studentName);
                swap(student[i].trpoMark, student[j].trpoMark);
                swap(student[i].averagemarkLabs, student[j].averagemarkLabs);
            }
        }
    }
    for (i = 0; i < countLine; i++) {
        out << endl << student[i].studentName << " " << student[i].trpoMark << " " << student[i].averagemarkLabs << " " << student[i].rating;
    }

    cout << "Size of the source file is: " << fileSize << " bytes";
    delete[] student;
}