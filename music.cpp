#include <string>
#include "music.h"

Music::Music(
    const std::string &t,
    const std::string &a,
    const std::string &ip,
    const unsigned int &y,
    const double &d,
    const std::string &al,
    const std::string &l
    ) : AbstractMedia(t,a,ip,y,d), album(al), lirycs(l) {}
Music::~Music(){}

//Gets
std::string Music::getAlbum() const{
    return album;
}
std::string Music::getLirycs() const{
    return lirycs;
}

//Sets
void Music::setAlbum(const std::string &a){
    this->album = a;
}
void Music::setLirycs(const std::string &l){
    this->lirycs = l;
}
