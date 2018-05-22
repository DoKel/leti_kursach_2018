#ifndef SEQUENCE_TREE_ITERATOR_CPP
#define SEQUENCE_TREE_ITERATOR_CPP

#include <set>
#include <utility>
#include "PairOrderedByFirst.cpp"

template<class T>
class SequenceTreeIterator{
public:
	using customPair = pairOrderedByFirst<T>;
	using StlTreeIterator = typename std::set<customPair, ComparePairsByFirst<customPair>>::iterator;
	using StlListIterator = typename std::list<StlTreeIterator>::const_iterator;

	SequenceTreeIterator(const StlListIterator _iterator):
	it(_iterator)
	{
	}

	const T& operator*() const {
		return (**it).first;
	}

	void operator++(){
		++it;
	}

	bool operator!=(const SequenceTreeIterator& other) const {
		return this->it != other.it;
	}

	bool operator==(const SequenceTreeIterator& other) const {
		return this->it == other.it;
	}

	

private:
	 StlListIterator it;
};

#endif
