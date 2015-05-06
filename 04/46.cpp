/* ============================================================================
 * 46. 動詞の格フレーム情報の抽出
 *
 * 45のプログラムを改変し，述語と格パターンに続けて項（述語に係っている文節そのもの）を
 * タブ区切り形式で出力せよ．45の仕様に加えて，以下の仕様を満たすようにせよ．
 *
 * - 項は述語に係っている文節の単語列とする（末尾の助詞を取り除く必要はない）
 * - 述語に係る文節が複数あるときは，助詞と同一の基準・順序でスペース区切りで並べる
 *
 * 「吾輩はここで始めて人間というものを見た」という例文（neko.txt.cabochaの8文目）を考える．
 * この文は「始める」と「見る」の２つの動詞を含み，「始める」に係る文節は「ここで」，「見る」に
 * 係る文節は「吾輩は」と「ものを」と解析された場合は，次のような出力になるはずである．
 *
 * 始める  で      ここで
 * 見る    は を   吾輩は ものを
 * ========================================================================= */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <map>
#include <set>
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

std::string getBunsetsu(const std::vector<Morph>& morphs)
{
	std::stringstream ss;
	for (auto itr = morphs.begin(); itr != morphs.end(); ++itr) {
		if (itr->pos != "記号")
			ss << itr->surface;
	}
	return ss.str();
}

std::string show(const std::vector<Chunk>& chunks)
{
	std::stringstream ss1, ss2;

	std::multimap<std::string, Chunk> mm;
	for (auto itr = chunks.begin(); itr != chunks.end(); ++itr)
		mm.insert(std::make_pair(itr->morphs.back().surface, *itr));
	
	for (auto itr = mm.begin(); itr != mm.end(); ++itr) {
		ss1 << itr->first << " ";
		ss2 << getBunsetsu(itr->second.morphs) << " ";
	}

	return ss1.str() + " " + ss2.str();
}

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

template<class Map, class Key, class Val>
void addWord(Map& m, const Key& k, const Val& v)
{
	typename Map::iterator it = m.lower_bound(k);
	if (it != m.end() && !m.key_comp()(k, it->first)) {
		it->second.push_back(v);
	} else {
		std::vector<Val> vec; vec.push_back(v);
		m.insert(it, typename Map::value_type(k, vec));
	}
}

int main(void)
{
	std::shared_ptr<CaboCha::Parser> parser = std::shared_ptr<CaboCha::Parser>(CaboCha::createParser("-f3"));
	std::multimap<std::string, std::vector<Chunk> > mm;

	std::ifstream ifs("neko.txt");
	for (std::string line; std::getline(ifs, line); ) {
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

		for (size_t i = 0; i < chunks.size(); ++i) {
			if (chunks[i].morphs.front().pos == "動詞" && chunks[i].srcs.size() != 0) {
				for (auto itr = chunks[i].srcs.begin(); itr != chunks[i].srcs.end(); ++itr) {
					if (chunks[*itr].morphs.back().pos == "助詞")
						addWord(mm, chunks[i].morphs.front().base, chunks[*itr]);
				}
			}
		}
	}

	for (auto itr = mm.begin(); itr != mm.end(); ++itr)
		std::cout << itr->first << "\t" << show(itr->second) << std::endl;
}
