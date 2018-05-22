#ifndef EXCLUSIONITERATOR_CPP
#define EXCLUSIONITERATOR_CPP

#include "Sequence.cpp"
#include "SequenceTreeIterator.cpp"

template<class T>
class ExclusionIterator{
public:
	//For actual usage
	ExclusionIterator(Sequence<T>& _d1, const Sequence<T>& _d2):
	d1(_d1),
	d2(_d2),
	it1(_d1.seq.begin()),
	curPosition(0)
	{
		this->skipD2IfCan();
	}
	//For defining end iterator
	ExclusionIterator(Sequence<T>& _d1, const Sequence<T>& _d2, nullptr_t n ):
	d1(_d1),
	d2(_d2),
	it1(_d1.seq.end()),
	curPosition(0)
	{
	}

	void operator++() {
		if(this->it1 == this->d1.seq.end()){
			return;
		}
		++this->it1;
		this->skipD2IfCan();
		++curPosition;
	}
	typename Sequence<T>::StlTreeIterator operator*() const{
		return *it1;
	}

	bool operator!=(const ExclusionIterator& other){
		return (this->it1!=other.it1);
	}

protected:
	Sequence<T>& d1;
	const Sequence<T>& d2;
	typename Sequence<T>::StlList::iterator it1;
	size_t curPosition;

	void skipD2IfCan(){
		if(this->it1 == this->d1.seq.end()){
			return;
		}
		auto temp = this->it1;
		auto it2 = this->d2.seq.begin();
		while(it2 != this->d2.seq.end() && (*this->it1)->first== (*it2)->first){
			++this->it1;
			++it2;

			if(this->it1 == this->d1.seq.end()){
				break;
			}
		}
		this->it1 = temp;
		if(it2 == this->d2.seq.end()){
			it2 = this->d2.seq.begin();
			while(it2 != this->d2.seq.end()){
				d1.safeDeleteFromTree(*it1);
				++this->it1;
				++it2;
			}
		}
	}
};



#endif
