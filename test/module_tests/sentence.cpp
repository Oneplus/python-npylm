#include <boost/functional/hash.hpp>
#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <string>
#include "../../src/npylm/common.h"
#include "../../src/npylm/hash.h"
#include "../../src/npylm/sentence.h"
using namespace npylm;
using std::cout;
using std::flush;
using std::endl;

void test_get_substr_word_id(){
	std::wstring sentence_str = L"本論文 では, 教師 データ や 辞書 を 必要 とせず, あらゆる言語に適用できる教師なし形態素解析器および言語モデルを提案する. 観測された文字列を, 文字 nグラム-単語 nグラムをノンパラメトリックベイズ法の枠組で統合した確率モデルからの出力とみなし, MCMC 法と動的計画法を用いて, 繰り返し隠れた「単語」を推定する. 提案法は, あらゆる言語の生文字列から直接, 全く知識なしに Kneser-Ney と同等に高精度にスムージングされ, 未知語のない nグラム言語モデルを構築する方法とみなすこともできる.話し言葉や古文を含む日本語, および中国語単語分割の標準的なデータセットでの実験により, 提案法の有効性および効率性を確認した.";
	Sentence* sentence = new Sentence(sentence_str);
	for(int t = 0;t < sentence_str.size();t++){
		for(int k = 0;k < std::min((size_t)t, sentence_str.size());k++){
			size_t hash = hash_substring(sentence_str, t - k, t);
			std::wstring substr(sentence_str.begin() + t - k, sentence_str.begin() + t + 1);
			size_t _hash = hash_wstring(substr);
			size_t __hash = sentence->get_substr_word_id(t - k, t);
			assert(hash == _hash && _hash == __hash);
		}
	}
}

void test_get_substr_word_str(){
	std::wstring sentence_str = L"本論文 では, 教師 データ や 辞書 を 必要 とせず, あらゆる言語に適用できる教師なし形態素解析器および言語モデルを提案する. 観測された文字列を, 文字 nグラム-単語 nグラムをノンパラメトリックベイズ法の枠組で統合した確率モデルからの出力とみなし, MCMC 法と動的計画法を用いて, 繰り返し隠れた「単語」を推定する. 提案法は, あらゆる言語の生文字列から直接, 全く知識なしに Kneser-Ney と同等に高精度にスムージングされ, 未知語のない nグラム言語モデルを構築する方法とみなすこともできる.話し言葉や古文を含む日本語, および中国語単語分割の標準的なデータセットでの実験により, 提案法の有効性および効率性を確認した.";
	Sentence* sentence = new Sentence(sentence_str);
	for(int t = 0;t < sentence_str.size();t++){
		for(int k = 0;k < std::min((size_t)t, sentence_str.size());k++){
			std::wstring substr(sentence_str.begin() + t - k, sentence_str.begin() + t + 1);
			std::wstring _substr = sentence->get_substr_word_str(t - k, t);
			assert(substr.compare(_substr) == 0);
		}
	}
}

int main(){
	test_get_substr_word_id();
	cout << "OK" << endl;
	test_get_substr_word_str();
	cout << "OK" << endl;
	return 0;
}