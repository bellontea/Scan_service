#include "Scan.h"

/* Ининциализация проверок, при необходимости можно дополнить
 * или изменить если вызвать функцию get_suspected*/
vector<Scan::suspected> Scan::suspects =
		{{"JS", {".js"}, {"<script>evil_script()</script>"}},
		 {"unix", {""}, {"rm -rf ~/Documents"}},
		 {"macOS", {""}, {"system(\"launchctl load /Library/LaunchAgents/com.malware.agent\")"}}};

Scan::Scan(string path) : path(std::move(path)), processed_files(0)
{}

void Scan::scan(vector<string> &files, const vector<string> &suspicious, unsigned int &err, size_t &processed_files)
{
	vector<string> res;
	char elem;

	for(string &file_name : files)
	{
		ifstream file(file_name);
		if (!file.is_open())
		{
			++err;
			processed_files--;
			continue;
		}
		while(!file.eof() && (res.empty() || res.back() != file_name))
		{
			elem = (char)file.get();
			/* Считываю посимвольно,
			 * потому что "\n" тоже необходимо учитывать,
			 * хоть и есть потеря производительности
			*/
			for(const string &check : suspicious)
			{
				int i = 0;
				while(check[i] == elem)
				{elem = (char)file.get(); ++i;}
				if (i == check.size())
				{res.push_back(file_name); break;}
				if(i)
					file.seekg(-i, ios::cur);// Возвращаемся назад
			}
		}
		file.close();
	}
	files = res;
}

std::string Scan::start_scan()
{
	clock_t time = clock();
	/* Массив с названиями файлов для каждого типа подозреваемых */
	vector<vector<string>> files(suspects.size());
	unsigned int err = 0;

	try {
		for(filesystem::path p : filesystem::directory_iterator(path))
		{
			string s(p.string());
			// Приводим к нижнему регистру
			for_each(s.begin(), s.end(),[](char &c){c = (char)tolower(c);});
			for(int i = 0; i < suspects.size(); i++)
				// Неодходимо найти файлы с соответсвующим расширением
				for(const auto &extension : suspects[i].file_extension)
					if(extension.empty() || (s.size() > extension.size()
					   && !s.compare(s.size() - extension.size(), extension.size(), extension)))
						files[i].push_back(s);
			processed_files++;
		}
	} catch(exception &e)
	{ cout << e.what() << endl; return {}; }
	for (int i = 0; auto &f : files)
		scan(f, suspects[i++].target, err, processed_files);
	std::stringstream result;
	time = clock() - time;
	result	<< "====== Scan result ======\n"
			<< "Processed files: " << processed_files << endl;
	for (int i = 0; const auto &f : files)
		result << suspects[i++].name << " detects: " << f.size() << endl;
	result	<< "Errors: " << err << endl
			<< "Execution time: "
			<< setfill('0') << setw(2) << time / (CLOCKS_PER_SEC * 60) << ":"
			<< setfill('0') << setw(2) << (time / (CLOCKS_PER_SEC)) % 60<< ":"
			<< setfill('0') << setw(2) << time % (CLOCKS_PER_SEC) / 10 << endl
			<< "=========================\n";
	return result.str();
}

vector<Scan::suspected> &Scan::get_suspected() {
	return suspects;
}


