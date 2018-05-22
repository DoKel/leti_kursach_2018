#ifndef SEQUENCE_OPS_CPP
#define SEQUENCE_OPS_CPP

#include "Sequence.cpp"
#include "EraseIterator.cpp"
#include "ExclusionIterator.cpp"
#include <algorithm>
#include <unordered_map>

/**
* Complexity: O(n)
*/
template<class T>
Sequence<T> Sequence<T>::erase(const Sequence<T>& d1, size_t pos1 , size_t pos2){
	Sequence<T> result = d1;

	auto iteratorBegin = EraseIterator<T>(result, pos1 , pos2);
	auto iteratorEnd = EraseIterator<T>(result, pos1 , pos2 , nullptr);

	Sequence<T>::StlList tmp_list;
	for(auto it = iteratorBegin; it != iteratorEnd; ++it){
		tmp_list.push_back(*it);
	}

	result.seq = std::move(tmp_list);

	return result;
}

template<class T>
Sequence<T> Sequence<T>::exclusion(const Sequence<T>& d1, const Sequence<T>& d2){
	Sequence<T> result = d1;

	auto iteratorBegin = ExclusionIterator<T>(result, d2);
	auto iteratorEnd = ExclusionIterator<T>(result, d2, nullptr);

	Sequence<T>::StlList tmp_list;
	for(auto it = iteratorBegin; it != iteratorEnd; ++it){
		tmp_list.push_back(*it);
	}

	result.seq = std::move(tmp_list);

	return result;
}

template<class T>
Sequence<T> Sequence<T>::subst(const Sequence<T>& d1, const Sequence<T>& d2, size_t pos){
	Sequence<T> result;
	std::set_union(d1.set.begin(), d1.set.end() , d2.set.begin()  , d2.set.end() , std::inserter(result.set, result.set.begin()));
	for(auto& el : result.set){
		el.getCountRef() = 0;
	}

	auto it = d1.seq.begin();
	size_t cur_pos = 0;
	for(;it != d1.seq.end() && cur_pos < pos; ++it){
		result.seq.push_back(*it);
		++cur_pos;
	}
	result.seq.insert(result.seq.end(), d2.seq.begin(), d2.seq.end());
	for(;it != d1.seq.end(); ++it){
		result.seq.push_back(*it);
	}

	std::unordered_map<T, StlTreeIterator> renew_table;

	for(auto it = result.set.begin(); it!=result.set.end(); ++it){
		renew_table.insert(std::pair(it->first, it));
	}

	for(auto it = result.seq.begin(); it!=result.seq.end(); ++it){
		*it = renew_table.at((*it)->first);
		(*it)->getCountRef() += 1;
	}

	return result;
}


template<class T>
Sequence<T> Sequence<T>::concat(const Sequence<T>& d1, const Sequence<T>& d2){
	return Sequence<T>::subst(d1, d2, d1.seq.size());
}

template<class T>
Sequence<T> Sequence<T>::mul(const Sequence<T>& d1, size_t times){
	Sequence<T> result = d1;
	for(auto& el : result){
		el.getCountRef()*=times;
	}

	for(size_t i = 0; i < times; ++i ){
		result.seq.insert(result.seq.end(), d1.seq.begin(), d1.seq.end());
	}
}

template<class T>
Sequence<T> Sequence<T>::merge(const Sequence<T>& d1, const Sequence<T>& d2){
	Sequence<T> result;
	auto iterator = result.set.end();
	StlTreeIterator it1 = d1.set.begin();
	StlTreeIterator it2 = d2.set.begin();
	while(it1 != d1.set.end() || it2 != d2.set.end()){
		StlTreeIterator* max = nullptr;
		if(it1 == d1.set.end()){
			max = &it2;
		}else if(it2 == d2.set.end()){
			max = &it1;
		}else {
			max = &(it1->first < it2->first ? it1 : it2);
		}

		for(int i = 0; i < (*max)->getCountRef(); ++i){
			iterator = result.safeAddToTreeByIterator(iterator, (*max)->first);
		}
		++*max;
	}

	for(auto it = result.set.begin(); it != result.set.end(); ++it){
		for(int i = 0; i < (it)->getCountRef(); ++i){
			result.seq.push_back(it);
		}
	}

	return result;
}

template<class T>
Sequence<T> Sequence<T>::change(const Sequence<T>& d1, const Sequence<T>& d2, size_t pos){
	Sequence<T> result = d1;

	result = Sequence<T>::erase(result, pos, pos+d2.seq.size()-1);
	result = Sequence<T>::subst(result, d2, pos);

	return result;
}


#endif
