#include "csv_parser.h"

namespace csv_parser {
	word_list_type split(string txt, string delimiter) {
		word_list_type word_list{};
		size_t pos;
		while ((pos = txt.find(delimiter)) != string::npos) {
			word_list.push_back(txt.substr(0, pos));
			txt.erase(0, pos + delimiter.length());
		}
		// last word
		word_list.push_back(txt);
		return word_list;
	}

	void print_word_list(word_list_type word_list) {
		for (const auto& str : word_list) {
			cout << str << endl;
		}
	}

	csv_data_type read_csv(string file_path, string delimiter) {
		string str;
		csv_data_type csv_data{};
		ifstream ifs(file_path);

		if (ifs.fail()) {
			cerr << "File open error: " << file_path << "\n";
			return csv_data;
		}

		while (getline(ifs, str)) {
			csv_data.push_back(split(str, delimiter));
		}

		return csv_data;
	}

	int write_csv(string file_path, csv_data_type csv_data, string delimiter) {
		ofstream ofs(file_path);

		if (ofs.fail()) {
			std::cerr << "File open error: " << file_path << "\n";
			return EXIT_FAILURE;
		}

		// write
		for (size_t i = 0; i < csv_data.size(); i++) {
			for (size_t j = 0; j < csv_data[0].size(); j++) {
				ofs << csv_data[i][j] << delimiter;
			}
			ofs << endl;
		}

		if (ofs.fail()) {
			cerr << "File write error: " << file_path << "\n";
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}

	void print_csv_data(csv_data_type csv_data, string delimiter, int header = 0, bool show_idx = false) {
		for (size_t i = 0; i < csv_data.size(); i++) {
			if (show_idx == true) {
				cout << i << ": ";
			}
			for (size_t j = 0; j < csv_data[i].size(); j++) {
				cout << csv_data[i][j] << delimiter << "\t";
			}
			cout << endl;
			if (header == i) {
				cout << "----------------------------------------------" << endl;
			}
		}
	}

	vector<size_t> one_line_search(csv_line_type one_line_data, string target_str) {
		vector<size_t> idx_list{};

		for (size_t i = 0; i < one_line_data.size(); i++) {
			string str = one_line_data[i];
			size_t index = str.find(target_str);
			if (index != std::string::npos) {
				idx_list.push_back(i);
			}
		}

		return idx_list;
	}

	search_idx_list_type search_idx(csv_data_type csv_data, string target_str, bool show_detail = false) {
		search_idx_list_type idx_list{};

		if (target_str == "") {
			return idx_list;
		}

		for (size_t i = 0; i < csv_data.size(); i++) {
			vector<size_t> v = one_line_search(csv_data[i], target_str);
			for (size_t j = 0; j < v.size(); j++) {
				search_idx_type idx(i, v[j]);
				idx_list.push_back(idx);
			}
		}

		if (show_detail == true) {
			cout << "target word is : " << target_str << endl;
			for (size_t i = 0; i < idx_list.size(); i++) {
				cout << "(" << idx_list[i].first << ", " << idx_list[i].second << ") ";
			}
			cout << endl;
		}

		return idx_list;
	}

	csv_line_type ext_csv_data(csv_data_type csv_data, vector<search_idx_type> idx_list, bool show_detail = false) {
		csv_line_type result{};
		for (size_t i = 0; i < idx_list.size(); i++) {
			result.push_back(csv_data[idx_list[i].first][idx_list[i].second]);
		}

		if (show_detail == true) {
			cout << "ext csv data : " << endl;
			for (size_t i = 0; i < result.size(); i++) {
				cout << result[i] << endl;
			}
		}

		return result;
	}
}

#if(0)
using namespace csv_parser;
int main() {
	string text = "If you can dream it, you can do it.\n"
		"Love the life you live. Live the life you love.\n"
		"You’ll never find a rainbow if you’re looking down.\n";
	string delimiter = ",";

	// split
	word_list_type word_list{};
	word_list = split(text, delimiter);
	cout << "--- print_word_list ---" << endl;
	print_word_list(word_list);

	// csv
	csv_data_type csv_data = read_csv("./test_csv_data.csv", ",");
	cout << "--- print_csv_data ---" << endl;
	print_csv_data(csv_data, delimiter, 0, true);

	search_idx_list_type idx_list = search_idx(csv_data, "example", true);
	ext_csv_data(csv_data, idx_list, true);

	(void)write_csv("./test_write.csv", csv_data, delimiter);

	return EXIT_SUCCESS;
}
#endif