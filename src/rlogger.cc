#include "rlogger.h"

rlogger* rlogger::obj = nullptr;

rlogger::rlogger()
{
	if (obj != nullptr) {
		std::cout << "Singleton Proterty Violation" << std::endl;
		throw "Singleton Exception!";
	} else {
		std::cout << "Singleton " << obj << std::endl;
		this->b_init = false;
		this->obj = this;
	}
}

rlogger::~rlogger()
{
	if ( this->b_init ) this->shutdown();
}

rlogger* rlogger::getObj()
{
	if (obj == nullptr) {
		//obj = new rlogger();
		new rlogger();
	}
	return obj;
}

bool rlogger::init( const rloggerSettings& settings )
{
	this->settings = settings;
	if ( !this->b_init )
	{
		if ( this->settings.b_overwriteFile )
		{
			this->ofs.open( this->settings.path+this->settings.filename );
		}
		else
		{
			this->ofs.open( this->settings.path+getDateTimeFilenameStr()+"_"+this->settings.filename );
		}

		if ( this->ofs.is_open() )
		{
			this->b_init = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

void rlogger::shutdown()
{
	if ( this->b_init )
	{
		this->ofs.close();
		this->b_init = false;
	}
}

std::string rlogger::prefix( const std::string& file , const int line ) 
{
	std::string result = "";
	if ( this->settings.b_datetime )
	{
		result += getDateTimeStr();

		if ( !this->settings.b_fileline ) result += ": ";
		else result += ", ";
	}

	result += this->getloglevelstr(this->curr_loglevel);
	result += ":";

	if ( !this->settings.b_module.empty() ) 
	{
		result += this->settings.b_module + " :";
	}
	if ( this->settings.b_pid )
	{
		std::string pid;
		result += "[" + pid + "]:";
	}
	if ( this->settings.b_tid )
    {
		std::string tid;
        result += "[" + tid + "]: ";
    }
	if ( this->settings.b_fileline )
	{
		result += file + "(" + tostring(line) + "): ";
	}
	return result;
}

std::string rlogger::getloglevelstr(log_level_t level)
{
	std::string str;
	switch (level){
		case LOGINFO:
			str = "INFO    ";
			break;
		case LOGERR:
			str = "ERROR   ";
            break;
		case LOGDEBUG:
			str = "DEBUG   ";
            break;
		case LOGCRITICAL:
			str = "CRITICAL";
            break;
		case LOGPANIC:
			str = "PANIC   ";
            break;
		default:
			str = "UNKNOWN ";
	}
	return str;
}

rloggerSettings& rlogger::getsettings()
{
	return this->settings;
}

void rlogger::setsettings(rloggerSettings &settings)
{
	rloggerSettings &set = getsettings();
	set = settings;
}

void rlogger::setlevelsetting(log_level_t level)
{
	this->settings.b_loglevel |= level;
}

void rlogger::resetlevelsetting(log_level_t level)
{
    this->settings.b_loglevel &= ~(1 << level);
}

void rlogger::setcurrlevel(log_level_t level)
{
    this->curr_loglevel = level;
}
bool rlogger::checklogging()
{
	return((this->settings.b_loglevel & ( 1 << this->curr_loglevel)) != 0);
}
