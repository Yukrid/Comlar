#include <comlar.hpp>

#include <array>
#include <vector>
#include <sstream>

using namespace comlar;

int main(int argc, char** argv){

    //-> 1. Instantiation of Executor class
    Executor exec(argc, argv);



    //-> 2. Prepare variables for use in option operation
    bool flag =false;
    int  sum =0, prod =1;
    std::array<std::string, 5> strs;
    std::vector<float> vector;

    //-> 3. Definition of options
    // Example1 (-b --bool)
    {
        Option<Arg<>, bool> opt{"b", "bool", OPTIONAL, flag};
        
        opt.set_operate(opt.default_flag<true>());
        
        exec.add_option(opt);
    }
  
    // Example2 (-is1 --int_sum1)
    {
        Option<Arg<int, int, int>, int, int> opt{"is1", "int_sum_prod1", OPTIONAL, sum, prod};
        
        opt.set_operate([](const int& a_, const int& b_, const int& c_, int& sum_, int& prod_){
            
            sum_  = a_ + b_ + c_;
            prod_ = a_ * b_ * c_;
            return 0;
        });

        exec.add_option(opt);
    }

    // Example3 (-is2 --int_sum2)
    {
        Option<Arg<int, int, int>> opt{"is2", "int_sum_prod2", OPTIONAL};
        
        opt.set_function([&](const int& a_, const int& b_, const int& c_){
            
            sum  = a_ + b_ + c_;
            prod = a_ * b_* c_;
            return 0;
        });

        exec.add_option(opt);
    }


    // Example4 (-ss --strings)
    {
        Option<std::array<std::string, 5>> opt{"ss", "strings", OPTIONAL, strs};
        
        opt.set_operate(opt.default_assign());

        exec.add_option(opt);
    }


    // Example5 (-v --vector)
    {
        Option<std::vector<float>> opt{"v", "vector", OPTIONAL, vector};
        
        opt.set_operate(opt.default_assign());

        exec.add_option(opt);
    }



    //-> 4. Call the execute function of Exectutor class
    exec.add_help("Comalr Sample Code \"basic2\"");
    int result=exec.execute();
    if(result){
        std::cout<<"result: "<<result<<std::endl;
        std::exit(EXIT_FAILURE);
    }


    //-> Result
    std::cout<<"flag      : "<<(flag ? "true" : "false")<<std::endl;
    std::cout<<"sum, prod : "<<sum<<" "<<prod<<std::endl;
    for(size_t a=0; a<strs.size(); ++a)   { std::cout<<"strs["<<a<<"] :"<<strs[a]<<std::endl; }
    for(size_t a=0; a<vector.size(); ++a) { std::cout<<"vector["<<a<<"] :"<<vector[a]<<std::endl; }
    std::cout<<"result : "<<result<<std::endl;
}
