#ifndef COMLAR_EXECUTOR_HPP
#define COMLAR_EXECUTOR_HPP

#include "forward.hpp"
#include "command.hpp"
#include <vector>
#include <unordered_map>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Executor Structure    )//
    struct Executor{
        
        //+    Member Varialbe    +//
        int                                    argc;
        char**                                 argv;
        std::vector<Core*>                     cores; 
        std::unordered_map<std::string, Core*> abrn_tb;
        std::unordered_map<std::string, Core*> fomn_tb;
        std::vector<std::string>               fields;
        std::vector<Core*>                     required;
        std::string                            help_head;


        //+    Member Function    +//
        //_ Constructor
        inline Executor (int, char**) noexcept;
        
        //_ Destructor
        inline ~Executor (void) noexcept;

        //_ Variable Function
        template <class Com> inline auto add_command (Com& com_)                                        noexcept -> Core*;
                             inline auto add_field   (const std::string&)                               noexcept -> Field;
                             inline auto add_help    (const std::string& ="", std::ostream& =std::cout) noexcept -> Core*;
                             inline auto execute     (void)                                             noexcept -> int;
    };
}

#include "executor.inl"

#endif
