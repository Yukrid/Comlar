#ifndef COMLAR_EXECUTOR_INL
#define COMLAR_EXECUTOR_INL

#include "executor.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::Executor Structure    )//
    //_ Constructor
    inline Executor::Executor (int argc_, char** argv_) noexcept
        : argc      {argc_}
        , argv      {argv_}
        , cores     { }
        , abrn_tb   { }
        , fomn_tb   { }
        , fields    {1}
        , required  { }
        , help_head { }
    {
        return;
    }



    //_ Destructor
    inline Executor::~Executor (void) noexcept
    {
        for(Core* core_p : cores){
            
            std::free(core_p);
        }

        return;
    }


    //_ Variable Function
    template <class Opt>
    inline auto Executor::add_option (Opt& com_) noexcept
        -> Core*
    {
        if(abrn_tb.find(com_.abr_name)!=abrn_tb.end()){
            
            error_os<<"[comlar::Executor::add_option] -"<<com_.abr_name<<" already exists as another option."<<std::endl;
            return nullptr;

        }else{
    
            if(fomn_tb.find(com_.fom_name)!=fomn_tb.end()){
            
                error_os<<"[comlar::Executor::add_option] --"<<com_.fom_name<<" already exists as another option."<<std::endl;
                return nullptr;

            }else{
        
                cores.push_back(nullptr);
                cores[cores.size()-1]=(reinterpret_cast<Core*>(std::malloc(sizeof com_)));
                Core& core=*cores[cores.size()-1]; 
                new(reinterpret_cast<Opt*>(&core)) Opt(com_);
    
                abrn_tb[core.abr_name]=&core;
                fomn_tb[core.fom_name]=&core;
                if(core.attribute==REQUIRED) required.push_back(&core);

                return &core;
            }
        }
    }


    inline auto Executor::add_field (const std::string& f_str_) noexcept
        -> Field
    {
        fields.push_back(f_str_);

        return fields.size()-1;
    }


    inline auto Executor::add_help (const std::string& head_, std::ostream& os_) noexcept
        -> Core*
    {
        help_head=head_;

        Option<Arg<>, Executor, std::ostream> com{"h", "help", OPTIONAL, *this, os_};
        
        com.set_info("show help");
        com.set_operate([](Executor& exec_, std::ostream& os_){
           
            os_<<exec_.help_head<<std::endl;

            for(size_t a=0; a<exec_.fields.size(); ++a){
                
                if(a) os_<<"["<<exec_.fields[a]<<"]"<<std::endl;
                
                size_t abrn_len =0;
                size_t fomn_len =0;
                bool   atr_flag =false;
                size_t mess_len =0;
                size_t typs_len =0;
                size_t supp_len =0;

                for(const Core* core : exec_.cores){
                
                    if(core->field==a){
                        
                        if(core->abr_name.length()>abrn_len) abrn_len =core->abr_name.length();
                        if(core->fom_name.length()>fomn_len) fomn_len =core->fom_name.length();
                        if(core->message.length()>mess_len)  mess_len =core->message.length();
                        if(core->typestr.length()>typs_len)  typs_len =core->typestr.length();
                        if(core->supple.length()>supp_len)   supp_len =core->supple.length();
                        
                        if(!atr_flag and core->attribute==OPTIONAL) atr_flag =true;
                    }
                }


                for(const Core* core : exec_.cores){
                    
                    if(core->field==a){
                        
                        os_<<" -"<<core->abr_name<<std::string(abrn_len-core->abr_name.length(), ' ')<<"  ";
                        os_<<"--"<<core->fom_name<<std::string(fomn_len-core->fom_name.length(), ' ')<<"  ";
                        os_      <<core->message <<std::string(mess_len-core->message.length(), ' ')<<"  ";
                        if(atr_flag){
                            if(core->attribute==OPTIONAL) os_<<"(Opt.)"<<"  ";
                            else                          os_<<"      "<<"  ";
                        }
                        if(core->typestr==""){
                            os_<<std::string(typs_len+2, ' ')<<"  ";
                        }else{
                            os_<<'<'<<core->typestr<<'>'<<std::string(typs_len-core->typestr.length(), ' ')<<"  ";
                        }
                        os_<<core->supple<<std::string(supp_len-core->supple.length(), ' ')<<std::endl;
                    }
                }

                os_<<std::endl;
            }

            std::exit(EXIT_SUCCESS);

            return 0;
        });
        
        return add_option(com);
    } 


    inline auto Executor::execute (void) noexcept -> int
    {
        enum State{
        
            EXPECT_COM, EXPECT_ARG

        } state=EXPECT_COM;
        

        Core*  core;
        int32_t arg_num=0;
        size_t arg_cnt=0;

        for(uint32_t a=1; a<argc; ++a){
            
            std::string str(argv[a]);

            switch(state){

                case EXPECT_COM:
                {
                    if(str.length()<2 or str[0]!='-'){
                        
                        error_os<<"[comlar::Executor::execute] "<<str<<" is not expected."<<std::endl;
                        return -2;
                    }

                    
                    if(str[1]=='-'){

                        if(str.length()<3){
                        
                            error_os<<"[comlar::Executor::execute] "<<str<<" is not expected."<<std::endl;
                            return -2;
                        
                        }else{
                            
                            if(fomn_tb.find(str.substr(2))==fomn_tb.end()){

                                error_os<<"[comlar::Executor::execute] "<<str<<" is unknwon option."<<std::endl;
                                return -3;

                            }else{
    
                                core=fomn_tb[str.substr(2)];
                                
                                if(core->choiced){
                                    error_os<<"[comlar::Executor::execute] -"<<core->abr_name<<" --"<<core->fom_name<<" has already been called."<<std::endl;
                                }
                                core->choiced=true;
                                arg_num=core->nof_args();

                            }
                        }
                    
                    }else{

                        if(abrn_tb.find(str.substr(1))==abrn_tb.end()){

                            error_os<<"[comlar::Executor::execute] "<<str<<" is unknwon option."<<std::endl;
                                return -3;

                        }else{
    
                            core=abrn_tb[str.substr(1)];

                            if(core->choiced){
                                error_os<<"[comlar::Executor::execute] "<<str<<" has already been called."<<std::endl;
                            }
                            core->choiced=true;
                            arg_num=core->nof_args();
                        }
                    }
                    
                    if(arg_num){
                        
                        if(a==argc-1){
                            
                            error_os<<"[comlar::Executor::execute] -"<<core->abr_name<<" --"<<core->fom_name<<" should have more "<<arg_num-arg_cnt<<" argments."<<std::endl;
                            return -5;
                        }
                        
                        state=EXPECT_ARG;

                    }else{

                        if(int eval =core->function()){
                                
                            error_os<<"[comlar::Executor::execute] Error detected in functioning -"<<core->abr_name<<" --"<<core->fom_name<<" ("<<eval<<")."<<std::endl;
                            return eval;
                        }
                        if(int eval =core->operate()){
                                
                            error_os<<"[comlar::Executor::execute] Error detected in operating -"<<core->abr_name<<" --"<<core->fom_name<<" ("<<eval<<")."<<std::endl;
                            return eval;
                        }
                    }

                    break;
                }

                case EXPECT_ARG:
                {

                    if(arg_num<0){
                        
                        arg_num=std::stoull(str);
                    }else{
                        core->set_value(arg_cnt++, str.c_str());
                    }

                    if(arg_cnt==arg_num){
                        
                        state=EXPECT_COM;
                        
                        if(int eval =core->function()){
                                
                            error_os<<"[comlar::Executor::execute] Error detected in functioning -"<<core->abr_name<<" --"<<core->fom_name<<" ("<<eval<<")."<<std::endl;
                            return eval;
                        }
                        if(int eval =core->operate()){
                                
                            error_os<<"[comlar::Executor::execute] Error detected in operating -"<<core->abr_name<<" --"<<core->fom_name<<" ("<<eval<<")."<<std::endl;
                            return eval;
                        }
                        arg_cnt=0;
                    
                    }else if(a==argc-1){
                            
                        error_os<<"[comlar::Executor::execute] -"<<core->abr_name<<" --"<<core->fom_name<<" should have more "<<arg_num-arg_cnt<<" argments."<<std::endl;
                        return -5; 
                    }

                    break;
                }
            }
        }


        for(Core* core : required){
            
            if(!core->choiced){
                
                error_os<<"[comlar::Executor::execute] -"<<core->abr_name<<" --"<<core->fom_name<<" is required but not inputed."<<std::endl;
                return -4;
            }
        }
        
        return 0;
    }
}
#endif
