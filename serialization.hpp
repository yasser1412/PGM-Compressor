#include <bits/stdc++.h>
using namespace std;

void serialize(map<int, string> &enc_pixTable, vector<uint8_t> PixelArray, const int width, const int height, vector<int> freq)
{
    string bits = "";
    string code = "";
    for (int i = 0; i < width * height; i++)
    {
        bits += enc_pixTable[int(PixelArray[i])];
        //  cout<<bits.size()<<endl;
    }
    int paddingBits = 8 - (bits.size() % 8);
    ofstream outenc("image.enc"); //Creating file
    outenc << width << " " << height << char(255) << char(paddingBits);

    for (int i = 0; i < bits.size(); i++)
    {
        code += bits[i];
        if (code.size() % 8 == 0)
        {
            int intcode = stoi(code, 0, 2);
            char strcode = (char)intcode;
            outenc << strcode;
            code = "";
        }
    }
    for (int i = 0; i < paddingBits; i++)
        code += '0';
    int intcode = stoi(code, 0, 2);
    char strcode = (char)intcode;
    outenc << strcode;
    outenc.close();

    ofstream outfrq("image.frq");
    for (int i = 0; i < 256; i++)
    {
        outfrq << freq[i]<<" ";
    }
    outfrq.close();
}

void deserialize(string encfile, string frqfile, vector<int> &freq, string &bits, int &width, int &height)
{
    //for frequency table
    ifstream infreq(frqfile);
    int frequancy;
    int i = 0;
    for (int i = 0; i < 256; i++)
    {
        infreq >> frequancy;

        freq[i] = frequancy;
    }
    infreq.close();

    //for encoded image
    unsigned char uc;
    char c;
    string line = "";
    ifstream inenc(encfile);
    inenc >> height >> width;
    

    //Getting the padding bits number to remove them later
    inenc.get(c);
    uc = (unsigned char)c;
    int charDes = int(uc);
    int paddingBits = charDes;

    while (inenc.get(c))
    {
        charDes = int(c);
        bitset<8> x(charDes);
        bits += x.to_string();
    }
    //Removing padding bits
    for (int i = 0; i < paddingBits; i++)
        bits.pop_back();
    inenc.close();
}
