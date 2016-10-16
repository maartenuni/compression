
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include "HuffmanStats.h"
#include "HuffmanTree.h"
#include "BitWriter.h"

using namespace std;

std::string file("compressed.txt");

void premature_exit(const string& start, int errornum)
{
    ostringstream msg;
    msg << start << ": " << strerror(errornum);
    cerr << msg.str() << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
    std::vector<uint8_t> compressed;

    if (argc == 2) {
        file = argv[1];
    }

    // read the input
    ifstream in(file, ios::binary | ios::ate);
    auto insz = in.tellg();
    in.seekg(0);
    compressed.resize(insz);
    in.read(reinterpret_cast<char*>(compressed.data()), insz);

    if(!in) {
        int err = errno;
        ostringstream s;
        s << "Unable to open \"" << file << "\"";
        premature_exit(s.str() , err);
    }

    // construct huffman tree
    std::string input;
    int c;
    while ((c = getchar()) != EOF )
        input.push_back(char(c));

    HuffmanStats hs(input);
    HuffmanTree htree(hs);

    std::string output = htree.decompress(compressed);
    cout << output;

    return 0;
}
