#include "sgf/utils/logger.h"

#include <spdlog/spdlog.h>

namespace sgf::utils {
    constexpr std::string_view levelToString(LogLevel eLevel) {
        switch (eLevel) {
            case LogLevel::Trace:   return "Trace";
            case LogLevel::Debug:   return "Debug";
            case LogLevel::Info:    return "Info";
            case LogLevel::Warning: return "Warning";
            case LogLevel::Error:   return "Error";
        }
        return "";
    }

    constexpr std::string_view categoryToString(LogCategory eCategory) {
        switch (eCategory) {
            case LogCategory::Game:     return "Game";
            case LogCategory::System:   return "System";
            case LogCategory::Backend:  return "Backend";
        }
        return "";
    }

    Logger::Logger() {
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%n]%v");
    }

    bool Logger::isEnable(
        LogLevel eLevel,
        LogCategory eCategory
    ) {
        return eLevel <= m_eLevelFilter && eCategory <= m_eCategoryFilter;
    }

    void Logger::log(
        const LogMetadata &rMetaData,
        LogLevel eLevel,
        const std::string_view sMessage
    ) {
        switch (eLevel) {
            case LogLevel::Trace:
                spdlog::trace(
                    "[{}][{}][{}] {}",
                    levelToString(eLevel),
                    categoryToString(rMetaData.m_eCategory),
                    rMetaData.m_sSource,
                    sMessage
                );
                break;
            case LogLevel::Debug:
                spdlog::debug(
                    "[{}][{}][{}] {}",
                    levelToString(eLevel),
                    categoryToString(rMetaData.m_eCategory),
                    rMetaData.m_sSource,
                    sMessage
                );
                break;
            case LogLevel::Info:
                spdlog::info(
                    "[{}][{}][{}] {}",
                    levelToString(eLevel),
                    categoryToString(rMetaData.m_eCategory),
                    rMetaData.m_sSource,
                    sMessage
                );
                break;
            case LogLevel::Warning:
                spdlog::warn(
                    "[{}][{}][{}] {}",
                    levelToString(eLevel),
                    categoryToString(rMetaData.m_eCategory),
                    rMetaData.m_sSource,
                    sMessage
                );
                break;
            case LogLevel::Error:
                spdlog::error(
                    "[{}][{}][{}] {}",
                    levelToString(eLevel),
                    categoryToString(rMetaData.m_eCategory),
                    rMetaData.m_sSource,
                    sMessage
                );
                break;
        }
    }
}
