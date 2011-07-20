#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int getTransformedCharValue(char c){
	int val = c;
	val = val-97;
	return val;
}


class Node{
	public:
		int words;
		int prefixes;
		Node* references[26];

		Node(){
			words = 0;
			prefixes = 0;
			for(int i=0;i < 26;i++){
				references[i] = NULL;
			}
		}

		bool hasReferenceTo(char c){
			int val = getTransformedCharValue(c);
			if(references[val] != NULL){
				return true;
			}
			return false;
		}
};


class Trie{
	private:
		Node root;
		void _addWord(Node &n, string word);
		int _countPrefix(Node &n, string prefix);
		int _countWord(Node &n, string word);
	public:
		Trie();
		void addWord(string word);
		int countPrefix(string prefix);
		int countWord(string word);
};

Trie::Trie(){
	root = Node();
}

void Trie::_addWord(Node &n, string word){
	if(word.length() == 0){
		n.words += 1;
		return;
	}
	n.prefixes += 1;
	char first = word[0];
	int index = getTransformedCharValue(first);
	if (!n.hasReferenceTo(first)){
		Node* new_n = new Node();
		n.references[index] = new_n;
	}
	_addWord(*n.references[index],word.erase(0,1));
}

int Trie::_countWord(Node &n, string word){
	if(word.length() == 0){
		return n.words;
	}
	char first = word[0];
	int index = getTransformedCharValue(first);
	if(n.references[index] == NULL){
		return 0;
	}
	else{
		return _countWord(*n.references[index],word.erase(0,1));
	}

}

int Trie::_countPrefix(Node &n, string word){
	if(word.length() == 0){
		return n.prefixes;
	}
	char first = word[0];
	int index = getTransformedCharValue(first);
	if(n.references[index] == NULL){
		return 0;
	}
	else{
		return _countPrefix(*n.references[index],word.erase(0,1));
	}

}

void Trie::addWord(string word){
	transform(word.begin(),word.end(),word.begin(),::tolower);
	_addWord(root,word);
}

int Trie::countPrefix(string prefix){
	transform(prefix.begin(),prefix.end(),prefix.begin(),::tolower);
	return _countPrefix(root,prefix);
}

int Trie::countWord(string word){
	transform(word.begin(),word.end(),word.begin(),::tolower);
	return _countWord(root,word);
}

int main() {
	Trie t;
	string s1("Suvash");
	string s2("Surendra");
	string s3("Suvash");
	string prefix("Su");
	t.addWord(s3);
	t.addWord(s1);
	t.addWord(s1);
	t.addWord(s2);
	cout << "word count for " << s1 << " is " << t.countWord(s1)<<endl;
	cout << "word count for " << s2 << " is " << t.countWord(s2)<<endl;
	cout << "prefix count for " << prefix << "is " << t.countPrefix(prefix)<<endl;

	return 0;
}
