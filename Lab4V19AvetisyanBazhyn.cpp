// Лабораторна робота №4 варіант 19. Виконують Бажин Олександр та Аветисян Єгор з групи К-24
// вар 19  
//     поле 0          поле 1
// read    write    read   write       string
// 5%      40%      5%     5%          45%

#include <iostream>
#include <mutex>
#include "Struct.h"
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <thread>
#include <syncstream>

using namespace std;

int NumberOfFiles(int NumOfThreads);   //повернення випадкового числа, що є кількістю файлів, що будуть згенеровані в майбутньому відповідно до кількості потоків для програми
vector<string> GenerateComands(vector<int> dist);   //генерація команд за заданим розподілом 
void GenetateInputFiles(int NumberOfFiles, vector<int> distribution);  //створення випадкової кількості файлів серед яких розподіляються команди
void DoCommands(int NumberOfFiles, int NumOfThreads);
void ReadCommand(string FileName, Calc& a);
void GetDistrInf(vector<int> distribution);

int main()
{
    vector<int> distribution1 = { 5,40,5,5,45 }; // розподіл заданий варіантом
    vector<int> distribution2 = { 20,20,20,20,20 }; // рівномірний розподіл між операціями
    vector<int> distribution3 = { 30,20,10,30,10 };// далекий від умови розподіл
    vector<vector<int>> distributions = { distribution1, distribution2 , distribution3 };
    for (auto& dist : distributions) {
        for (int NumOfThreads = 1; NumOfThreads < 4; NumOfThreads++) {
            cout << "<<<Counting for " << NumOfThreads << " threads>>>" << endl;
            GetDistrInf(dist);
            int num = NumberOfFiles(NumOfThreads);
            GenetateInputFiles(num, dist);
            DoCommands(num, NumOfThreads);
            cout << "____________________________________" << endl;
        }
    }
    return 0;
}

int NumberOfFiles(int NumOfThreads) {
    int NumberOfFiles = 0;
    if (NumOfThreads == 1) {

        random_device r;

        seed_seq seeds{ r(), r(), r(), r(), r(), r() };

        default_random_engine e(seeds);

        uniform_real_distribution<double> d(2, 6); //нехай кількість файлів буде від 2 до 6

        NumberOfFiles = d(e);
    }
    else NumberOfFiles = NumOfThreads;
    return NumberOfFiles;
}

void GenetateInputFiles(int NumberOfFiles, vector<int> distribution) {
    vector<string> commands = GenerateComands(distribution);

    int NumOfFiles = NumberOfFiles;

    for (int i = 0; i < NumOfFiles; i++) {
        string FileName = to_string(i)+".txt"; //створення файлів з назвою (0,1,...,NumOfFiles).txt
        ofstream fout(FileName);
        if (fout.is_open()) {
            int incr = commands.size() / NumOfFiles * i;
            for (int j = 0+incr; j < commands.size()/ NumOfFiles +incr; j++) {
                fout << commands[j];
            }
        } else cout << "Error while file was oppening";
        fout.close();
    }
}

vector<string> GenerateComands(vector<int> dist) {
    vector<string> commands;
    string temp;
    for (int i = 0; i < dist.size(); i++) {
        for (int j = 0; j < dist[i]; j++) {
            if (i == 0) {
                temp = "read 0\n";
            }
            else if (i == 1) {
                temp = "write 0 " + to_string(j) + "\n";
            }
            else if (i == 2) {
                temp = "read 1\n";
            }
            else if (i == 3) {
                temp = "write 1 " + to_string(j) + "\n";
            }
            else if (i == 4) {
                temp = "string\n";
            }
            commands.push_back(temp);
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(commands.begin(), commands.end(), g); //оскільки команди у векторі впорядковані - перемішаємо для рівномірного невпорядкованого розподіленні між файлами 
    return commands;
}

void DoCommands(int NumberOfFiles, int NumOfThreads) {
    Calc a;
    vector<thread> Threads;
    if (NumOfThreads == 1) {
        for (int i = 0; i < NumberOfFiles; i++) {
            string FileName = to_string(i) + ".txt";
            ReadCommand(FileName, a);
        }
    }
    else {
        for (int i = 0; i < NumOfThreads; i++) {
            string FileName = to_string(i) + ".txt";
            Threads.push_back(std::thread(ReadCommand, FileName, ref(a)));
        }
        for (auto& t : Threads) {
            t.join();
        }
    }
}

void ReadCommand(string FileName, Calc&a) {
    chrono::time_point<chrono::high_resolution_clock> start_time, end_time;
    chrono::duration<double> total_time(0);
    ifstream fin(FileName);
    string out_path = "out" + FileName;
    ofstream fout(out_path);
    string command;
    int field;
    int value;
    int b = 0;
    if (fin.is_open()) {
        while (fin >> command) {
            if (command == "write") {
                fin >> field;
                fin >> value;
                start_time = std::chrono::high_resolution_clock::now();
                a.SetField(field, value);
                end_time = std::chrono::high_resolution_clock::now();
            }
            else if (command == "read") {
                fin >> field;
                start_time = std::chrono::high_resolution_clock::now();
                a.GetField(field);
                end_time = std::chrono::high_resolution_clock::now();
            }
            else if (command == "string") {
                start_time = std::chrono::high_resolution_clock::now();
                string info = a;
                end_time = std::chrono::high_resolution_clock::now();
                fout << info;
            }
            auto tdiff = end_time - start_time;
            total_time += tdiff;
        }
        fout.close();
        fin.close();
    }
    //auto time_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
    auto bout = osyncstream(cout);

    bout <<"This thread id: " << this_thread::get_id() << endl;
    bout<< "Spend "<<total_time <<" for counting commands in " <<FileName << "\n\n";
}

void GetDistrInf(vector<int> distribution) {
    cout << "Distribution { ";
    for (int i = 0; i < distribution.size(); i++) {
        cout << distribution[i] << ";";
    }
    cout << " }\n";
}