#pragma once

#include <string_view>
#include <typeinfo>

#include <fmt/format.h>

namespace sgf::utils {
    enum class LogLevel {
        Error,
        Warning,
        Info,
        Debug,
        Trace
    };

    enum class LogCategory {
        Game,
        System,
        Backend
    };

    struct LogMetadata {
        const LogCategory m_eCategory;
        const std::string_view m_sSource;

        constexpr LogMetadata(
            LogCategory eCategory,
            std::string_view m_sSource
        ):
            m_eCategory(eCategory),
            m_sSource(m_sSource)
        {
        }

        template <class SourceClass>
        static LogMetadata build(
            LogCategory eCategory
        ) {
            return LogMetadata(eCategory, typeid(SourceClass).name());
        }
    };

    class Logger {
    private:
        LogLevel m_eLevelFilter = LogLevel::Trace;
        LogCategory m_eCategoryFilter = LogCategory::Backend;

        bool isEnable(LogLevel eLevel, LogCategory eCategory);

        void log(const LogMetadata& rMetaData, LogLevel eLevel, const std::string_view sMessage);

    public:
        Logger();

        inline void setLevelFilter(
            LogLevel eLevel
        ) {
            m_eLevelFilter = eLevel;
        }

        inline void setCategoryFilter(
            LogCategory eCategory
        ) {
            m_eCategoryFilter = eCategory;
        }

        template <typename... Args>
        void trace(
            const LogMetadata& rMetaData,
            fmt::format_string<Args...> sFormat,
            Args&&... args
        ) {
            if (!isEnable(LogLevel::Trace, rMetaData.m_eCategory)) {
                return;
            }
            log(
                rMetaData,
                LogLevel::Trace,
                fmt::format(sFormat, std::forward<Args>(args)...)
            );
        }
        
        template <typename... Args>
        void debug(
            const LogMetadata& rMetaData,
            fmt::format_string<Args...> sFormat,
            Args&&... args
        ) {
            if (!isEnable(LogLevel::Debug, rMetaData.m_eCategory)) {
                return;
            }
            log(
                rMetaData,
                LogLevel::Debug,
                fmt::format(sFormat, std::forward<Args>(args)...)
            );
        }

        template <typename... Args>
        void info(
            const LogMetadata& rMetaData,
            fmt::format_string<Args...> sFormat,
            Args&&... args
        ) {
            if (!isEnable(LogLevel::Info, rMetaData.m_eCategory)) {
                return;
            }
            log(
                rMetaData,
                LogLevel::Info,
                fmt::format(sFormat, std::forward<Args>(args)...)
            );
        }
        
        template <typename... Args>
        void warning(
            const LogMetadata& rMetaData,
            fmt::format_string<Args...> sFormat,
            Args&&... args
        ) {
            if (!isEnable(LogLevel::Warning, rMetaData.m_eCategory)) {
                return;
            }
            log(
                rMetaData,
                LogLevel::Warning,
                fmt::format(sFormat, std::forward<Args>(args)...)
            );
        }
        
        template <typename... Args>
        void error(
            const LogMetadata& rMetaData,
            fmt::format_string<Args...> sFormat,
            Args&&... args
        ) {
            if (!isEnable(LogLevel::Error, rMetaData.m_eCategory)) {
                return;
            }
            log(
                rMetaData,
                LogLevel::Error,
                fmt::format(sFormat, std::forward<Args>(args)...)
            );
        }
    };
}
