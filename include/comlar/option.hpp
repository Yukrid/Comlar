#ifndef COMLAR_OPTION_HPP
#define COMLAR_OPTION_HPP

#include "forward.hpp"
#include "arg.hpp"
#include "ope.hpp"
//#include "constraint.hpp"

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

        //_ Destructor
        virtual inline ~Core (void) noexcept =default;
    
        //_ Variable Function
        inline auto set_info  (const std::string&, const std::string& ="") noexcept -> void;
        inline auto set_field (Field)                                      noexcept -> void;

        virtual inline auto set_value (size_t, const char*) noexcept -> int    =0;
        virtual inline auto nof_args  (void)                noexcept -> size_t =0;
        virtual inline auto operate   (void)                noexcept -> int    =0;
        virtual inline auto function  (void)                noexcept -> int    =0;
    };



    //(    comlar::Option<As...> Structure Template    )//
    template <typename... As>
    struct Option : public Core{

        //+    Member Constant Expression Function    +//
        inline static constexpr auto default_assign (void) noexcept -> std::function<int(const std::tuple<As...>&, std::tuple<As&...>&)>;

        //+    Member Variable    +//
        Arg<As...>             args;
        Ope<Arg<As...>, As...> ope;

        //+    Member Function    +//
        //_ Constructor
        inline Option (const std::string&, const std::string&, Attribute, As&...)             noexcept;
        inline Option (const std::string&, const std::string&, Attribute, std::tuple<As...>&) noexcept;
       
        //_ Destructor
        inline ~Option (void) noexcept override =default;

        //_ Variable Function
        inline auto set_value (size_t, const char*) noexcept -> int    override;
        inline auto nof_args  (void)                noexcept -> size_t override;
        inline auto operate   (void)                noexcept -> int    override;
        inline auto function  (void)                noexcept -> int    override;

        inline void set_function (const typename Arg<As...>::FuncType1&)      noexcept;
        inline void set_function (const typename Arg<As...>::FuncType2&)      noexcept;
        inline void set_operate  (const typename Ope<Arg<As...>, As...>::FuncType1&) noexcept;
        inline void set_operate  (const typename Ope<Arg<As...>, As...>::FuncType2&) noexcept;
    };



    //(    comlar::Option<Arg<>, bool> Specialized Structure Template    )//
    template <>
    struct Option<Arg<>, bool> : public Core{
 
        //+    Member Constant Expression Function    +//
        template <bool B> inline static auto default_flag (void) noexcept -> std::function<int(bool&)>;


        //+    Member Variable    +//
        Arg<>            args;
        Ope<Arg<>, bool> ope;


        //+    Member Function    +//
        //_ Constructor
        inline Option (const std::string&, const std::string&, Attribute, bool&)             noexcept;
        inline Option (const std::string&, const std::string&, Attribute, std::tuple<bool>&) noexcept;
 
        //_ Destructor
        inline ~Option (void) noexcept override =default;
    
        //_ Variable Function
        inline auto set_value (size_t, const char*) noexcept -> int    override;
        inline auto nof_args  (void)                noexcept -> size_t override;
        inline auto operate   (void)                noexcept -> int    override;
        inline auto function  (void)                noexcept -> int    override;

        inline void set_function (const typename Arg<>::FuncType1&)            noexcept;
        inline void set_function (const typename Arg<>::FuncType2&)            noexcept;
        inline void set_operate  (const typename Ope<Arg<>, bool>::FuncType1&) noexcept;
        inline void set_operate  (const typename Ope<Arg<>, bool>::FuncType2&) noexcept;
    };



    //(    comlar::Option<Arg<As...>, Bs...> Specialized Structure Template    )//
    template <typename... As, typename... Bs>
    struct Option<Arg<As...>, Bs...> : public Core{
        
        //+    Member Variable    +//
        Arg<As...>             args;
        Ope<Arg<As...>, Bs...> ope;

        //+    Member Function    +//
        //_ Constructor
        inline Option (const std::string&, const std::string&, Attribute, Bs&...)             noexcept;
        inline Option (const std::string&, const std::string&, Attribute, std::tuple<Bs...>&) noexcept;
 
        //_ Destructor
        inline ~Option (void) noexcept override =default;
    
        //_ Variable Function
        inline auto set_value (size_t, const char*) noexcept -> int    override;
        inline auto nof_args  (void)                noexcept -> size_t override;
        inline auto operate   (void)                noexcept -> int    override;
        inline auto function  (void)                noexcept -> int    override;

        inline void set_function (const typename Arg<As...>::FuncType1&)             noexcept;
        inline void set_function (const typename Arg<As...>::FuncType2&)             noexcept;
        inline void set_operate  (const typename Ope<Arg<As...>, Bs...>::FuncType1&) noexcept;
        inline void set_operate  (const typename Ope<Arg<As...>, Bs...>::FuncType2&) noexcept;
    };
}

#include "option.inl"

#endif
