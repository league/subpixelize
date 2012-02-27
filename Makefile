CXXFLAGS=-Wall `Magick++-config --cppflags --cxxflags`
LDFLAGS=`Magick++-config --ldflags --libs`

default: all

all: subpixelize

clean:
	$(RM) subpixelize
	$(RM) -r *.dSYM
