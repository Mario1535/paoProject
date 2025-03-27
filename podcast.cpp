#include <string>
#include "podcast.h"

Podcast::Podcast(
    const std::string &t,
    const std::string &a,
    const std::string &ip,
    const unsigned int &y,
    const double &d,
    const unsigned int &e,
    const unsigned int &s
    ) : AbstractMedia(t,a,ip,y,d), episode(e), season(s) {}
Podcast::~Podcast(){}

//Gets
unsigned int Podcast::getEpisode() const{
    return episode;
}
unsigned int Podcast::getSeason() const{
    return season;
}

//Sets
void Podcast::setEpisode(const unsigned int &e){
    this->episode = e;
}
void Podcast::setSeason(const unsigned int &s){
    this->season = s;
}
