#include <bits/stdc++.h>
#include "huffmantree.hpp"
#include "serialization.hpp"
//#include "readwrite.hpp"

using namespace std;

map<int, string> encTable;

map<string, int> invTable;

int height;

int width;


string bits = "";

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    vector<uint8_t> arr = readpgm(width, height, argv[1]);

    CountFreq(arr, height * width);

    encTable = HuffmanCodes(freq);

    serialize(encTable, arr, width, height, freq);

	cout<<"Comprisson Done"<<endl;
  }
  else if(argc==4)
  {
    deserialize(argv[1], argv[3], freq, bits, width, height);

    encTable = HuffmanCodes(freq);

    invTable = InverseCode(encTable);

    vector<uint8_t> newimg = decode(bits, invTable, width, height);

    writepgm(newimg, width, height);

	cout<<"Decomprisson Done"<<endl;
  }

  else
  {
    	cout<<"Invalid usage"<<endl;
  }
  
}
