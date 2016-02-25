// count words from a file concurrently
#include <string>
#include <algorithm>
#include <iostream>
#include <ios>
#include <fstream>
#include <array>
#include <thread>

void word_count(const std::string& filename, std::ios::pos_type begin,
	std::ios::pos_type end, std::vector<unsigned long>::iterator count) {
	std::cout << begin << ' ' << end << ": ";
	std::string word;
	std::ifstream file(filename);
	file.seekg(begin);
	while(file && begin < end) {
		file >> word;
		begin = file.tellg();
		*count++;
		std::cout << *count << ' ';
	}
	std::cout << std::endl;
}

unsigned int calculate_nthread(const std::ios::pos_type& file_sz,
	const unsigned long per_thread) {
	const unsigned int hw_nthread = std::thread::hardware_concurrency();
	const unsigned int nthread = file_sz / per_thread;
	return std::min(nthread, hw_nthread);
}

int main(void) {
	constexpr unsigned int per_thread = 25;
	std::string filename;
	std::vector<std::thread> threads;
	std::cout << "Enter file name: ";
	std::cin >> filename;
	if(filename.empty()) return 1;
	std::ifstream file(filename);
	file.seekg(0, std::ios::end);
	std::ios::pos_type file_sz = file.tellg();
	unsigned int nthread = calculate_nthread(file_sz, per_thread);
	unsigned long count = 0;
	std::vector<unsigned long>::size_type processed = 0;
	if(nthread) {
		std::vector<unsigned long> counts(nthread - 1, 0);
		for(std::vector<unsigned long>::iterator i = counts.begin();
			processed != counts.size(); ++processed, ++i) {
			std::ios::pos_type begin = processed * per_thread,
			end = begin + per_thread;
			std::thread t(word_count, filename, begin, end, 
				std::move(i));
			threads.push_back(std::move(t));
		}
		for(std::vector<std::thread>::iterator t = threads.begin();
			t != threads.end(); ++t) {
			if(t->joinable()) t->join();
		}
		std::accumulate(counts.begin(), counts.end(), count);
	}
	const std::ios::pos_type begin = processed * per_thread,
	end = begin + per_thread;
	std::vector<unsigned long> temp(1, 0);
	word_count(filename, begin, end, temp.begin());
	count += *(temp.begin());
	std::cout << "Total " << count << " words\n";
	return 0;
}
