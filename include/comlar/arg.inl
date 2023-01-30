#ifndef COMLAR_ARG_INL
#define COMLAR_ARG_INL

#include "arg.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::ArgShaow<As...> Structure    )//
    //_ Variable Function
    template <typename... As> template <typename... Bs>
    auto ArgShadow<As...>::set_value (std::tuple<Bs...>&, size_t, const char*) noexcept
        -> int
    {
        error_os<<"[comlar::ArgShadow<As...>::set_value] Terminal function called due to invalid number of arguments."<<std::endl;
    
        return -1;

    }


    template <typename A, typename... As> template <typename... Bs>
    auto ArgShadow<A, As...>::set_value (std::tuple<Bs...>& tp_, size_t cnt_, const char* str_) noexcept
        -> int
    {
        if(cnt_==0){
            
            std::get<sizeof...(Bs)-sizeof...(As)-1>(tp_)=str_conv<A>(str_);
            return 0;

        }else{

            return shadow.set_value(tp_, cnt_-1, str_);
        }
    }



    //_ Constant Function
    template <typename... As> 
    inline auto ArgShadow<As...>::stream_type_str (std::string& str_) const noexcept
        -> std::string&
    {
        return str_;
    }


    template <typename A, typename... As> 
    inline auto ArgShadow<A, As...>::stream_type_str (std::string& str_) const noexcept
        -> std::string&
    {
        std::string typestr=std::string(typeid(A).name());
        if(typestr==std::string(typeid(std::string).name())){

            if(str_=="") str_+="str";
            else         str_+=std::string{", "}+"str";

        }else if(typestr.length()>5){

            if(str_=="") str_+=typestr.substr(0, 5);
            else         str_+=std::string{", "}+typestr.substr(0, 5);

        }else{
            
            if(str_=="") str_+=typeid(A).name();
            else         str_+=std::string{", "}+typeid(A).name();
        }

        return shadow.stream_type_str(str_);
    }


    //(    comlar::Arg<As...> Structure    )//
    //+    Member Constant Expression Function    +//
    template <typename... As>
    constexpr inline auto Arg<As...>::nof_args (void) noexcept
        -> int32_t
    {
        return sizeof...(As);
    }

    

    //+    Member Function    +//
    //_ Variable Function
    template <typename... As>
    inline auto Arg<As...>::set_function (const FuncType1& f_) noexcept
        -> void
    {
        func1   = f_;
        func_id = 1;

        return;
    }


    template <typename... As>
    inline auto Arg<As...>::set_function (const FuncType2& f_) noexcept
        -> void
    {
        func2   = f_;
        func_id = 2;

        return;
    }


    template <typename... As>
    inline auto Arg<As...>::set_value (size_t cnt_, const char* str_) noexcept
        -> int
    {
        return shadow.set_value(tuple, cnt_, str_);
    }

    

    //_ Constant Function
    template <typename... As>
    inline auto Arg<As...>::function (void) const noexcept
        -> int
    {
        switch(func_id){
            case 1:  return std::apply(func1, tuple);
            case 2:  return func2(tuple);
            default: return 0;
        }
    }


    template <typename... As> 
    inline auto Arg<As...>::stream_type_str (std::string& str_) const noexcept
        -> std::string&
    {
        return shadow.stream_type_str(str_);
    }




    //(    comlar::Arg<std::array<A, S>> Structure    )//
    //+    Member Constant Expression Function    +//
    template <typename A, size_t S>
    constexpr inline auto Arg<std::array<A, S>>::nof_args (void) noexcept
        -> int32_t
    {
        return S;
    }

    

    //+    Member Function    +//
    //_ Variable Function
    template <typename A, size_t S>
    inline auto Arg<std::array<A, S>>::set_function (const FuncType1& f_) noexcept
        -> void
    {
        func1   = f_;
        func_id = 1;

        return;
    }


    template <typename A, size_t S>
    inline auto Arg<std::array<A, S>>::set_value (size_t cnt_, const char* str_) noexcept
        -> int
    {
        array.at(cnt_)=str_conv<A>(str_);

        return 0;
    }

    

    //_ Constant Function
    template <typename A, size_t S>
    inline auto Arg<std::array<A, S>>::function (void) const noexcept
        -> int
    {
        if(func_id) return func1(array);
        else        return 0;
    }


    template <typename A, size_t S> 
    inline auto Arg<std::array<A, S>>::stream_type_str (std::string& str_) const noexcept
        -> std::string&
    {
        std::string typestr=std::string(typeid(A).name());
        if(typestr==std::string(typeid(std::string).name())){

            if(str_=="") str_+="str["+std::to_string(S)+"]";
            else         str_+=std::string{", "}+"str["+std::to_string(S)+"]";

        }else if(typestr.length()>5){

            if(str_=="") str_+=typestr.substr(0, 5)+"["+std::to_string(S)+"]";
            else         str_+=std::string{", "}+typestr.substr(0, 5)+"["+std::to_string(S)+"]";

        }else{
            
            if(str_=="") str_+=std::string(typeid(A).name())+"["+std::to_string(S)+"]";
            else         str_+=std::string{", "}+typeid(A).name()+"["+std::to_string(S)+"]";
        }

        return str_;
    }



    //(    comlar::Arg<std::vector<A>> Structure    )//
    //+    Member Constant Expression Function    +//
    template <typename A>
    constexpr inline auto Arg<std::vector<A>>::nof_args (void) noexcept
        -> int32_t
    {
        return -1;
    }

    

    //+    Member Function    +//
    //_ Variable Function
    template <typename A>
    inline auto Arg<std::vector<A>>::set_function (const FuncType1& f_) noexcept
        -> void
    {
        func1   = f_;
        func_id = 1;

        return;
    }
    

    template <typename A>
    inline auto Arg<std::vector<A>>::set_value (size_t cnt_, const char* str_) noexcept
        -> int
    {
        vector.resize(cnt_+1);
        vector.at(cnt_)=str_conv<A>(str_);

        return 0;
    }
    
    

    //_ Constant Function
    template <typename A>
    inline auto Arg<std::vector<A>>::function (void) const noexcept
        -> int
    {
        if(func_id) return func1(vector);
        else        return 0;
    }


    template <typename A> 
    inline auto Arg<std::vector<A>>::stream_type_str (std::string& str_) const noexcept
        -> std::string&
    {
        std::string typestr=std::string(typeid(A).name());
        std::string intstr=std::string(typeid(int32_t).name());
        if(typestr==std::string(typeid(std::string).name())){

            str_+=intstr+", str[i]";

        }else if(typestr.length()>5){

            str_+=intstr+", "+typestr.substr(0, 5)+"[i]";

        }else{
            
            str_+=intstr+", "+std::string(typeid(A).name())+"[i]";
        }

        return str_;
    }

}
#endif
