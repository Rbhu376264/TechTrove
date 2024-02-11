#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include "huffman.h"
using namespace std;

// Complete
RawTextVector AsciiHexIO::read(const char* filename)
{
    RawTextVector text;
    ifstream ifile(filename);
    if(ifile.fail()){
        throw std::invalid_argument("Bad input filename");
    }
    while(!ifile.fail()) {
        char c;
        string word;
        for(int i=0; i < 4; i++){
            ifile >> c;
            if(ifile.fail()){
                if(i > 0) {
                    throw std::runtime_error(
                        "Bad file format...did not find multiple of 4 hex characters");
                }
                else {
                    break; // normal exit
                }
            }
            else {
                word += c;
            }
        }
        if(word.size() == 4) {
            text.push_back(word);
        }
    }
    ifile.close();
    return text;
}

// Complete
void AsciiHexIO::write(const char* filename, const RawTextVector&  text)
{
    const size_t NUM_WORDS_PER_LINE = 8;
    ofstream ofile(filename);
    if(ofile.fail()){
        throw std::runtime_error("Unable to open output file");
    }
    size_t i = 0;
    for( const auto & word : text ){
        ofile << word;
        if(i % NUM_WORDS_PER_LINE != NUM_WORDS_PER_LINE-1 ){
            ofile << " ";
        }
        else {
            ofile << endl;
        }
        i++;
    }
    ofile.close();
}

// Complete
void AsciiHuffmanIo::writeCodedText(
    const char* filename, 
    const CompressedData& inText, 
    const CodeKeyMap& code)
{
    ofstream ofile(filename);
    ofile << code.size() << endl;
    // copy from map to vector so we can sort
    typedef pair<string,string> StrStrPair;
    vector< StrStrPair > codesToSort(code.begin(), code.end());
    std::sort(
        codesToSort.begin(), codesToSort.end(), 
        [] (const StrStrPair& s1, const StrStrPair& s2) -> bool
            { return (s1.first.size() < s2.first.size()) ||
                     (s1.first.size() == s2.first.size() && s1.first < s2.first); } );
    for(const auto& pair : codesToSort) {
        ofile << pair.first << " " << pair.second << endl;
    }
    ofile << inText << endl;
    ofile.close();
}

// To be completed
void AsciiHuffmanIo::readCodedText(
    const char* filename, 
    CompressedData& outText, 
    CodeKeyMap& code)
{
    // clear old contents of the output parameters that this function
    // should fill in
    code.clear();
    outText.clear();

    // Complete the code below
    ifstream ifile(filename);
    if(ifile.fail()){
        throw runtime_error("Cannot open file");
    }

    int size;
    ifile>>size;
    
    string line1, line2;
    int inc = 0;

    while(inc != size)
    {
        ifile>>line1>>line2;
        map<string,string>::iterator it = code.find(line1);

        if(it == code.end())
        {
            code.insert(make_pair(line1,line2));
        }
        
        inc++;

    }

    ifile>>outText;





}

// To be completed
void HuffmanCoder::compress(
    const RawTextVector& inText, 
    CompressedData& outText, 
    CodeKeyMap& codes)
{
    // Clear old contents of the output parameters that this function should fill in
    codes.clear();
    outText.clear();

    // Add your code here
    KeyFrequencyMap compressmap;
    for(unsigned int i = 0; i<inText.size(); i++)
    {
        map<string,size_t>::iterator it = compressmap.find(inText[i]);

        if(it == compressmap.end())
        {
            compressmap.insert(make_pair(inText[i],1));
        }
        else
        {
            it->second++;
        }

    }
    Heap<HeapItem> sheap(2);

    for(map<string,size_t>::iterator it = compressmap.begin(); it!= compressmap.end(); ++it)
    {
        HeapItem val;

        val.total = it->second;
        val.keys.insert(it->first);

        sheap.push(val);

        codes.insert(make_pair(it->first,""));
    }

    while(sheap.size()>=2)
    {
        HeapItem item = sheap.top();
        for(set<string>::iterator it = item.keys.begin(); it != item.keys.end(); ++it)
        {
            map<string,string>::iterator it_1 = codes.find(*it);

            if(it_1 != codes.end())
            {
                it_1->second = '0' + it_1->second;
            }
        }

        sheap.pop();

        HeapItem item1 = sheap.top();

        for(set<string>::iterator it = item1.keys.begin(); it != item1.keys.end(); ++it)
        {
            map<string,string>::iterator it_1 = codes.find(*it);

            if(it_1 != codes.end())
            {
                it_1->second = '1' + it_1->second;
            }
        }

        sheap.pop();

        HeapItem another_one;

        another_one.total = item.total + item1.total;
        another_one.keys = item.keys;

        set<string> copy = item1.keys;
        for(set<string>::iterator it = copy.begin(); it != copy.end(); ++it)
        {
            another_one.keys.insert(*it);

        }

        sheap.push(another_one);



    }
    for(unsigned int i = 0; i<inText.size(); i++)
    {
        map<string,string>::iterator it = codes.find(inText[i]);

        if(it != codes.end())
        {
            outText += it->second;
        }

    }

    CodeKeyMap tempmap;

    for(map<string,string>::iterator it = codes.begin(); it != codes.end(); ++it)
    {
        tempmap.insert(make_pair(it->second,it->first));


    }

    codes = tempmap;
}

// To be completed
void HuffmanCoder::decompress(
    const CompressedData& inText, 
    const CodeKeyMap& codes, 
    RawTextVector& outText)
{
    // Clear old contents of the output parameter
    outText.clear();
    // Add your code here
    string inputCode;

    // create the decompressed text by reading one char at a time and, 
    // since Huffman codes are prefix codes, once the string matches 
    // a key in the code map, just substitute the word and start again
    
    for(unsigned int i = 0; i<inText.size(); i++)
    {
        inputCode += inText[i];
        map<string,string>::const_iterator it = codes.find(inputCode);

        if(it != codes.end())
        {
            outText.push_back(it->second);
            inputCode = "";
        }

    }




}

// Complete
double HuffmanCoder::ratio(const RawTextVector& inText, const CompressedData& outText, const CodeKeyMap& codes)
{
    // 2 bytes per entry
    double rawSize = 2 * inText.size(); 
    // each character in outText is a bit so convert to bytes
    double compressedSize = (outText.size() + 7) / 8; 
    for(const auto& pair : codes) {
        compressedSize += 2 + pair.first.size()+1; // 2 bytes for 16-bit val + string of 1,0 + null char
    }
    cout << "Original size (bytes): " << rawSize << endl;
 
    cout << "Compressed size (bytes): " << compressedSize << endl;
    double compressionRatio = rawSize / compressedSize;
    cout << "Compression ratio: " << setprecision(2) << fixed << compressionRatio << endl;
    return compressionRatio;
}
