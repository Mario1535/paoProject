#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <string>

#include "abstractMedia.h"
#include "music.h"
#include "podcast.h"
#include "audiobook.h"

class Container
{
private:
    std::vector<const AbstractMedia*> media;

public:
    ~Container();
    void remove(const AbstractMedia*);
    void add(const AbstractMedia*);
    const AbstractMedia* getMedia(std::string &)const;
    std::vector<const AbstractMedia*> getMediaVec()const;

    std::vector<const AbstractMedia*>::const_iterator begin() const;
    std::vector<const AbstractMedia*>::const_iterator end() const;
    void search(Container*, std::string);
    bool empty();
    void clear();
    int size();

};

#endif // CONTAINER_H
