#ifndef OBSERVERPATTERN_H
#define OBSERVERPATTERN_H

#include <list>
#include <iostream>
class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void Update(const std::string &message_from_subject) = 0;
};

class ISubject {
	private:
		std::list<IObserver *> list_observer_;
	public:
		virtual ~ISubject(){};
		void Attach(IObserver *observer);
		void Detach(IObserver *observer);
		void Notify();
};

#endif