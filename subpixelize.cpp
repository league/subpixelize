#include <Magick++.h>
#include <iostream>
#include <cassert>

using std::cout;
using std::string;
using namespace Magick;

/* Each pixel in input image is rendered as
 *    GRBx
 *    BRGx
 *    xxxx
 * in the output image. So pixels are 4x3,
 * including inter-pixel space.
 */

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
    for(unsigned x = 0; x < gin.width(); x++) {
        for(unsigned y = 0; y < gin.height(); y++) {
            Color c = in.pixelColor(x,y);
            unsigned i = x*4;
            unsigned j = y*3;
            // Row 0: GRB
            out.pixelColor(i+0, j+0, Color(0, c.greenQuantum(), 0));
            out.pixelColor(i+1, j+0, Color(c.redQuantum(), 0, 0));
            out.pixelColor(i+2, j+0, Color(0, 0, c.blueQuantum()));
            // Row 1: BRG
            out.pixelColor(i+0, j+1, Color(0, 0, c.blueQuantum()));
            out.pixelColor(i+1, j+1, Color(c.redQuantum(), 0, 0));
            out.pixelColor(i+2, j+1, Color(0, c.greenQuantum(), 0));
        }
    }
    out.write(outputPath);
    return 0;
}
