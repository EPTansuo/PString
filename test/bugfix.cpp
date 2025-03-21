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

	{
		PString input = "\x0bW4inVjunmlP\t";
		std::vector<PString> expected = {PString("W4inVjunmlP")};
		auto result = input.rsplit("", 1);
		bool veri = result.size() == 1 && result[0] == expected[0];
		if(!veri){
						std::cout << input.repr() << ".rsplit(maxsplit=1)" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << result <<std::endl;
		}
		else        std::cout << input.repr() << ".rsplit(maxsplit=1)" SUCC  << std::endl;
	}

	{
		PString input = "9B7";
		std::vector<PString> expected = {PString("9B7")};
		auto result = input.rsplit("", 1);
		bool veri = result.size() == 1 && result[0] == expected[0];
		if(!veri){
						std::cout << input.repr() << ".rsplit(maxsplit=1)" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << result <<std::endl;
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
	{
		PString input = "4t\x0cGF\x0cU";
		std::vector<PString> expected = {PString("4t"), PString("GF"), PString("U")};
		auto result = input.split();
		bool veri = result.size() == 3 && result[0] == expected[0] && 
											result[1] == expected[1] && 
											result[2] == expected[2];
		if(!veri){
						std::cout << input.repr() << ".split()" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << result <<std::endl;
		}
		else        std::cout << input.repr() << ".split()" SUCC  << std::endl;
	}

	{
		PString input = "4t\x0cGF\x0cU";
		std::vector<PString> expected = {PString("4t"), PString("GF\x0cU")};
		auto result = input.split("",1);
		bool veri = result.size() == 2 && result[0] == expected[0] && 
											result[1] == expected[1];
		if(!veri){
						std::cout << input.repr() << ".split(maxsplit=1)" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << result <<std::endl;
		}
		else        std::cout << input.repr() << ".split()" SUCC  << std::endl;
	}
}

void bug_splitlines(){
	{
		PString input = "\t\n\r\x0b\x0c";
		std::vector<PString> expected = {PString("\t"), PString(""),
										 PString(""), PString("")};
		auto result = input.splitlines();
		bool veri = result.size() == 4 && result[0] == expected[0] && 
											result[1] == expected[1] && 
											result[2] == expected[2] && 
											result[3] == expected[3];
		if(!veri){
						std::cout << input.repr() << ".splitlines()" FAILED << std::endl;
						std::cout << "expected: " << expected << std::endl;
						std::cout << "result:   " << input.splitlines() <<std::endl;
		}
		else        std::cout << input.repr() << ".splitlines()" SUCC  << std::endl;
	}
}

void bug_expandtabs(){
	{
		PString input = " \r\n\thello world\t\r\n ";
		PString expected = " \r\n  hello world \r\n ";
		auto result = input.expandtabs(2);
		print_result(input, expected, result, "expandtabs(2)");
	}
}

void bug_list(){
	bug_rstrip();
	bug_rsplit();
	bug_strip();
	bug_split();
	bug_splitlines();
	bug_expandtabs();
}
