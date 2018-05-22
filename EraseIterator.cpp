#ifndef ERASE_ITERATOR_CPP
#define ERASE_ITERATOR_CPP

#include "Sequence.cpp"
#include "SequenceTreeIterator.cpp"

template<class T>
class EraseIterator{
public:
	friend Sequence<T>;

	EraseIterator(Sequence<T>& _d, size_t _pos1 , size_t _pos2):
	d(_d),
	it_cur(_d.seq.begin()),
	pos1(_pos1),
	pos2(_pos2),
	curPosition(0)
	{
		skipp();
	}

	EraseIterator(Sequence<T>& _d, size_t _pos1 , size_t _pos2, nullptr_t n):
	d(_d),
	it_cur(_d.seq.end()),
	pos1(_pos1),
	pos2(_pos2),
	curPosition(0)
	{
	}

	bool operator==(const EraseIterator& other){
		return this->it_cur == other.it_cur;
	}

	bool operator!=(const EraseIterator& other){
		return !(*this == other);
	}

	typename Sequence<T>::StlTreeIterator operator*() const{
		return *it_cur;
	}

	void operator++(){
		if(curPosition < pos1 || curPosition > pos2){
			if(it_cur == d.seq.end()){
				return;
			}
			++it_cur;
			++curPosition;
		}
		skipp();
	}

protected:
	Sequence<T>& d;
	typename Sequence<T>::StlList::iterator it_cur;
	size_t curPosition;
	size_t pos1;
	size_t pos2;
private:
	void skipp(){
		while(pos1 <= curPosition && curPosition <= pos2){
			if(it_cur == d.seq.end()){
				return;
			}
			d.safeDeleteFromTree(*it_cur);

			it_cur = d.seq.erase(it_cur);
			++curPosition;
		}
	}
};

#endif
