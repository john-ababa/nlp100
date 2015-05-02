#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <mecab.h>
#include "common.h"

std::string splitWord(const std::string& feature, const size_t count)
{
	size_t pos = 0, pos2 = 0, c = 0;
	while ((pos2 = feature.find_first_of(",", pos)) != std::string::npos) {
		if (++c == count)
			break;
		pos = pos2 + 1;
	}
	return feature.substr(pos, pos2-pos);
}

std::vector<std::map<std::string, std::string>> runMecab(void)
{
	std::shared_ptr<MeCab::Tagger> tagger = std::shared_ptr<MeCab::Tagger>(MeCab::createTagger(""));
	std::vector<std::map<std::string, std::string>> vec;

	std::ifstream ifs("neko.txt");
	for (std::string line; std::getline(ifs, line); ) {
		for (const MeCab::Node* node = tagger->parseToNode(line.c_str()); node != NULL; node = node->next) {
			if (node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE) {
				std::map<std::string, std::string> m;
				m["surface"] = std::string(node->surface, node->length); 
				m["base"] = splitWord(node->feature, 7);              
				m["pos"]  = splitWord(node->feature, 1);              
				m["pos1"] = splitWord(node->feature, 2);              
				vec.push_back(m);
			}
		}
	}
	return vec;
}
