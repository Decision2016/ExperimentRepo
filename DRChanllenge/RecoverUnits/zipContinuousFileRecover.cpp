#include<string>
#include<iostream>
#include<cstdio>
using namespace std;

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

const int READ_BYTE_LEN = 8;
const int READ_BYTE_COUNT = 1;

// seek 504 bytes after read 8 bytes
const int SECTOR_SIZE = 512;

const int SEEK_FROM_NOW = 1;

const string path = "../DiskImage/dfrws-2006-challenge.raw";
const string base_path = "../RecoverFiles/%d.html";
const uint64_t htmlHeadEnter = 0x5954434F44213C0A;
const uint64_t htmlHeadNoEnter = 0x505954434F44213C;
const uint64_t htmlLeaf = 0x3E6C6D74682F3C0A;
const uint64_t htmlLeafBigger = 0x0A0D3E4C4D54482F;
const uint64_t fileSize = 0x2FAEFFF;

uint64_t value;
uint64_t head_pos = 0;
uint64_t leaf_pos = 0;
uint64_t lastestPosition = 0;
bool headExisted = true;
bool hasEnter = false;

int fileCount = 0;

inline uint64_t readFile(FILE *fp) {
    uint64_t result;
    fread(&result, READ_BYTE_LEN, READ_BYTE_COUNT, fp);
    fseek(fp, -8, SEEK_FROM_NOW);
    return result;
}

void seek_head(FILE *fp) {
    value = readFile(fp);
    uint64_t count = lastestPosition;

    // check if head is right
    if (value == htmlHeadNoEnter || value == htmlHeadEnter) {
        head_pos = 0;
        return ;
    }
    // seek all sector`s header
    while (count <= fileSize) {
        fseek(fp, SECTOR_SIZE, SEEK_FROM_NOW);
        count += SECTOR_SIZE;
        uint64_t nowValue = readFile(fp);
        if (htmlHeadNoEnter == nowValue || htmlHeadEnter == nowValue) {
            if (count <= head_pos) continue;
            else {
                hasEnter = nowValue == htmlHeadEnter ? true : false;
                head_pos = count;
                break ;
            }
        }
    }
    if (count > fileSize) headExisted = false;
    //return to head
    fseek(fp, head_pos, 0);
}

void seek_leaf(FILE *fp) {
    value = readFile(fp);

    if (value == htmlLeaf) {
        leaf_pos = head_pos;
        return ;
    }

    uint64_t count = head_pos;
    while (count <= fileSize) {
        fseek(fp, 1, SEEK_FROM_NOW);
        uint64_t nowValue = readFile(fp);
        ++count;
        if (htmlLeaf == nowValue || htmlLeafBigger == nowValue) {
            if (count <= leaf_pos) continue;
            else {
                leaf_pos = count + 7;
                break;
            }
        }
    }

    fseek(fp, head_pos, 0);
}

void recoverHtmlFile(int headPosition, int leafPosition, FILE *fp) {
    char *save_path = new char[100];
    sprintf(save_path, base_path.c_str(), fileCount++);
    // string save_path = base_path + itoa(1) + ".html";
    uint8_t *buffer = new uint8_t[leafPosition - headPosition + 1];
    int file_size = leafPosition - headPosition + 1;
    FILE *wfp = fopen(save_path, "wb");
    fseek(fp, headPosition, 0);
    fseek(wfp, 0, 0);
    fread(buffer, 1, file_size, fp);
    fwrite(buffer, 1, file_size, wfp);
    delete buffer;
    delete save_path;
    buffer = nullptr;
    save_path = nullptr;
    fclose(wfp);
}

int main() {
    FILE *fp = fopen(path.c_str(), "rb");
    while (true) {
        fseek(fp, lastestPosition, 0);
        seek_head(fp);
        if (!headExisted) break;
        cout<<"Find file header:"<<head_pos<<endl;
        fseek(fp, head_pos, 0);
        seek_leaf(fp);
        cout<<"Find file leaf:"<<leaf_pos<<endl;
        if (leaf_pos <= head_pos) break;
        recoverHtmlFile(head_pos, leaf_pos, fp);
        lastestPosition = (leaf_pos / SECTOR_SIZE + 1) * SECTOR_SIZE;
        cout<<"recovered one file"<<endl;
    }
    fclose(fp);
    return 0;
}
