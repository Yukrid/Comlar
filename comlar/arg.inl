//#include "arg.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::Arg<As...> Structure    )//
    //+    Member Constant Expression Function    +//
    template <typename... As>
    constexpr inline auto Arg<As...>::nof_args (void) noexcept
        -> int32_t
    {
        return sizeof...(As);
    }


    template <typename A, typename... As>
    constexpr inline auto Arg<A, As...>::nof_args (void) noexcept
        -> int32_t
    {
        return sizeof...(As)+1;
    }

    

    //+    Member Function    +//
    //_ Variable Function
    template <typename... As>
    inline auto Arg<As...>::set_check (void* f_) noexcept
        -> void
    {
        check=f_;

        return;
    }


    template <typename A, typename... As>
    inline auto Arg<A, As...>::set_check (void* f_) noexcept
        -> void
    {
        arg.set_check(f_);

        return;
    }
    

    template <typename... As>
    inline auto Arg<As...>::set_value (size_t, const char*) noexcept
        -> int
    {
        error_os<<"[comlar::Arg<As...>::set_value] Terminal function called due to invalid number of arguments."<<std::endl;
    
        return -1;
    }


    template <typename A, typename... As>
    inline auto Arg<A, As...>::set_value (size_t cnt_, const char* str_) noexcept
        -> int
    {
        if(cnt_==0){
            
            arg_val=str_conv<A>(str_);
            return 0;
        
        }else{

            return arg.set_value(cnt_-1, str_);
        }
    }

    

    //_ Constant Function
    template <typename... As> template <typename Com, typename... Bs>
    inline auto Arg<As...>::_check1 (Com& com_, const Bs&... bs_) const noexcept
        -> int
    {
        if(check) return reinterpret_cast<int(*)(const Bs&..., void*)>(check)(bs_..., check);
        else      return 0;
    }


    template <typename A, typename... As> template <typename Com, typename... Bs>
    inline auto Arg<A, As...>::_check1 (Com& com_, const Bs&... bs_) const noexcept
        -> int
    {
        return arg._check1(com_, bs_..., arg_val);
    }
    

    template <typename... As> template <typename Com, typename... Bs>
    inline auto Arg<As...>::_operate1 (Com& com_, const Bs&... bs_) const noexcept
        -> int
    {
        return com_._operate2(com_, bs_...);
    }
 

    template <typename A, typename... As> template <typename Com, typename... Bs>
    inline auto Arg<A, As...>::_operate1 (Com& com_, const Bs&... bs_) const noexcept
        -> int
    {
        return arg._operate1(com_, bs_..., arg_val);
    }


    template <typename... As> 
    inline auto Arg<As...>::stream_type_str (std::string& str_) const noexcept
        -> std::string&
    {
        return str_;
    }


    template <typename A, typename... As> 
    inline auto Arg<A, As...>::stream_type_str (std::string& str_) const noexcept
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

        return arg.stream_type_str(str_);
    }
}
