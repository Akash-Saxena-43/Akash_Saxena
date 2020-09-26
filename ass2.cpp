#include <bits/stdc++.h> 
using namespace std; 



// Structure of Trie 
struct Trie { 
	bool isLast; 
	unordered_map<char, Trie*> map; 
	int freq; 
    Trie *parent;
    char ch;
}; 
vector<Trie*> mp;




// function for creating new tries
Trie* makeNode(char ch, Trie *parent) 
{ 
	Trie* Node = new Trie; 
	Node->isLast = false; 
    Node->parent = parent;
    Node->ch = ch;
	return Node; 
} 




// Function to Insert a students name  with their frequencies
// in the dictionary for building trie 

void InsertionOfWords(Trie*& rootNode, const string& str, 
			const int& freq) 
{ 

	// If rootNode is null 
	if (rootNode == NULL) 
		rootNode = makeNode(0, NULL); 

	Trie* t = rootNode; 

	for (int i = 0; i < str.length(); i++) 
    { 
		char x = str[i]; 


		//to make the new  node if there is no path 
		if (t->map.find(x) == t->map.end()) 
			t->map[x] = makeNode(x, t); 

		t = t->map[x]; 
	} 

	// Mark last name and store the meaning 
	t->isLast = true; 
	t->freq = freq; 
    mp.push_back(t);
} 




// Function to find a student in the Trie and return its freq if it exists

 string find(Trie * rootNode, int ind)
 {
     string word;
     if (ind >= mp.size()) {
         return word;
     }
     Trie *node = mp[ind];
     while(node->parent != NULL) {
         word += node->ch;
         node = node->parent;
     }   
     reverse(word.begin(), word.end());
     return word;
 }

//  This is derived function
 
int main() 
{ 
	Trie* rootNode = NULL; 


	// Build the dictionary 
	ifstream myFile;
	myFile.open("EnglishDictionary.csv");
	string freq;
    string  words, line;

	vector<pair<string, int>> v;
	int f;

	while(getline(myFile, line))
    {
		stringstream st(line);
		getline(st, words, ',');
		getline(st, freq, ',');
		f = stoi(freq);
		v.push_back({words,f});
	}

	for(auto it : v){
		InsertionOfWords(rootNode, it.first, it.second);
	}
	
    int query;
    cin >> query;
    string answer = find(rootNode, query);
	if(answer.size() > 0) cout  << answer << endl;
	else cout << "Not found\n";

	return 0;              
}