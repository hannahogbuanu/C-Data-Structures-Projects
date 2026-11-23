#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Image.hpp"
#include "processing.hpp"
using namespace std;
static void print_usage(){
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
}
int main(int argc, char *argv[]) {
    if (argc != 4 && argc != 5 ){
        print_usage();
        return 1;
    }
    string ifilename = argv[1];
    string ofilename = argv[2];

    ifstream fin(ifilename);
    if (!fin.is_open()) {
        cout << "Error opening file: " << ifilename << endl;
        return 1;
    }
    Image img;
    Image_init(&img, fin);

    int width = stoi(argv[3]);
    bool has_height = (argc == 5);
    int height;
    if (has_height){
        height = stoi(argv[4]);
    }
    if ((width < 1) | (width > Image_width(&img))
     | (height < 1) | (height > Image_height(&img))){
        print_usage();
        return 1;
    }

    ofstream fout(ofilename);
    if (!fout.is_open()){
        cout << "Error opening file: " << ofilename << endl;
        return 1;
    }
    seam_carve(&img, width, height);
    Image_print(&img, fout);

    return 0;


}