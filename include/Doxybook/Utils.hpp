#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace Doxybook2 {
    namespace Utils {
        namespace Detail {
            inline void join(std::stringstream& ss, const std::string& first) {
                ss << first;
            }

            template <typename... Args>
            inline void join(std::stringstream& ss, const std::string& first, const Args&... args) {
#ifdef _WIN32
                ss << first << "\\";
#else
                ss << first << "/";
#endif
                Detail::join(ss, args...);
            }
        } // namespace Detail

        template <typename... Args> inline std::string join(const Args&... args) {
            std::stringstream ss;
            Detail::join(ss, args...);
            return ss.str();
        }

        inline std::string filename(const std::string& path) {
            const auto a = path.find_last_of('/');
            const auto b = path.find_last_of('\\');
            if (a != std::string::npos && b != std::string::npos) {
                return path.substr(std::max<size_t>(a, b) + 1);
            } else if (a != std::string::npos) {
                return path.substr(a + 1);
            } else if (b != std::string::npos) {
                return path.substr(b + 1);
            } else {
                return path;
            }
        }

        std::string escape(std::string str);
        std::string title(std::string str);
        std::string toLower(std::string str);
        std::string safeAnchorId(std::string str, bool replaceUnderscores);
        std::string namespaceToPackage(std::string str);
        std::string date(const std::string& format);
        std::string stripNamespace(const std::string& format);
        std::string stripAnchor(const std::string& str);
        std::string extractQualifiedNameFromFunctionDefinition(const std::string& str);
        std::vector<std::string> split(const std::string& str, const std::string& delim);
        void createDirectory(const std::string& path);
        std::string normalizeLanguage(const std::string& language);
        std::string replaceNewline(std::string str);
    } // namespace Utils
} // namespace Doxybook2
