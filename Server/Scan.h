#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
/* Структура для стандартизации проверяемых файлов */
class Scan {
	struct suspected
	{
		string name; /* имя */
		vector<string> file_extension; /* Расширения файлов */
		vector<string> target; /* Ключевые слова для поиска по файлу */
	};
	string path;
	size_t processed_files;

	/* Статический массив всех проверок */
	static vector<suspected> suspects;
	/* Функция, которая принимает файлы и проверяет по шаблону */
	static void scan(vector<string> &files, const vector<string> &suspicious, unsigned int &err, size_t &processed_files);
public:
	Scan(string path);
	/* Функция, запускающая сканирование */
	string start_scan();
	/* Функция, возвращающая адресс шаблонов проверки */
	static vector<suspected> &get_suspected();
};

