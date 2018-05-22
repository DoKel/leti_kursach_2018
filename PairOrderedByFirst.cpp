#ifndef MY_PAIR_CPP
#define MY_PAIR_CPP

#include <utility>
#include <memory>

template<class T>
class pairOrderedByFirst: public std::pair<T, std::unique_ptr<unsigned int>>{
public:
	pairOrderedByFirst(T el, unsigned int times):
	std::pair<T, std::unique_ptr<unsigned int>>(el, std::make_unique<unsigned int>(times))
	{
	}

	pairOrderedByFirst(const pairOrderedByFirst& other)
	{
		this->first = other.first;
		this->second = std::make_unique<unsigned int>(*(other.second));
	}

	pairOrderedByFirst(pairOrderedByFirst&& other)
	{
		this->first = std::move(other.first);
		this->second = std::move(other.second);
	}

	bool operator==(const pairOrderedByFirst& other){
		return this->first == other.first;
	}
	bool operator!=(const pairOrderedByFirst& other){
		return this.first != other.first;
	}
	bool operator>(const pairOrderedByFirst& other){
		return this->first > other.first;
	}

	bool operator<(const pairOrderedByFirst& other){
		return this->first < other.first;
	}

	bool operator>=(const pairOrderedByFirst& other){
		return this->first >= other.first;
	}

	bool operator<=(const pairOrderedByFirst& other){
		return this->first <= other.first;
	}

	unsigned int& getCountRef() const{
		return *(this->second);
	}
};

template<class T>
struct ComparePairsByFirst
{
    bool operator ()(const T& p1, const T& p2)
    {
		return p1.first < p2.first;
    }
};

#endif
