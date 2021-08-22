#include "log.h"

namespace sylar{

const char* LogLevel::ToString(LogLevel::Level level){
    switch(level) {
#define XX(name) \
        case LogLevel::name:\
            return #name;\
            break;
        XX(DEBUG); 
        XX(INFO); 
        XX(WARN); 
        XX(ERROR); 
        XX(FATAL); 
#undef XX
        default:
            return "UNKNOW";
    }
    return "UNKNOW";
}

Logger::Logger(const std::string& name)
    :m_name(name){
}

void Logger:addAppender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}

void Logger:addAppender(LogAppender::ptr appender){
    for(auto it = m_appenders.begin(); it != m_appenders.end(); it++){
        if(*it == appender) {
            m_appders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
    if(level >= m_level){
        for(auto& i: m_appender){
            i->log(level, event);
        }
    }   
}

void Logger::debug(LogLevel::Level level){
    debug(LogLevel::DEBUG, event);
}

void Logger::info(LogLevel::Level level){
    debug(LogLevel::INFO, event);
}

void Logger::warn(LogLevel::Level level){
    debug(LogLevel::WARN, event);
}

void Logger::error(LogLevel::Level level){
    debug(LogLevel::ERROR, event);
}

void Logger::fatal(LogLevel::Level level){
    debug(LogLevel::FATAL, event);
}

FileLogAppender::FileLogAppender(const std:;string& filename){
}

void FileLogAppender::log(LogLevel level, LogEvent::ptr event){
    if(level >= m_level) {
        m_filestream << m_formatter->format(event);
    }
}

bool FileLogAppeder::reopen() {
    if(m_filestream) {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !!m_filestream;
}
void StdoutLOgAppender::log(LogLevel::Level, LogEvent::ptr event){
    if(level >= m_level){
        std::cout << m_formatter->format(event);
}

LogFormatter::LogFormatter(const std::string& pattern)
    : m_pattern(pattern){
}

std::string& LogFormatter::format(LogLevel level, LogEvent::ptr event){
    std::stringstream ss;
    for(auto& i : m_items){
        i->format(ss, level, event);
    }
    return ss.str();
}

void LogFormatter::init() {
    //str, format, type
    std::vector<std::tuple<std::string, int> > vec;
    size_t last_pos = 0;
    for(size_t i = 0; i < m_pattern.size(); ++i){
        if(m_pattern[i] != '%'){
            str.append(1, m_pattern[i]);
            continue;
        }
        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;
        while(n < m_pattern.size()) {
            if(ispace(m_pattern[n]) {
                    break;
            }
            if(fmt_status == 0) {
                if(m_pattern[n] == '{') {
                    str = m_pattern.substr(i + 1, n - i);
                    fmt_status = 1;
                    ++n;
                    fmt_begin = n;
                    continue;
                }
            }
            if(fmt_status == 1) {
                if(m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin);
                }
            }
        }

    }
}

class MessageFormatItem : public Logformatter::FormatItem {
public:
     void format(std::ostream& os,LogLevel::Level level, LogEvent::ptr event) override {
         os << event->gegtContent();
     }
};

class LevelFormatItem : public Logformatter::FormatItem {
public:
     void format(std::ostream& os, LogLevel::Level level, LogEvent::ptr event) override {
         os << LogLevel::ToString(event->getContent());
     }
};
}

