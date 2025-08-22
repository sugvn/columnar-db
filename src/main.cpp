#include <expected>
#include <iostream>


std::expected<int,std::string> divide(int a,int b){
        if(b==0) return std::unexpected("Divide by 0 error");
        return a/b;
}



int main(){
        auto res=divide(5,0);
        if(res){
                std::cout<<"The result is"<<*res;
        }else {
                std::cout<<res.error();
        }
        return 0;
}
