#include <comlar.hpp>
#include <sstream>

using namespace comlar;

int main(int argc, char** argv){

    //-> 1. Instantiation of Executor class
    Executor exec(argc, argv);



    //-> 2. Prepare variables for use in option operation
    float f_val1;
    float f_val2;
    int   i_val;  char c_val;



    //-> 3. Definition of options
    // Example1 (-f1 --float1)
    {
        Option<float> opt{"f1", "float1", OPTIONAL, f_val1};
        
        opt.set_operate(opt.default_assign());
        
        exec.add_option(opt);
    }
  
    // Example2 (-f2 --float2)
    float min=-1.f, max=1.f;
    {
        Option<float> opt{"f2", "float2", OPTIONAL, f_val2};
        
        opt.set_function([&](const float& input_){
            if(min<input_ and input_<max) return 0;
            else                          return 1;
        });

        opt.set_operate(opt.default_assign());

        exec.add_option(opt);
    }

    // Example3 (-ic --intchar)
    {
        Option<int, char> opt{"ic", "intchar", OPTIONAL, i_val, c_val};

        opt.set_operate(opt.default_assign());
        
        exec.add_option(opt);
    }


    //-> 4. Call the execute function of Exectutor class
    exec.add_help();
    int result=exec.execute();
    if(result){
        std::cout<<"result: "<<result<<std::endl;
        std::exit(EXIT_FAILURE);
    }


    //-> Result
    std::cout<<"f_val1      : "<<f_val1<<std::endl;
    std::cout<<"f_val2      : "<<f_val2<<std::endl;
    std::cout<<"i_val, c_val: "<<i_val<<" "<<c_val<<std::endl;
    std::cout<<"result      : "<<result<<std::endl;
}
