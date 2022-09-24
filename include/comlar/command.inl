//#include "command.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::Core Structure    )//
    //+    Member Function    +//
    //_ Constructor
    inline Core::Core (const std::string& abrn_, const std::string& fomn_, Attribute atr_) noexcept
        : abr_name  {abrn_}
        , fom_name  {fomn_}
        , attribute {atr_}
        , message   { }
        , typestr   { }
        , supple    { }
        , field     {0}
        , choiced   {false}
    {
        return;
    }



    //_ Variable Function
    inline auto Core::set_info (const std::string& mes_, const std::string& sup_) noexcept
        -> void
    {
        message =mes_;
        supple  =sup_;

        return;
    }


    inline auto Core::set_field (Field field_) noexcept
        -> void
    {
        field =field_;

        return;
    }




    //(    comlar::Command<Arg, Ope> Structure    )//
    //_ Constructor
    template <class Arg, class Ope> template <typename... As>
    inline Command<Arg, Ope>::Command (const std::string& abrn_, const std::string& fomn_, Attribute atr_, As&... as_) noexcept
        : Core {abrn_, fomn_, atr_}
        , Arg  { }
        , Ope  {as_...}
    {
        Arg::stream_type_str(Core::typestr);

        return;
    }
    


    //_ Varialbe Function
    template <class Arg, class Ope> template <typename Func>
    inline auto Command<Arg, Ope>::set_check (Func* f_) noexcept
        -> void
    {
        Arg::set_check(reinterpret_cast<void*>(f_));

        return;
    }


    template <class Arg, class Ope>  template <typename A, class B>
    inline auto Command<Arg, Ope>::set_check (const Constraint<A, B>& cstr_) noexcept
        -> void
    {
        using Itype=typename Arg::type<0>;

        void* fp=reinterpret_cast<void*>(+[](const Itype& i_, void* ptr_){

            const A& value=*reinterpret_cast<const A*>(_capture.at(ptr_));
            int      ret;

            if(Constraint<A, B>::get_result_func(VirtualType<Itype>{ })(i_, value)){
                
                ret=0;
                
            }else{

                error_os<<"[comlar::(default_cstr::func)] Input value does not satisfy the constraint."<<std::endl;    
                ret=std::numeric_limits<int>().max();
            }

            delete reinterpret_cast<const A*>(_capture.at(ptr_));
            _capture.erase(ptr_);

            return ret;
        });

        _capture[fp]=reinterpret_cast<void*>(new A{cstr_.value});

        Arg::set_check(fp);

        return;
    }
 

    template <class Arg, class Ope>  template <typename A, class B, class... As>
    inline auto Command<Arg, Ope>::set_check (const Constraints<A, B, As...>& cstrs_) noexcept
        -> void
    {
        using Itype=typename Arg::type<0>;
        using Array=std::array<A, sizeof...(As)>;

        void* fp=reinterpret_cast<void*>(+[](const Itype& i_, void* ptr_){

            const Array& values=*reinterpret_cast<Array*>(_capture.at(ptr_));
            int          ret;

            std::cout<<i_<<" ";
            for(auto& a: values){
                std::cout<<a<<" ";
            }
            std::cout<<std::endl;
            if(Constraints<A, B, As...>::get_result_func(VirtualType<Itype>{ }, Num<sizeof...(As)>{ })(i_, values, 0)){
                
                ret=0;
                
            }else{

                error_os<<"[comlar::(default_cstr::func)] Input value does not satisfy the constraint."<<std::endl;    
                ret=std::numeric_limits<int>().max();
            }

            delete reinterpret_cast<Array*>(_capture.at(ptr_));
            _capture.erase(ptr_);

            return ret;
        });

        Array* ar_p =new Array;
        for(size_t a=0; a<sizeof...(As); ++a){
            std::cout<<"Get:"<<cstrs_.get_value(a)<<std::endl;
            ar_p->at(a)=cstrs_.get_value(a);
        }
        _capture[fp]=reinterpret_cast<void*>(ar_p);

        Arg::set_check(fp);

        return;
    }
           
    
    template <class Arg, class Ope> template <typename Func>
    inline auto Command<Arg, Ope>::set_operate (Func* f_) noexcept
        -> void
    {
        Ope::set_operate(reinterpret_cast<void*>(f_));

        return;
    }
    

    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::_nof_args (void) noexcept
        -> size_t
    {
        return Arg::nof_args();
    }
 

    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::set_value (size_t num_, const char* str_) noexcept
        -> int
    {
        return Arg::set_value(num_, str_);
    }


    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::_operate (void) noexcept
        -> int
    {
        return Arg::_operate1(*this);
    }


    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::_check (void) noexcept
        -> int
    {
        return Arg::_check1(*this);
    }
}
