#include <iostream>
#include <fstream>
#include<string.h>
using namespace std;

class TrieNode{
public:
    int frequency;
    TrieNode* data[26];
    bool end=false;
    TrieNode() {
        frequency = 0;
        for(auto &i : data) {
            i = nullptr;
        }
    }
};
void insert(TrieNode* root, const string& key, int freq) {
    auto* new_node = new TrieNode;
    for(char i : key) {
        int index = i - 'a';
        if(!root->data[index]) {
            root->data[index] = new_node;
        }
        root = root->data[index];
    }
    root->frequency = freq;
    root->end=true;
}
void search(TrieNode* root, const string& key) {
    for(char i : key) {
        int index = i - 'a';
        if(!root->data[index]) {
            cout << "No\n";
            return;
        }
        root = root->data[index];
    }
    if(root != nullptr && root->frequency) {
        cout << "YES, " << root->frequency<<"\n";
    }
}
int main() {
   
    TrieNode *root = new TrieNode;
    ifstream fin;
    fin.open("EnglishDictionary.csv");
    string line;
    
    while (fin) {
        string current, freq;
        int i = 0;
        getline(fin,line);
        while(line[i] != ',') {
            current += line[i];
            ++i;
        }
        ++i;
        while(line[i]) {
            freq += line[i];
            ++i;
        }
        insert(root, current, stoi(freq));
        line.clear();
    }
    string key;
    cin>>key;
    search(root, key);
    return 0;
}