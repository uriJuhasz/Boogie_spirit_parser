#include <iostream>
#include <string>
#include <fstream>
#include "front_end/Boogie/Parser.h"

using namespace std;

const string boogieFileName = "C:\\work\\Slicer\\test\\Chalice\\AVLTree\\AVLTree.bpl";

int main() {
    cout << "Start" << endl;

    ifstream boogieFile(boogieFileName);
/*
    front_end::Boogie::Parser parser(boogieFile);

    parser.parse();
*/
    parseTest(boogieFile);
    cout << "End" << endl;
    return 0;
}

