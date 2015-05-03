/* ============================================================================
 * 41. 係り受け解析結果の読み込み（文節・係り受け）
 *
 * 40に加えて，文節を表すクラスChunkを実装せよ．このクラスは形態素（Morphオブジェクト）のリスト（morphs），
 * 係り先文節インデックス番号（dst），係り元文節インデックス番号のリスト（srcs）をメンバ変数に持つこととする．
 * さらに，入力テキストのCaboChaの解析結果を読み込み，１文をChunkオブジェクトのリストとして表現し，
 * 8文目の文節の文字列と係り先を表示せよ．第5章の残りの問題では，ここで作ったプログラムを活用せよ．
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
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
	for (auto itr = morphs.begin(); itr != morphs.end(); ++itr)
		ss << itr->surface;
	return ss.str();
}

int main(void)
{
	std::shared_ptr<CaboCha::Parser> parser = std::shared_ptr<CaboCha::Parser>(CaboCha::createParser("-f3"));
	int count = 0;

	std::ifstream ifs("neko.txt");
	for (std::string line; std::getline(ifs, line); ) {
		if (++count == 8) {
			const std::string cabocha_xml = parser->parseToString(line.c_str());

			std::vector<Chunk> chunks;
			rapidxml::xml_document<> doc;
			doc.parse<0>((char*)cabocha_xml.c_str());
			for (rapidxml::xml_node<> *p = doc.first_node()->first_node(); p; p = p->next_sibling())
				chunks.push_back(parseChunk(p));

			for (size_t i = 0; i < chunks.size(); ++i) {
				if (chunks[i].dst != -1)
					chunks[chunks[i].dst].srcs.push_back(i);
			}

			for (size_t i = 0; i < chunks.size(); ++i)
				std::cout << "[" << i << "] " << getBunsetsu(chunks[i].morphs) << " " << chunks[i].dst << std::endl;
			break;
		}
	}
}
