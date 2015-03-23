/* ============================================================================
 * 07. テンプレートによる文生成
 * 引数x, y, zを受け取り「x時のyはz」という文字列を返す関数を実装せよ．
 * さらに，x=12, y="気温", z=22.4として，実行結果を確認せよ．
 * ========================================================================= */
#include <iostream>
#include <sstream>
#include <string>

std::string xyz(const int x, const std::string& y, const double z)
{
	std::stringstream ss;
	ss << x << "時の" << y << "は" << z;
	return ss.str();
}

int main(void)
{
	std::cout << xyz(12, "気温", 22.4) << std::endl;
}
