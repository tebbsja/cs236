/*
 * Relation.h
 *
 *  Created on: Jul 27, 2015
 *      Author: mocklera
 */

#ifndef RELATION_H_
#define RELATION_H_

#include <string>
#include <vector>
#include <set>
#include "Tuple.h"
#include "Scheme.h"

class Relation {
public:
	Relation();
	Relation(std::string name);
	virtual ~Relation();
	Relation select(int index, std::string value);
	Relation select(int index1, int index2);
	Relation project(std::vector<int> indices);
	Relation rename(std::vector<std::string> names);
	Relation join(Relation r2);
	std::string do_union(Relation r2);
	std::string to_string();
	Scheme scheme;
	std::set<Tuple> tuples;

private:
	std::string name;

	Scheme join_scheme(Relation r2);
	std::vector<std::pair<int, int>> get_common_attributes(Relation r2);
	bool can_join(Tuple t1, Tuple t2, std::vector<std::pair<int, int>> common_attributes);
	Tuple join_tuples(Tuple t1, Tuple t2, std::vector<std::pair<int, int>> common_attributes);
	Tuple do_product(Tuple t1, Tuple t2);
};

#endif /* RELATION_H_ */
