#ifndef COMLAR_ARG_HPP
#define COMLAR_ARG_HPP

#include "forward.hpp"

#include <array>
#include <vector>
#include <functional>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::ArgShadow<As...> Structure Template    )//
    template <typename... As>
    struct ArgShadow{

        //+    Member Function    +//
        //_ Variable Function
        template<typename... Bs> inline auto set_value (std::tuple<Bs...>&, size_t, const char*) noexcept -> int;

        //_ Constnat Function
        inline auto stream_type_str (std::string& str_) const noexcept -> std::string&;
    };
    

    
    //(    comlar::ArgShadow<A, As...> Specialized Structure Template   )//
    template <typename A, typename... As>
    struct ArgShadow<A, As...>{

        //+    Member Variable    +//
        ArgShadow<As...> shadow;


        //+    Member Function    +//
        //_ Variable Function
        template<typename... Bs> inline auto set_value (std::tuple<Bs...>&, size_t, const char*) noexcept -> int;

        //_ Constant Function
        inline auto stream_type_str (std::string& str_) const noexcept -> std::string&;
    };
    


    //(    comlar::Arg<As...> Structure Template    )//
    template <typename... As>
    struct Arg{
        
        //+    Member Constant Expression Function    +//
        static constexpr inline auto  nof_args (void)              noexcept -> int32_t;
        

        //+    Alias   +//
        using FuncType1 = std::function<int(const As&...)>;
        using FuncType2 = std::function<int(const std::tuple<As...>&)>;


        //+    Member Varialbe    +//
        FuncType1         func1;
        FuncType2         func2;
        uint8_t           func_id = 0;
        std::tuple<As...> tuple;
        ArgShadow<As...>  shadow;


        //+    Member Function    +//
        //_ Variable Function
        inline auto set_function (const FuncType1&)    noexcept -> void; 
        inline auto set_function (const FuncType2&)    noexcept -> void; 
        inline auto set_value    (size_t, const char*) noexcept -> int;

        //_ Constant Function
        inline auto function        (void)              const noexcept -> int;
        inline auto stream_type_str (std::string& str_) const noexcept -> std::string&;
    };


    //(    comlar::Arg<std::array<A, S>> Structure Template    )//
    template <typename A, size_t S>
    struct Arg<std::array<A, S>>{
        
        //+    Member Constant Expression Function    +//
        static constexpr inline auto  nof_args (void) noexcept -> int32_t;
        

        //+    Alias   +//
        using FuncType1 = std::function<int(const std::array<A, S>&)>;
        using FuncType2 = std::function<void(void)>;


        //+    Member Varialbe    +//
        FuncType1        func1;
        uint8_t          func_id = 0;
        std::array<A, S> array;


        //+    Member Function    +//
        //_ Variable Function
        inline auto set_function (const FuncType1&)    noexcept -> void; 
        inline auto set_value    (size_t, const char*) noexcept -> int;

        //_ Constant Function
        inline auto function        (void)              const noexcept -> int;
        inline auto stream_type_str (std::string& str_) const noexcept -> std::string&;
    };



    //(    comlar::Arg<std::vector<A>> Structure Template    )//
    template <typename A>
    struct Arg<std::vector<A>>{
        
        //+    Member Constant Expression Function    +//
        static constexpr inline auto  nof_args (void) noexcept -> int32_t;
        
        //+    Alias   +//
        using FuncType1 = std::function<int(const std::vector<A>&)>;
        using FuncType2 = std::function<void(void)>;


        //+    Member Varialbe    +//
        FuncType1      func1;
        uint8_t        func_id = 0;
        std::vector<A> vector;

        //+    Member Function    +//
        //_ Variable Function
        inline auto set_function (const FuncType1&)    noexcept -> void; 
        inline auto set_value    (size_t, const char*) noexcept -> int;

        //_ Constant Function
        inline auto function        (void)              const noexcept -> int;
        inline auto stream_type_str (std::string& str_) const noexcept -> std::string&;
    };

}

#include "arg.inl"

#endif
