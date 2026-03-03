#include "stock.h"
#include <iostream>
#include <algorithm>
#include <limits>

Stock::Stock() : next_id(0), current_id(0){}

void Stock::Add(int w, int v) {
	Box new_box{ next_id, w, v, current_time };

	boxes.push_back(new_box);
	by_weight.insert({ w, next_id });
	by_volume.insert({ v, next_id });
	box_by_id[next_id] = new_box;

	next_id++;
	current_id++;
}

int Stock::GetByW(int min_w) {
	auto it = by_weight.lower_bound({ min_w, -1 }); //поиск с нужным весом и минимальным значением ID
	if (it == by_weight.end()) {
		return = -1 //если коробок нет
	}

	int best_id = -1;
	int best_time = std::numeric_limits<int>::max();

	std::vector<decltype(it)> to_remove; //кооп auto и decltype

	while (it != by_weight.end() && it->first >= min_w) {
		int current_id = it->second;

		if (box_by_id.find(current_id) != box_by_id.end()) {
			int current_time = box_by_id[current_id].timestamp;

			if (current_time < best_time) {
				best_time = current_time;
				best_id = current_id;
			}
		}
		it++;
	}

	if (best_id == -1) {
		return -1;
	}

	//Удаляем из всех структур
	Box& found_box = box_by_id[best_id];

	// Удаляем из by_weight
	auto weight_range = by_weight.equal_range({ found_box.w, best_id });
	for (auto wit = weight_range.first; wit != weight_range.second; ++wit) {
		if (wit->second == best_id) {
			by_weight.erase(wit);
			break;
		}
	}

	// Удаляем из by_volume
	auto volume_range = by_volume.equal_range({ found_box.v, best_id });
	for (auto vit = volume_range.first; vit != volume_range.second; ++vit) {
		if (vit->second == best_id) {
			by_volume.erase(vit);
			break;
		}
	}

	// Удаляем из box_by_id
	box_by_id.erase(best_id);

	return best_id;
}

int Stock::GetByV(int min_v) {
    // Ищем первую коробку с меньшим объемом
    auto it = by_volume.lower_bound({ min_v, -1 });

    if (it == by_volume.end()) {
        return -1; 
    }

    int best_id = -1;
    int best_time = std::numeric_limits<int>::max();

    while (it != by_volume.end() && it->first >= min_v) {
        int current_id = it->second;

        if (box_by_id.find(current_id) != box_by_id.end()) {
            int current_time = box_by_id[current_id].timestamp;

            if (current_time < best_time) {
                best_time = current_time;
                best_id = current_id;
            }
        }
        ++it;
    }

    if (best_id == -1) {
        return -1;
    }

    Box& found_box = box_by_id[best_id];

    auto weight_range = by_weight.equal_range({ found_box.w, best_id });
    for (auto wit = weight_range.first; wit != weight_range.second; ++wit) {
        if (wit->second == best_id) {
            by_weight.erase(wit);
            break;
        }
    }

    auto volume_range = by_volume.equal_range({ found_box.v, best_id });
    for (auto vit = volume_range.first; vit != volume_range.second; ++vit) {
        if (vit->second == best_id) {
            by_volume.erase(vit);
            break;
        }
    }

    box_by_id.erase(best_id);

    return best_id;
}

void Stock::PrintStock() const {
    std::cout << "Stock now:" << std::endl;
    std::cout << "All boxes: " << box_by_id.size() << std::endl;

    // Сортируем коробки по времени поступления для наглядности
    std::vector<Box> sorted_boxes;
    for (const auto& pair : box_by_id) {
        sorted_boxes.push_back(pair.second);
    }

    std::sort(sorted_boxes.begin(), sorted_boxes.end(),
        [](const Box& a, const Box& b) {
            return a.timestamp < b.timestamp;
        });

    for (const auto& box : sorted_boxes) {
        std::cout << "  ID: " << box.id
            << " (w=" << box.w << ", v=" << box.v
            << ", time=" << box.timestamp << ")" << std::endl;
    }
    std::cout << std::endl;
}