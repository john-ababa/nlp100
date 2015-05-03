/* ============================================================================
 * 40. 係り受け解析結果の読み込み（形態素）
 *
 * 形態素を表すクラスMorphを実装せよ．このクラスは表層形（surface），基本形（base），
 * 品詞（pos），品詞細分類1（pos1）をメンバ変数に持つこととする．
 * さらに，CaboChaの解析結果（neko.txt.cabocha）を読み込み，
 * 各文をMorphオブジェクトのリストとして表現し，3文目の形態素列を表示せよ．
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cabocha.h>
#include <rapidxml/rapidxml.hpp>

class Morph {
	const std::string surface;
	const std::string base;
	const std::string pos;
	const std::string pos1;
public:
	Morph(const std::string& _surface, const std::string& _base, const std::string& _pos, const std::string& _pos1)
		: surface(_surface), base(_base), pos(_pos), pos1(_pos1) { ; }
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
	std::vector<Morph> vec;
	for (rapidxml::xml_node<> *tok = node->first_node(); tok; tok = tok->next_sibling()) {
		for (rapidxml::xml_attribute<> *attr = tok->first_attribute(); attr; attr = attr->next_attribute()) {
			if (attr->name() == std::string("feature")) {
				const std::string surface = tok->value();
				const std::string base = splitWord(attr->value(), 7);
				const std::string pos =  splitWord(attr->value(), 1);
				const std::string pos1 = splitWord(attr->value(), 2);
				vec.push_back(Morph(surface, base, pos, pos1));
			}
		}
	}
	return vec;
}

int main(void)
{
	std::shared_ptr<CaboCha::Parser> parser = std::shared_ptr<CaboCha::Parser>(CaboCha::createParser("-f3"));

	std::ifstream ifs("neko.txt");
	for (std::string line; std::getline(ifs, line); ) {
		const std::string cabocha_xml = parser->parseToString(line.c_str());

		rapidxml::xml_document<> doc;
		doc.parse<0>((char*)cabocha_xml.c_str());
		for (rapidxml::xml_node<> *p = doc.first_node()->first_node(); p; p = p->next_sibling()) {
			std::vector<Morph> morph = parseTok(p);
			// TODO: 3文目の形態素列？
		}
	}
}
