#pragma once

#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

// Implementation from
// https://juanchopanzacpp.wordpress.com/2013/02/24/simple-observer-pattern-implementation-c11/

namespace framework
{

enum class TextEvent
{ 
    Word,
    Letter
};


class Observer
{
public:
	virtual ~Observer();
    virtual void notif() = 0;
};

using ObserverObjPtr = std::weak_ptr<Observer>;

class Subject
{
public:
    void addObserver(const TextEvent& event, ObserverObjPtr observer)
    {
        observers_[event].push_back(observer);
    }

    void removeObserver(const TextEvent& event, ObserverObjPtr observer)
    {
        //std::remove(observers_[event].begin(),  observers_[event].end(), observer), observers_.end();
    }

    void notify(const TextEvent& event)
    {
        for (auto& observer : observers_[event])
        {
            if (auto obj = observer.lock())
            {
                obj->notif();
            }
        }
 }

private:
    std::map<TextEvent, std::vector< ObserverObjPtr> > observers_;
};

} // framework
