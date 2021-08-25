#include "log.h"
#include <map>

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

class MessageFormatItem : public Logformatter::FormatItem {
public:
     void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
         os << event->getContent();
     }
};

class LevelFormatItem : public Logformatter::FormatItem {
public:
     void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
         os << LogLevel::ToString(event->getContent());
     }
};

class ElapseFormatItem : pulic LogFormatter::FormatItem {
public:
    void foramt(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getElapse();
    }
};

class NameFormatItem : pulic LogFormatter::FormatItem {
public:
    void foramt(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getName();
    }
};

class ThreadIdFormatItem : pulic LogFormatter::FormatItem {
public:
    void foramt(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getName();
    }
};

class FiberIdFormatItem : pulic LogFormatter::FormatItem {
public:
    void foramt(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getName();
    }
};

class DateTimeFormatItem : pulic LogFormatter::FormatItem {
public:
    DateTimeFormatItem(const std::string& format ="%Y:%m:%d %H:%M:%s")
        :m_format(format) {
    }
    void foramt(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getTime();
    }
private:
    std::string m_format;
};

class FilenameFormatItem : public LogFarmatter::FormatItem {
public:
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFile();
    }
};

class LineFormatItem : public LogFarmatter::FormatItem {
public:
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLine();
    }
};

class NewLineFormatItem : public LogFarmatter::FormatItem {
public:
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << std::endl; 
    }
};

class StringFormatItem : public LogFarmatter::FormatItem {
public:
    StringFormatItem(const std::string& str)
        :FormatItem(str), m_string(str){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << m_string; 
    }
private:
    std::string m_string;
};




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

void FileLogAppender::log(std::shared_ptr<Logger> logger, LogLevel level, LogEvent::ptr event){
    if(level >= m_level) {
        m_filestream << m_formatter->format(logger, level, event);
    }
}

bool FileLogAppeder::reopen() {
    if(m_filestream) {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !!m_filestream;
}
void StdoutLOgAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level, LogEvent::ptr event){
    if(level >= m_level){
        std::cout << m_formatter->format(logger, level, event);
    }
}

LogFormatter::LogFormatter(const std::string& pattern)
    : m_pattern(pattern){
}

std::string& LogFormatter::format(std::shared_ptr<Logger> logger, LogLevel level, LogEvent::ptr event){
    std::stringstream ss;
    for(auto& i : m_items){
        i->format(ss, logger, level, event);
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
    static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)> > s_format_items = { 
#define XX(str, C)\
        {str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt));}}
            XX(m, MessageFormatItem),
            XX(p, LevelFormatItem),
            XX(r, ElapseFormatItem),
            XX(c, NameFormatItem),
            XX(t, ThreadIdFormatItem),
            XX(n, NewLineFormatItem),
            XX(d, DateTimeFormatItem),
            XX(f, FilenameFormatItem),
            XX(l, LineFormatItem),
#undef XX
        };
    for(auto& i : vec) {
        if(std::get<2>(i) == 0){
            m_items.push_back(FormatItem::ptr(new stringFormatItem(std::get<0>(i))));
        }
        else{
            auto it = s_format_items.find(std::get<0>(i));
            if(it == s_format_items.end()) {
                m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
            }
            else{
                m_items.push_back(it->second(std::get<1>(i)));
            }
        }

        std::cout << std::get<0>(i) << " - " << std::get<1>(i) << " - " << std::get<2>(i) << std::endl;
    }
}


}

