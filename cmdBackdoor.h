/*
 * cmdBackdoor.h
 *
 *  Created on: Sep 29, 2019
  *      Author: Mladen Dobrichev
 */

#ifndef CMDBACKDOOR_H_
#define CMDBACKDOOR_H_

#include "fsss2.h"

/*
 --backdoor    Print backdoors size & exemplar
*/
class cmdBackdoor {
private:
	bool vanilla = false;
public:
	cmdBackdoor();
	int exec();
	void findBackdoor(const pencilmarks& pm);
};

#endif /* CMDBACKDOOR_H_ */
