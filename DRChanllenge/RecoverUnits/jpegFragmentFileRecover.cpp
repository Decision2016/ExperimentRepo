#include<string>
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

const int READ_BYTE_LEN = 8;
const int READ_BYTE_COUNT = 1;

// seek 504 bytes after read 8 bytes
const int SECTOR_SIZE = 512;

const int SEEK_FROM_NOW = 1;

const string path = "../DiskImage/dfrws-2006-challenge.raw";
const string base_path = "../RecoverFiles/pics/%d.jpg";
const string frag_path = "../RecoverFragmentFiles/pics/%d.jpg";
const uint64_t jpegHead = 0x464A1000E0FFD8FF;
const uint16_t jpegLeaf = 0xD9FF;
const uint64_t fileSize = 0x2FAEFFF;

uint64_t value;
uint64_t head_pos = 0;
uint64_t leaf_pos = 0;
uint64_t lastestPosition = 0;
bool headExisted = true;
bool hasEnter = false;

int fileCount = 0;

vector<uint64_t> headPositions, leafPositions;

void tryCutSector(int headPosition, int leafPosition, FILE *fp);

inline uint64_t readFile(FILE *fp) {
    uint64_t result;
    fread(&result, READ_BYTE_LEN, READ_BYTE_COUNT, fp);
    fseek(fp, -8, SEEK_FROM_NOW);
    return result;
}

inline uint16_t readFile2byte(FILE *fp) {
    uint16_t result;
    fread(&result, 2, READ_BYTE_COUNT, fp);
    fseek(fp, -2, SEEK_FROM_NOW);
    return result;
}

void seek_all_head(FILE *fp) {
    value = readFile(fp);
    uint64_t count = lastestPosition;

    // check if head is right
    if (value == jpegHead) {
        head_pos = 0;
        return ;
    }
    // seek all sector`s header
    while (count <= fileSize) {
        fseek(fp, SECTOR_SIZE, SEEK_FROM_NOW);
        count += SECTOR_SIZE;
        uint64_t nowValue = readFile(fp);
        if (nowValue == jpegHead) {
                head_pos = count;
                headPositions.push_back(head_pos);
        }
    }
    if (count > fileSize) headExisted = false;
    //return to head
    fseek(fp, 0, 0);
}

void seek_all_leaf(FILE *fp) {
    fseek(fp, 0, 0);
    uint16_t value_16 = readFile2byte(fp);

    if (value_16 == jpegLeaf) {
        leaf_pos = head_pos;
        return ;
    }

    uint64_t count = 0;
    while (count <= fileSize) {
        fseek(fp, 1, SEEK_FROM_NOW);
        uint16_t nowValue = readFile2byte(fp);
        ++count;
        if (jpegLeaf == nowValue) {
                leaf_pos = count + 1;
                leafPositions.push_back(leaf_pos);
                cout<<dec<<"leaf count:"<<leafPositions.size()<<endl;
        }
    }

    fseek(fp, 0, 0);
}

void recoverHtmlFile(int headPosition, int leafPosition, FILE *fp) {
    int sectors = (leafPosition / SECTOR_SIZE + 1) - (headPosition / SECTOR_SIZE);
    cout<<"header:"<<hex<<headPosition<<"    footer:"<<leafPosition<<"    sectors:"<<dec<<sectors<<endl;
    if (sectors <=1000) {
        cout<<"Trying find fragment file..."<<endl;

        tryCutSector(headPosition, leafPosition, fp);
    }

    char *save_path = new char[100];
    sprintf(save_path, base_path.c_str(), fileCount++);
    // string save_path = base_path + itoa(1) + ".html";
    uint8_t *buffer = new uint8_t[leafPosition - headPosition + 1];
    uint64_t file_size = leafPosition - headPosition + 1;
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

void tryCutSector(int headPosition, int leafPosition, FILE *fp) {
    int beginSector = headPosition / SECTOR_SIZE + 1;
    int endSector = leafPosition / SECTOR_SIZE - 1;

    char *save_path = new char[100];
    uint8_t *buffer = new uint8_t[leafPosition - headPosition + 1];

    for (int i = beginSector; i < endSector; ++i) {
        // select start delete sector
        for (int j = i + 1; j <= endSector; ++j) {
            // select end delete sector
            int firstEndPosition = i * SECTOR_SIZE - 1;
            int secondStartPosition = j * SECTOR_SIZE;
            // file count
            sprintf(save_path, frag_path.c_str(), fileCount++);
            FILE *wfp = fopen(save_path, "wb");
            // first file size
            int firstFileSize = firstEndPosition - headPosition + 1;
            // second file size
            int secondFileSize = leafPosition - secondStartPosition + 1;
            // output first part of file
            fseek(fp, headPosition, 0);
            fread(buffer, 1, firstFileSize, fp);
            fwrite(buffer, 1, firstFileSize, wfp);
            // output second part of file
            fseek(fp, secondStartPosition, 0);
            fread(buffer, 1, secondFileSize, fp);
            fwrite(buffer, 1, secondFileSize, wfp);
            fclose(wfp);
        }
    }
    delete buffer;
    delete save_path;
}

int main() {
    FILE *fp = fopen(path.c_str(), "rb");
    /*
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
        headPositions.push_back(head_pos);
        leafPositions.push_back(leaf_pos);
        lastestPosition = (leaf_pos / SECTOR_SIZE + 1) * SECTOR_SIZE;
        cout<<"recovered one file"<<endl;
    }
    */
    cout<<"Trying seek all header"<<endl;
    seek_all_head(fp);
    cout<<"Trying seek all leaf"<<endl;
    seek_all_leaf(fp);
    cout<<"Try recover with all position..."<<endl;
    for (uint64_t head : headPositions) {
        for (uint64_t leaf : leafPositions) {
            if (leaf > head) recoverHtmlFile(head, leaf, fp);
        }
    }
    fclose(fp);
    return 0;
}
