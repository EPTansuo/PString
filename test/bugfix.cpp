#include <pstring.h>
#include <iostream>

#define FAILED "\033[31mFAILED\033[0m"
#define SUCC   "\033[32mSUCC\033[0m"


void print_result(const PString& input, const PString& expected, const PString& result, const PString &method){
	if(expected != result){
		std::cout << input.repr() << "."+ method << FAILED << std::endl;
		std::cout << "expected: " << expected.repr() << std::endl;
		std::cout << "result:   " << result.repr() << std::endl;
	}
	else{
		std::cout << input.repr() << "."+ method + " = " + result.repr() << SUCC << std::endl;
	}
}

void bug_rsplit(){
	{
		PString input= " \r\n\thello world\t\r\n ";
		std::vector expected = {PString(" \r\n\thello"), PString("world")};


		bool veri = input.rsplit("",  1).size() == 2 
							&& input.rsplit("",  1)[0] == expected[0]   
								&& input.rsplit("",  1)[1] == expected[1];

		if(!veri){
						std::cout << input.repr() << ".rsplit(maxsplit=1)" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << input.rsplit("", 1) <<std::endl;
		}
		else        std::cout << input.repr() << ".rsplit(maxsplit=1)" SUCC  << std::endl;
	}

	{
		PString input = "\t\n\r\x0b\x0c";
		std::vector<PString> expected = {};

		bool veri = input.rsplit("", 1).size() == 0;
		if(!veri){
						std::cout << input.repr() << ".rsplit(maxsplit=1)" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << input.rsplit("", 1) <<std::endl;
		}
		else        std::cout << input.repr() << ".rsplit(maxsplit=1)" SUCC  << std::endl;
	}

}

void bug_strip(){
	{
		PString input= " \r\n\v\fhello world\t\r\n \x0b\x0c";
		PString expected = "hello world";

		PString result = input.strip();
		print_result(input, expected, result, "strip()");
	}
	{
		PString input= "'\"\\";
		PString expected = "'\"\\";

		PString result = input.strip();
		print_result(input, expected, result, "strip()");
	}
}

void bug_rstrip(){
	{
		PString input= " \r\n\thello world\t\r\n ";
		PString expected = " \r\n\thello world";


		auto result = input.rstrip();

		print_result(input, expected, result, "rstrip()");
	}
	{
		PString input= "\t\n\r\x0b\x0c";
		PString expected = "";

		auto result = input.rstrip();

		print_result(input, expected, result, "rstrip()");
	}

}

void bug_split(){
	{
		PString input = "\t\n\r\x0b\x0c";
		std::vector<PString> expected = {};
		bool veri = input.rsplit("", 1).size() == 0;
		if(!veri){
						std::cout << input.repr() << ".split()" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << input.rsplit("", 1) <<std::endl;
		}
		else        std::cout << input.repr() << ".split()" SUCC  << std::endl;

	}
}

void bug_list(){
	bug_rstrip();
	bug_rsplit();
	bug_strip();
	bug_split();
}
