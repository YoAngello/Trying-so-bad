#pragma once

#include <vector>
#include <set>
#include <map>

class Stock {
	struct Box {
		int id;
		int w;
		int v;
		int timestamp;
	};

	std::vector<Box> boxes;
	int next_id;
	int curren_id;

	std::multiset<std::pair<int, int>> by_weight; //пара из веса и ID
	std::multiset<std::pair<int, int>> by_volume; //пара из объема и ID

	std::map<int, Box> box_by_id; // быстрый доступ к коробке по ID

public:

	Stock();

	void Add(int w, int v); 

	void GetByW(int min_w); //берем коробку по весу

	void GetByV(int min_v); //берем коробку по объему

	void PrintStock() const;// abuyz вывода
};