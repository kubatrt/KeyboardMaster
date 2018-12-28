#pragma once

#include <unordered_map>
#include <string>


namespace framework
{

const std::string ResourcesDirectory = "data/";

// Resource manager class
// TODO: get rid of extensions
template<typename Resource>
class ResourceManager
{
public:
    ResourceManager(const std::string& folder, const std::string& extention)
        : folder_(ResourcesDirectory + folder + "/")
        , extension_("." + extention)
    {
    }

    const Resource& get(const std::string& name)
    {
        if (!exists(name))
        {
            add(name);
        }
        return resources_.at(name);
    }

    bool exists(const std::string& name) const
    {
        return resources_.find(name) != resources_.end();
    }

    void add(const std::string& name)
    {
        Resource res;

        if (!res.loadFromFile(getFullname(name)))
        {
        	// If the resource fail to load, then default "fail" resource is added
            Resource fail;
            fail.loadFromFile(folder_ + "_fail_" + extension_);
            resources_.insert(std::make_pair(name, fail));
        }
        else
        {
           resources_.insert(std::make_pair(name, res));
        }
    }

private:
    std::string getFullname(const std::string& name)
    {
        return folder_ + name + extension_;
    }

    const std::string folder_;
    const std::string extension_;
    std::unordered_map<std::string, Resource> resources_;	// resources held as usual objects? Pointer not necessery, hence everything is on heap.
};

}
