#include <iostream>
#include <string>
#include "rlogger.h"

int main() {
	rloggerSettings set;
	set.filename = "rlogger.log";
	set.b_file = true;
	set.b_stdout =  true;

	rlogger *ilgr = new rlogger();
	ilgr->init( set );

	set.b_loglevel = LOGDEBUG;

	RLOG(ilgr) << "Ranjan" << std::endl;
	RLOG(ilgr) << "Ranjan" << std::endl;
	RLOG_L(ilgr, LOGERR) << "Ranjan" << std::endl;
		rlogger lgr;
	while (1);

}
