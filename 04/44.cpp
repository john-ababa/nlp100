/* ============================================================================
 * 44. 係り受け木の可視化
 *
 * 与えられた文の係り受け木を有向グラフとして可視化せよ．
 * 可視化には，係り受け木をDOT言語に変換し，Graphvizを用いるとよい．
 * また，Pythonから有向グラフを直接的に可視化するには，pydotを使うとよい．
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cabocha.h>
#include <rapidxml/rapidxml.hpp>

class Morph {
public:
	const std::string surface;
	const std::string base;
	const std::string pos;
	const std::string pos1;
	Morph(const std::string& _surface, const std::string& _base, const std::string& _pos, const std::string& _pos1)
		: surface(_surface), base(_base), pos(_pos), pos1(_pos1) { ; }
};

class Chunk {
public:
	std::vector<Morph> morphs;
	int dst;
	std::vector<int> srcs;
	Chunk() : dst(-1) { ; }
};

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

std::vector<Morph> parseTok(rapidxml::xml_node<> *node)
{
	std::vector<Morph> morphs;
	for (rapidxml::xml_node<> *tok = node->first_node(); tok; tok = tok->next_sibling()) {
		for (rapidxml::xml_attribute<> *attr = tok->first_attribute(); attr; attr = attr->next_attribute()) {
			if (attr->name() == std::string("feature")) {
				const std::string surface = tok->value();
				const std::string base = splitWord(attr->value(), 7);
				const std::string pos =  splitWord(attr->value(), 1);
				const std::string pos1 = splitWord(attr->value(), 2);
				morphs.push_back(Morph(surface, base, pos, pos1));
			}
		}
	}
	return morphs;
}

Chunk parseChunk(rapidxml::xml_node<> *node)
{
	Chunk chunk;
	for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		if (attr->name() == std::string("link"))
			chunk.dst = std::stoi(attr->value());
	}
	chunk.morphs = parseTok(node);
	return chunk;
}


std::string getBunsetsu(const std::vector<Morph>& morphs)
{
	std::stringstream ss;
	for (auto itr = morphs.begin(); itr != morphs.end(); ++itr) {
		if (itr->pos != "記号")
			ss << itr->surface;
	}
	return ss.str();
}

bool hasHinshi(const std::vector<Morph>& morphs, const std::string& hinshi)
{
	for (auto itr = morphs.begin(); itr != morphs.end(); ++itr) {
		if (itr->pos == hinshi)
			return true;
	}
	return false;
}

int main(void)
{
	std::shared_ptr<CaboCha::Parser> parser = std::shared_ptr<CaboCha::Parser>(CaboCha::createParser("-f3"));

	const std::string str = "何でも薄暗いじめじめした所でニャーニャー泣いていた事だけは記憶している。";
	const std::string cabocha_xml = parser->parseToString(str.c_str());

	std::vector<Chunk> chunks;
	rapidxml::xml_document<> doc;
	doc.parse<0>((char*)cabocha_xml.c_str());
	for (rapidxml::xml_node<> *p = doc.first_node()->first_node(); p; p = p->next_sibling())
		chunks.push_back(parseChunk(p));
	for (size_t i = 0; i < chunks.size(); ++i) {
		if (chunks[i].dst != -1)
			chunks[chunks[i].dst].srcs.push_back(i);
	}

	std::ofstream ofs("graph.dat");
	ofs << "digraph graphname {" << std::endl;
	for (size_t i = 0; i < chunks.size(); ++i) {
		for (size_t j = 0; j < chunks[i].srcs.size(); ++j) {
			ofs << getBunsetsu(chunks[chunks[i].srcs[j]].morphs) << " -> ";
			ofs << getBunsetsu(chunks[i].morphs) << ";" << std::endl;
		}
	}
	ofs << "}" << std::endl;

	std::system("dot graph.dat -Tpng -o graph.png");
	std::system("eog graph.png");
}
