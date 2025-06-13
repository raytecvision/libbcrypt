#ifdef _WIN32
	#include "bcrypt/BCrypt.hpp"
#else
    #include "BCrypt.hpp"
#endif
#include <iostream>

int main(){
	std::string right_password = "right_password";
	std::string wrong_password = "wrong_password";

	std::cout << "generate hash... " << std::flush << std::endl;
	std::string hash = BCrypt::generateHash(right_password, 12);
	std::cout << "hash: " << hash.c_str() << std::endl;
	std::cout << "done." << std::endl;

	std::cout << "checking right password: " << std::flush
			  << BCrypt::validatePassword(right_password,hash) << std::endl;

	std::cout << "checking wrong password: " << std::flush
			  << BCrypt::validatePassword(wrong_password,hash) << std::endl;

	return 0;
}
