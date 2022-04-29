#include <iostream>
#include <list>
#include <string>
#include "../../Inc/observerPattern.h"

using namespace std;

void ISubject::Attach(IObserver *observer){
	list_observer_.push_back(observer);
}

void ISubject::Detach(IObserver *observer){
	list_observer_.remove(observer);
}

void ISubject::Notify(){
	std::list<IObserver *>::iterator iterator = list_observer_.begin();
	while (iterator != list_observer_.end()) {
		(*iterator)->Update("Notify");
		++iterator;
	} 
}