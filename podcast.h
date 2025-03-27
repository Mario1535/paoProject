#ifndef PODCAST_H
#define PODCAST_H

#include <string>
#include "abstractMedia.h"

class Podcast : public AbstractMedia {
private:
    unsigned int episode;
    unsigned int season;

public:
    Podcast(
        const std::string & = "",
        const std::string & = "",
        const std::string & = "",
        const unsigned int & = 0,
        const double & = 0,
        const unsigned int & = 0,
        const unsigned int & = 0
        );
    ~Podcast() override;

    //Gets
    unsigned int getEpisode() const;
    unsigned int getSeason() const;

    //Sets
    void setEpisode(const unsigned int &);
    void setSeason(const unsigned int &);
};

#endif //PODCAST_H
