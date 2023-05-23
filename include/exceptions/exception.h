#ifndef SENGINE_ASSET_CREATOR_EXCEPTION_H
#define SENGINE_ASSET_CREATOR_EXCEPTION_H

//#include <backward.hpp>
#include <stdexcept>

namespace exceptions
{
    class Exception : public std::logic_error {
    public:
        explicit Exception(const std::string &message) : std::logic_error(message) {
//            backward::StackTrace st;
//            st.load_here(32);
//
//            backward::TraceResolver tr; tr.load_stacktrace(st);
//            for (size_t i = 0; i < st.size(); ++i) {
//                backward::ResolvedTrace trace = tr.resolve(st[i]);
//                std::cout << "#" << i
//                          << " " << trace.object_filename
//                          << " " << trace.object_function
//                          << " [" << trace.addr << "]"
//                          << std::endl;
//            }
        }
    };
}

#endif //SENGINE_ASSET_CREATOR_EXCEPTION_H
