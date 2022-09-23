#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

namespace csv_parser {
	using std::cout;
	using std::endl;
	using std::cerr;
	using std::vector;
	using std::string;
	using std::ifstream;
	using std::ofstream;

	using word_list_type = std::vector<std::string>;
	using csv_cell_type = std::string;
	using csv_line_type = std::vector<std::string>;
	using csv_data_type = std::vector<std::vector<std::string>>;
	using search_idx_type = std::pair<size_t, size_t>;
	using search_idx_list_type = std::vector<std::pair<size_t, size_t>>;

	extern word_list_type split(string txt, string delimiter);
	extern void print_word_list(word_list_type word_list);
	extern csv_data_type read_csv(string file_path, string delimiter);
	extern int write_csv(string file_path, csv_data_type csv_data, string delimiter);
	extern void print_csv_data(csv_data_type csv_data, string delimiter, int header, bool show_idx);
	extern vector<size_t> one_line_search(csv_line_type one_line_data, string target_str);
	extern search_idx_list_type search_idx(csv_data_type csv_data, string target_str, bool show_detail);
	extern csv_line_type ext_csv_data(csv_data_type csv_data, vector<search_idx_type> idx_list, bool show_detail);
}