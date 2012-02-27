#include <Magick++.h>
#include <iostream>
#include <cassert>

using std::cout;
using std::string;
using namespace Magick;

int main(int argc, char** argv)
{
    InitializeMagick(*argv);
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " input.png output.png\n";
        exit(1);
    }

    const string inputPath = argv[1];
    const string outputPath = argv[2];

    cout << "Loading " << inputPath << '\n';
    Image in (inputPath);
    Geometry gin = in.size();
    assert(in.depth() <= 8);
    assert(in.type() == TrueColorType);
    cout << gin.width() << 'x' << gin.height() << '\n';

    Geometry gout(gin.width()*4, gin.height()*3);

    Image out;
    out.size(gout);
    out.magick("RGBA");
    cout << "Writing " << outputPath << '\n';
    for(unsigned x = 0; x < gout.width(); x++) {
        for(unsigned y = 0; y < gout.height(); y++) {
            unsigned i = x/4;
            unsigned j = y/3;
            Color c = in.pixelColor(i,j);
            unsigned a = x%4;
            unsigned b = y%3;
            if(a==0 && b==0 || a==2 && b==1) { // green
                c.redQuantum(0);
                c.blueQuantum(0);
            }
            else if(a==0 && b==1 || a==2 && b==0) { // blue
                c.redQuantum(0);
                c.greenQuantum(0);
            }
            else if(a==1 && b==0 || a==1 && b==1) { // red
                c.greenQuantum(0);
                c.blueQuantum(0);
            }
            else {
                c.redQuantum(0);
                c.greenQuantum(0);
                c.blueQuantum(0);
            }
            out.pixelColor(x, y, c);
        }
    }
    out.write(outputPath);
    return 0;
}
