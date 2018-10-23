#pragma once

#include <list>
#include <memory>
#include <vector>
#include <iostream>


namespace prototype
{
/*  Observer design pattern

Subject: This class keeps track of all the observers and provides the facility to add or remove the observers.
Also it is the class that is RESPONSIBLE for updating the observers when any change occurs. In our solution,
we have ASubject implemented for the same purpose.

ConcreteSubject : This class is the real class that implements the Subject.
This class is the entity whose change will affect other objects.We have DummyProject class implemented for the same.

Observer : This represents an interface that defines the method that should be called whenever there is change.
We have implemented this as IObserver.

ConcreteObserver : This is the class which needs to keep itself updated with the change.This class just needs
to implement the Observer and  register itself with the ConcreteSubject and it is all set to receive the updates.
We have Shop class in our application serving the same purpose.
*/

class IObserver
{
public:
	virtual void notify() = 0;
};

class Observed : public IObserver
{
private:
	int value;
public:

	int getValue() { return value; }

	void update(int value)
	{
		this->value = value;
		std::cout << "Values has changed: " << value << std::endl;
	}
};
typedef std::unique_ptr<Observed>	ObservedPtr;


class Subject
{
protected:
	std::vector<ObservedPtr> list;

public:
    void registerObserver(ObservedPtr object)
    {
        //list.push_back( std::move(object));
    }
    void unregisterObserver(ObservedPtr object)
    {
        list.erase(std::remove(list.begin(), list.end(), object), list.end());
    }
    void notify(int value)
    {
        for (std::vector<ObservedPtr>::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            if (*it != nullptr)
                (*it)->notify(); // value
        }
    }
}
;
}