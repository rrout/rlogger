#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "util.h"

typedef enum {
	LOGINFO,
	LOGERR,
	LOGDEBUG,
	LOGCRITICAL,
	LOGPANIC
}log_level_t;

#define RLOG(logger)			(*logger << logger->prefix( __FILE__ , __LINE__ ))
#define RLOG_L(logger, level)	logger->setcurrlevel(level); \
									*logger << logger->prefix( __FILE__ , __LINE__ )

#define rlog(level)  			RLOG_L(rlogger::getObj(), level)
#define _INFO	            	RLOG_L(rlogger::getObj(), LOGINFO)
#define _ERR					RLOG_L(rlogger::getObj(), LOGERR)
#define _DEBUG      	        RLOG_L(rlogger::getObj(), LOGDEBUG)
#define _CRETICAL	           	RLOG_L(rlogger::getObj(), LOGCRITICAL)
#define _PANIC	             	RLOG_L(rlogger::getObj(), LOGPANIC)


class rloggerSettings
{
public:
	// path to the location of the log file, working directory by default
	std::string path;
	// filename, default "rlogger.log"
	std::string filename;
	// the log file will be overwritten, if false a new log file with the date and time is created
	bool b_overwriteFile;

	// print to the log file
	bool b_file;
	// print to the standard output
	bool b_stdout;

	// print the date and time
	bool b_datetime;
	// print the file and line
	bool b_fileline;

	std::string b_module;

	bool b_pid;

	bool b_tid;

	int32_t b_loglevel;

	rloggerSettings()
	{
		this->path = "";
		this->filename = "rlogger.log";
		this->b_overwriteFile = true;
		this->b_file = true;
		this->b_stdout = true;
		this->b_datetime = true;
		this->b_fileline = true;
		this->b_module = "";
		this->b_pid = false;
		this->b_tid = false;
		this->b_loglevel = LOGINFO | LOGERR | LOGDEBUG | LOGCRITICAL | LOGPANIC;
	}
};

class rlogger
{
public:
	rlogger();
	~rlogger();

	static rlogger* getObj();
	bool init( const rloggerSettings& settings );
	void shutdown();

	// overload the << operator to log all standard data types
	template< typename T > rlogger& operator<<( T t );
	// this is needed so << std::endl works
	rlogger& operator<<( std::ostream& (*fun)( std::ostream& ) );

	// Derive log level string
	std::string getloglevelstr(log_level_t level);
	rloggerSettings& getsettings();
	void setsettings(rloggerSettings &settings);
	void setlevelsetting(log_level_t level);
	void resetlevelsetting(log_level_t level);
	void setcurrlevel(log_level_t level);
	bool checklogging();

	// creates the prefix for every line depending on the settings
	std::string prefix( const std::string& file , const int line );

private:
	static rlogger* obj;
	bool b_init;
	log_level_t curr_loglevel;
	rloggerSettings settings;
	std::ofstream ofs;
};

template< typename T > inline rlogger& rlogger::operator<<( T t )
{
	if ( this->b_init && checklogging() )
	{
		if ( this->settings.b_file ) this->ofs << t;
		if ( this->settings.b_stdout ) std::cout << t;
	}
	return *this;
}

inline rlogger& rlogger::operator<<( std::ostream& (*fun)( std::ostream& ) )
{
	if ( this->b_init && checklogging() )
	{
		if ( this->settings.b_file ) this->ofs << std::endl;
		if ( this->settings.b_stdout ) std::cout << std::endl;
	}
	return *this;
}

