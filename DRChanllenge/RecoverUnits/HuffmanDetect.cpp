#include<string>
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

const int READ_BYTE_LEN = 8;
const int READ_BYTE_COUNT = 1;

// seek 504 bytes after read 8 bytes
const int SECTOR_SIZE = 512;

class HuffmanTree {
private:
    unordered_map<int, int> mp;
public:
    HuffmanTree();
    HuffmanTree(uint8_t* data);
}hfTrees[4];

int main() {

}
