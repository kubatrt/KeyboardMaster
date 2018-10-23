#pragma once

#include <unordered_map>
#include <string>


namespace framework
{

template<typename Resource>
class ResourceManager
{
public:
    ResourceManager(const std::string& folder, const std::string& extention)
        : folder_(resourceDirectory_ + folder + "\\")
        , extension_("." + extention)
    {
    }

    const Resource& get(const std::string& name)
    {
        if (!exists(name))
        {
            add(name);
        }
        return m_resources.at(name);
    }

    bool exists(const std::string& name) const
    {
        return m_resources.find(name) != m_resources.end();
    }

    void add(const std::string& name)
    {
        Resource res;
        //if the resource fails to load, then it adds a default "fail" resource
        if (!res.loadFromFile(getFullname(name)))
        {
            Resource fail;
            fail.loadFromFile(folder_ + "_fail_" + ".ogg");
            m_resources.insert(std::make_pair(name, fail));
        }
        else
        {
           m_resources.insert(std::make_pair(name, res));
        }
    }

private:
    std::string getFullname(const std::string& name)
    {
        return folder_ + name + extension_;
    }

    const std::string resourceDirectory_ = "D:\\Workspace\\Projects\\Framework\\Debug\\res\\";
    const std::string folder_;
    const std::string extension_;

    std::unordered_map<std::string, Resource> m_resources;
};

}
