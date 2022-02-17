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

	set.b_loglevel |= LOGDEBUG;

	RLOG(ilgr) << "Ranjan" << std::endl;
	RLOG(ilgr) << "Ranjan" << std::endl;
	RLOG_L(ilgr, LOGERR) << "Ranjan" << std::endl;

	rlog(LOGDEBUG) << "Ranjan" << std::endl;
	_INFO << "Ranjan" << std::endl;
	_ERR << "Ranjan" << std::endl;
	_DEBUG << "Ranjan" << std::endl;


	ilgr->resetlevelsetting(LOGERR);
	_ERR << "---------------------------" << std::endl;

	set.b_loglevel |= LOGERR;
	ilgr->setsettings(set);
	_ERR << "---------------------------||||||------------------------------" << std::endl;

		rlogger lgr;
	while (1);

}
