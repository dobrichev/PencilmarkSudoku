/*
 * tables.h
 *
 *  Created on: Dec 13, 2020
 *      Author: mladen
 */

#ifndef TABLES_H_
#define TABLES_H_

typedef int cellIndex;

struct tables {
	static const int affectedGroups[81][3];
	static const cellIndex cellsInGroup[27][9];
};

#endif /* TABLES_H_ */
