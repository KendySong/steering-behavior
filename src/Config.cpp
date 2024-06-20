#include "Config.hpp"

Config* Config::p_config = nullptr;

Config* Config::instance()
{
	if (!p_config)
	{
		p_config = new Config();
	}
	return p_config;
}

Config::Config()
{

}