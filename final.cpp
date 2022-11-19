#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
    // Create a file object
    ofstream file;
    // Open the file
    file.open("test.txt");
    // Write to the file
    file << "Hello World 2" << endl;
    // Close the file
    file.close();
};