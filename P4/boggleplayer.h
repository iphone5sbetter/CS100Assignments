#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "baseboggleplayer.h"


class boggleplayer: public baseboggleplayer {

private:

//create the alphaTrie
 alphaTrie* t;
 string** board; // do we need this?
 unsigned int col;
 unsigned int row;

};

#endif //BOGGLEPLAYER_H
