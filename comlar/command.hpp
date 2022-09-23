#ifndef COMLAR_COMMAND_HPP
#define COMLAR_COMMAND_HPP

#include "forward.hpp"
#include "arg.hpp"
#include "ope.hpp"
#include "constraint.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Core Structure    )//
    struct Core{
        
        //+    Member Varialbe    +//
        std::string abr_name;
        std::string fom_name;
        Attribute   attribute;

        std::string message;
        std::string typestr;
        std::string supple;
        Field       field;
        bool        choiced;

        //+    Member Function    +//
        //_ Constructor
        inline Core (const std::string&, const std::string&, Attribute) noexcept;

        //_ Variable Function
        inline auto set_info  (const std::string&, const std::string& ="") noexcept -> void;
        inline auto set_field (Field)                                      noexcept -> void;

        virtual inline auto  set_value (size_t, const char*) noexcept -> int    =0;
        virtual inline auto _nof_args  (void)                noexcept -> size_t =0;
        virtual inline auto _check     (void)                noexcept -> int    =0;
        virtual inline auto _operate   (void)                noexcept -> int    =0;
    };



    //(    comlar::Command<Arg, Ope> Structure    )//
    template <class Arg, class Ope>
    struct Command : public Core, Arg, Ope{
        
        //+    Member Function    +//
        //_ Constructor
        template <typename... As> inline Command (const std::string&, const std::string&, Attribute, As&...) noexcept;

        //_ Variable Function
        template <typename Func>                    inline auto  set_check   (Func*)                           noexcept -> void; 
        template <typename A, class B>              inline auto  set_check   (const Constraint<A, B>&)         noexcept -> void; 
        template <typename A, class B, class... As> inline auto  set_check   (const Constraints<A, B, As...>&) noexcept -> void; 
        template <typename Func>                    inline auto  set_operate (Func*)                           noexcept -> void; 
        
        inline auto  set_value (size_t, const char*) noexcept -> int    override;
        inline auto _nof_args  (void)                noexcept -> size_t override;
        inline auto _operate   (void)                noexcept -> int    override;
        inline auto _check     (void)                noexcept -> int    override;
    };
}

#include "command.inl"

#endif
