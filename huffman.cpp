
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

    if (argc == 2) {
        file = argv[1];
    }

    ofstream out(file);
    if(!out) {
        int err = errno;
        ostringstream s;
        s << "Unable to open \"" << file << "\"";
        premature_exit(s.str() , err);
    }

    std::string input;
    int c;
    while ((c = getchar()) != EOF )
        input.push_back(char(c));

    HuffmanStats hs(input);

    HuffmanTree htree(hs);
    std::vector<HNodePtr> codebook = htree.codebook();
    BitWriter writer;
    for (const auto& c : input) {
        HNodePtr ptr;
        auto cmp = [](const HNodePtr& ptr, char c){
                return ptr->repr() < string(&c, 1);
            };
        auto it = std::lower_bound(
                codebook.begin(),
                codebook.end(),
                c,
                cmp
                );
        if (it == codebook.end())
            return EXIT_FAILURE;
        ptr = *it;
        writer.write(ptr->bits(), ptr->length());
    }

    out << writer;

    return 0;
}
