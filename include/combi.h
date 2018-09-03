#ifndef SW_COMBI_H
#define SW_COMBI_H

#include <array>
#include <string>
#include "combi/model.h"

namespace simwar {

	TeamSetup stampToSetup(std::string stamp);
	std::string setupToStamp(TeamSetup setup);

	Array5 intToFormation(int r);
	int formationToInt(const Array5& r);

	void printForm(const Array5& arr);
	void printArr(const Array5& arr);

}

#endif
