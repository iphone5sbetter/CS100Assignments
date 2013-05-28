#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "baseboggleplayer.h"
#include "boggleutil.h"


class BogglePlayer: public BaseBogglePlayer {

private:
    //create the alphaTrie
    alphaTrie* t;
    string** board; // do we need this?
    unsigned int col;
    unsigned int row;
};

#endif //BOGGLEPLAYER_H
