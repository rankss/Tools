#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <mutex>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

namespace Tools
{
	class Logger
	{
	public:
		enum class Level
		{
			TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL
		};

	private:
		static Logger instance;
		bool active = false;
		std::mutex mutex;
		Level level = Level::TRACE;
		std::ofstream fstream;

		const std::string PRIORITY_MAP[6] = { "[Trace]", "[Debug]", "[Info]", "[Warn]", "[Error]", "[Critical]" };

		Logger(const Logger& source) = delete;
		Logger(const Logger&& source) = delete;

		void start(Level aLevel, const std::string& filepath)
		{
			if (active) return;
			active = true;
			level = aLevel;

			try
			{
				instance.fstream.open(filepath.c_str());
				instance.fstream << "This log file is created by Tools::Logger." << std::endl;
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}

		void stop()
		{
			instance.fstream << "Logger terminated." << std::endl;
			instance.active = false;
			if (instance.fstream.is_open())
			{
				instance.fstream.close();
			}
		}

		std::string now()
		{
			char buffer[32];
			time_t now = time(nullptr);
			struct tm timeinfo;
			localtime_s(&timeinfo, &now);
			strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &timeinfo);

			return std::string(buffer);
		}

	public:
		Logger()
		{
			instance.start(Level::INFO, "logfile.log");
		}

		Logger(Level aLevel, const std::string& filepath)
		{
			instance.start(aLevel, filepath);
		}

		~Logger() 
		{
			instance.stop();
		}
		
		static Logger& Instance()
		{
			return instance;
		}
		
		void Log(Level aLevel, const std::string& aMessage)
		{
			if (aLevel >= instance.level && aLevel <= Level::CRITICAL)
			{
				std::lock_guard<std::mutex> lock(instance.mutex);
				instance.fstream << instance.now() << " " << PRIORITY_MAP[(int)aLevel] << ": " << aMessage << std::endl;
			}
		}
	};

	Logger Logger::instance; // Forward declaration
}


#endif // !LOGGER_HPP