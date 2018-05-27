#include <iostream>
#include <array>

#include "Sequence.cpp"

int main()
{

	Sequence<int> seq;
	seq.insert(6);
	seq.insert(2);
	seq.insert(3);
	seq.insert(3);
	seq.insert(3);
	seq.insert(2);
	seq.insert(3);

	Sequence<int> seq2;
	seq2.insert(3);
	seq2.insert(3);


	auto res = Sequence<int>::exclude(seq, seq2);

	for(auto& el : res){
		std::cout << el << "\t";
	}
	std::cout << std::endl;


	return 0;
}
