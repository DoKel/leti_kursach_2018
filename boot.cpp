#include <iostream>
#include <vector>

#include "Sequence.cpp"

int main()
{

	Sequence<int> seq;
	seq.add(1);
	seq.add(2);
	seq.add(3);
	seq.add(4);
	seq.add(6);

	Sequence<int> seq2;
	seq2.add(2);
	seq2.add(3);
	seq2.add(4);
	seq2.add(5);

	Sequence<int> res = seq ^ seq2;
	for(auto& el : res){
		std::cout << el << "\t";
	}
	std::cout << std::endl;


	return 0;
}
