#ifndef RESSOURCEHOLDER_HPP
#define RESSOURCEHOLDER_HPP
#include "assert.h"

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    ResourceHolder(){}
    void load(Identifier id, const std::string& filename)
    {
        std::unique_ptr<Resource> res(new Resource());
        if(!res->loadFromFile(filename))
        {
            throw std::runtime_error("ResoruceHolder::load failed ro load" + filename);
        }
        auto inserted = ResourceMap.insert(std::make_pair(id,std::move(res))); // 2 args: iterator/boolean, falls bool = false => id exist => logic error
        assert(inserted.second);
    }
    template<typename param2>
    void load(Identifier id, const std::string& filename, const param2& p2)
    {
        std::unique_ptr<Resource> res(new Resource());
        if(!res->loadFromFile(filename,p2))
        {
            throw std::runtime_error("ResoruceHolder::load failed ro load" + filename);
        }
        auto inserted = ResourceMap.insert(std::make_pair(id,std::move(res))); // 2 args: iterator/boolean, falls bool = false => id exist => logic error
        assert(inserted.second);
    }
    Resource& get(Identifier id)
    {
        auto found = ResourceMap.find(id);
        assert(found != ResourceMap.end()); //iterator points to the past of end if id not inside
        return *found->second;
    }
    const Resource& get(Identifier id) const

    {
        auto found = ResourceMap.find(id);
        assert(found != ResourceMap.end()); //iterator points to the past of end if id not inside
        return *found->second;
    }


private:
    std::map<Identifier, std::unique_ptr<Resource>> ResourceMap;

};
#endif
