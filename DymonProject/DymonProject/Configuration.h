//created by Wang Jianwei on 01 Dec 2012
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>
#include <map>

namespace utilities {
	class Configuration{
		
	public:
		static Configuration* getInstance();

		std::map<std::string, std::string> getConfiguration() {return _config;}
	
		void setConfiguration(std::map<std::string, std::string> cfg);

		std::string getProperty(std::string,bool);
		
		typedef std::map<std::string, std::string> ConfigMap;
		
	private:
		Configuration(){};
		~Configuration(){};
		static Configuration* single;
		ConfigMap _config;
	};
}
#endif