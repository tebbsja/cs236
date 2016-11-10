/*
 * Relation.cpp
 *
 *  Created on: Jul 27, 2015
 *      Author: mocklera
 */

#include <iostream>
#include <sstream>
#include <algorithm>
#include "Relation.h"

Relation::Relation() {
	this->name = "";
}

Relation::Relation(std::string name) {
	this->name = name;
}

Relation::~Relation() {}

Relation Relation::select(int index, std::string value) {
	Relation temp = Relation(this->name);
	temp.scheme = this->scheme;

	for (Tuple tuple : this->tuples) {
		if (tuple.at(index) == value) {
			temp.tuples.insert(tuple);
		}
	}

	return temp;
}

Relation Relation::select(int index1, int index2) {
	Relation temp = Relation(this->name);
	temp.scheme = this->scheme;

	for (Tuple tuple : this->tuples) {
		if(tuple.at(index1) == tuple.at(index2)) {
			temp.tuples.insert(tuple);
		}
	}

	return temp;
}

Relation Relation::project(std::vector<int> indices) {
	Relation temp = Relation(this->name);

	int num_indices = indices.size();
	for (int i = 0; i < num_indices; i++) {
		temp.scheme.push_back(this->scheme.at(indices.at(i)));
	}

	for (Tuple tuple : this->tuples) {
		Tuple t;
		for (int i = 0; i < num_indices; i++) {
			t.push_back(tuple.at(indices.at(i)));
		}
		temp.tuples.insert(t);
	}

	return temp;
}

Relation Relation::rename(std::vector<std::string> names) {
	Relation temp = Relation(this->name);
	temp.tuples = this->tuples;

	for (auto name : names) {
		temp.scheme.push_back(name);
	}

	return temp;
}

std::string Relation::to_string() {
	std::stringstream s;

	for (auto tuple : this->tuples) {
		if (!tuple.empty()) {
			s << " ";
			int num_attributes = this->scheme.size();
			for (int i = 0; i < num_attributes; i++) {
				s << " " << this->scheme.at(i) << "=" << tuple.at(i);
			}
			s << "\n";
		}
	}

	return s.str();
}

Relation Relation::join(Relation r2) {
	// Combine the schemes and make a new empty relation that uses the combined schemes
	Relation join_result = Relation("temp_join");
	join_result.scheme = join_scheme(r2);

	// Find which attributes they have in common to prep for the join
	std::vector<std::pair<int, int>> common_attributes = get_common_attributes(r2);

	for (Tuple t1 : this->tuples) {
		for (Tuple t2 : r2.tuples) {
			if (common_attributes.size() > 0) {
				// Check if the tuples can join
				bool join = can_join(t1, t2, common_attributes);
				if (join) {
					// Build the joined tuple and add it to the new relation
					Tuple t = join_tuples(t1, t2, common_attributes);
					join_result.tuples.insert(t);
				}
			}
			else {
				Tuple t = do_product(t1, t2);
				join_result.tuples.insert(t);
			}
		}
	}

	return join_result;
}

Tuple Relation::do_product(Tuple t1, Tuple t2) {
	Tuple t = Tuple();
	for (auto item : t1) {
		t.push_back(item);
	}
	for (auto item2 : t2) {
		t.push_back(item2);
	}
	return t;
}

Tuple Relation::join_tuples(Tuple t1, Tuple t2, std::vector<std::pair<int, int>> common_attributes) {
	Tuple t = Tuple();

	for (auto item : t1) {
		t.push_back(item);
	}

	int num_attributes = t2.size();

	for (int i = 0; i < num_attributes; i++) {
		// Make sure you aren't adding common attributes twice
		bool is_common_attribute = false;
		for (auto pair : common_attributes) {
			if (i == pair.second)
				is_common_attribute = true;
		}

		if (!is_common_attribute) {
			t.push_back(t2.at(i));
		}
	}

	return t;
}

bool Relation::can_join(Tuple t1, Tuple t2, std::vector<std::pair<int, int>> common_attributes) {
	bool can_join = false;

	for (auto pair : common_attributes) {
		if ( t1.at(pair.first) == t2.at(pair.second) ) {
			can_join = true;
		}
		else {
			can_join = false;
			return can_join;
		}
	}

	return can_join;
}

std::vector<std::pair<int, int>> Relation::get_common_attributes(Relation r2) {
	std::vector<std::pair<int, int>> common_attributes;

	int num_attributes_1 = this->scheme.size();
	int num_attributes_2 = r2.scheme.size();
	for (int i = 0; i < num_attributes_1; i++) {
		for (int j = 0; j < num_attributes_2; j++) {
			if (this->scheme.at(i) == r2.scheme.at(j)) {
				common_attributes.push_back({i,j});
			}
		}
	}

	return common_attributes;
}

Scheme Relation::join_scheme(Relation r2) {
	Scheme s = Scheme();

	// Put in the whole first scheme
	for (auto var : this->scheme)
		s.push_back(var);

	// Put in any additional vars from the second scheme
	for (auto var1 : this->scheme) {
		for (auto var2 : r2.scheme) {
			if (std::find(s.begin(), s.end(), var2) == s.end()) {
				s.push_back(var2);
			}
		}
	}

	return s;
}

std::string Relation::do_union(Relation r2) {
	std::stringstream s;
	for (Tuple tuple : r2.tuples) {
		std::pair<std::set<Tuple>::iterator,bool> ret = this->tuples.insert(tuple);
		if (ret.second) {
			s << "\n ";
			int scheme_size = this->scheme.size();
			for (int i = 0; i < scheme_size; i++) {
				s << " " << this->scheme.at(i) << "=" << tuple.at(i);
			}
		}
	}
	return s.str();
}



















