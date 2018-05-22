#ifndef SEQUENCE_CPP
#define SEQUENCE_CPP

#include <set>
#include <list>
#include <utility>
#include <memory>

#include "SequenceTreeIterator.cpp"
#include "PairOrderedByFirst.cpp"


template<class T>
class EraseIterator;
template<class T>
class ExclusionIterator;

template<class T>
class Sequence{
public:
	friend EraseIterator<T>;
	friend ExclusionIterator<T>;


	using customPair = pairOrderedByFirst<T>;
	using StlTree = typename std::set<pairOrderedByFirst<T>, ComparePairsByFirst<pairOrderedByFirst<T>>>;
	using StlTreeIterator = typename StlTree::iterator;
	using StlList = typename std::list<StlTreeIterator>;

	Sequence(){};

	Sequence(const Sequence<T>& other){
		*this = other;
	}
friend ExclusionIterator<T>;
	Sequence(Sequence<T>&& other){
		*this = std::move(other);
	}

	Sequence<T>& operator=(const Sequence<T>& other){
		this->set = other.set;
		this->seq = other.seq;

		return *this;
	}

	Sequence<T>& operator=(Sequence<T>&& other){
		this->set = std::move(other.set);
		this->seq = std::move(other.seq);

		return *this;
	}

	SequenceTreeIterator<T> begin() const{
		return SequenceTreeIterator<T>(this->seq.cbegin());
	}

	SequenceTreeIterator<T> end() const{
		return SequenceTreeIterator<T>(this->seq.cend());
	}

	void add(T el){
		auto iter = this->safeAddToTree(el);
		this->seq.push_back(iter); //Iterator on inserted element or equal element in set
	}

	int getSeqSize(){
		return this->seq.size();
	}
	int getSetSize(){
		return this->set.size();
	}



	static Sequence<T> erase(const Sequence<T>& d1, size_t pos1 , size_t pos2);
	static Sequence<T> merge(const Sequence<T>& d1, const Sequence<T>& d2);
	static Sequence<T> exclusion(const Sequence<T>& d1, const Sequence<T>& d2);
	static Sequence<T> concat(const Sequence<T>& d1, const Sequence<T>& d2);
	static Sequence<T> mul(const Sequence<T>& d1, size_t times);
	static Sequence<T> subst(const Sequence<T>& d1, const Sequence<T>& d2, size_t pos);
	static Sequence<T> change(const Sequence<T>& d1, const Sequence<T>& d2, size_t pos);

	Sequence<T> operator|(const Sequence<T>& other) const;
	Sequence<T> operator&(const Sequence<T>& other) const;
	Sequence<T> operator^(const Sequence<T>& other) const;
	Sequence<T> operator/(const Sequence<T>& other) const;

private:
	 StlTree set;
	 StlList seq;
	 void safeDeleteFromTree(StlTreeIterator it){
		 --it->getCountRef();
 		if(it->getCountRef() <= 0){
 			this->set.erase(it);
 		}
 	}

	StlTreeIterator safeAddToTree(T el){
		return safeAddToTreeByIterator(this->set.begin(), el);
	}

	StlTreeIterator safeAddToTreeByIterator(StlTreeIterator out_it, T el){
		auto iterator = this->set.insert(out_it, pairOrderedByFirst(el, 0));

		++(iterator->getCountRef());

		return iterator;
	}

};

#include "SequenceOperations.cpp"
#include "SetOperations.cpp"

#endif
