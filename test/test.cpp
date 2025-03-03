#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <format>
#include <cassert>
#include "pstring.h"

void bug_list();

using namespace std;

template <typename T>
void const_iter(const T &collect){
    cout << "const_iter:" << endl;
    for(auto const &item: collect){
        cout << item << endl;
    }
}

void demo() {
    PString str = "  Hello, World!  ";

    // Python-style split
    auto str_split = str.split(",");
    std::cout << str_split[0].upper() << std::endl;
    
    // Python-style join
    auto str_joined = PString(":").join(str_split);
    std::cout << str_joined << std::endl;

    // Python-style slice
    auto str_sliced = str.slice(6, 1, -1);
    std::cout << str_sliced << std::endl;

    // Python-style strip
    auto str_stripped = str.strip();
    std::cout << str_stripped << std::endl;

    // ...
}


int main(){


    demo();


    PString str = "Hello, World!";
    cout << str << endl;

    PString str2("123");
    cout << std::stoi(str2) << endl;

    PString str_opt; 
    str_opt = str + str2 + "abc";
    str_opt = "abc" + str_opt;
    str_opt = string("std_String") + str_opt;
    str_opt += "abc";
    str_opt += str2;
    str_opt += string("std_String");
    cout << str_opt << endl;

    for(auto c : str){
        cout << (c) << endl;
    }
    PString str_split_debug = "async_inst  \\";
    std::vector<PString> list_split = str_split_debug.split();
    cout << str_split_debug.repr() + ".split() = " << list_split << endl;
    PString str_split_debug2 = "sd d f\n\r\t   f";
    std::vector<PString> list_split2 = str_split_debug2.split();
    cout << str_split_debug2.repr() + ".split() = " << list_split2 << endl;
    

    PString str3 = "abc:1222::3333:::";
    auto list = str3.split(":");
    cout << str3.repr() + ".split(\":\") = " << list << endl;
    cout << str3.repr() + ".split() = " << str3.split() << endl;
    cout << str3.repr() + ".split(\":\",2) = " << str3.split(":",2) << endl;
    cout << str3.repr() + ".rsplit(\":\") = " << str3.rsplit(":") << endl;
    // cout << str3.repr() + ".rsplit() = " << str3.rsplit() << endl;
    cout << str3.repr() + ".rsplit(\":\",2) = " << str3.rsplit(":",2) << endl;

    PString str_strip_before = "  \t\n\r  abc  \t\n\r  ";
    cout << str_strip_before.repr() + ".lstrip() = " << str_strip_before.lstrip().repr() << endl;
    cout << str_strip_before.repr() + ".rstrip() = " << str_strip_before.rstrip().repr() << endl;
    cout << str_strip_before.repr() + ".strip()  = " << str_strip_before.strip().repr() << endl;

    PString str_strip_2 = "abcaabb12345678bcaddbcabac";
    cout << str_strip_2.repr() + ".lstrip(\"abc\") = " << str_strip_2.lstrip("abc").repr() << endl;
    cout << str_strip_2.repr() + ".rstrip(\"abc\") = " << str_strip_2.rstrip("abc").repr() << endl;
    cout << str_strip_2.repr() + ".strip(\"abc\")  = " << str_strip_2.strip("abc").repr() << endl;

    PString str_cap1 = "aBC";
    cout << str_cap1.repr() + ".capitalize() = " << str_cap1.capitalize().repr() << endl;
    PString str_cap2 = "你好";
    cout << str_cap2.repr() + ".capitalize() = " << str_cap2.capitalize().repr() << endl;
    PString str_cap3 = " aBC dfdfd";
    cout << str_cap3.repr() + ".capitalize() = " << str_cap3.capitalize().repr() << endl;

    PString str_center = "abc";
    cout << str_center.repr() + ".center(10) = " << str_center.center(10).repr() << endl;
    cout << str_center.repr() + ".center(10, '-') = " << str_center.center(10, '-').repr() << endl;
    cout << str_center.repr() + ".center(2, '-') = " << str_center.center(2, '-').repr() << endl;
    cout << str_center.repr() + ".center(4, '-') = " << str_center.center(4, '-').repr() << endl;

    PString str_count = "abcabcabc";
    cout << str_count.repr() + ".count(\"abc\") = " << str_count.count("abc") << endl;
    cout << str_count.repr() + ".count(\"abc\",0,9) = " << str_count.count("abc",0,9) << endl;
    cout << str_count.repr() + ".count(\"abc\",0,8) = " << str_count.count("abc",0,8) << endl;
    cout << str_count.repr() + ".count(\"abc\",1,9) = " << str_count.count("abc",1,9) << endl;

#if __cplusplus >= 202002L
    PString fmt = "Hello, {}!";
    cout << fmt.repr() + ".format(\"World\") = " << fmt.format("World").repr() << endl;
#endif
    

    PString str_istitle1 = "Hello World!";
    PString str_istitle2 = "1Cc";
    PString str_istitle3 = "1CC";
    PString str_istitle4 = "1cC";
    PString str_istitle5 = "Ss Abc_cc";
    PString str_istitle6 = "Ss Abc_Cc";
    cout << str_istitle1.repr() + ".istitle() = " << str_istitle1.istitle() << endl;
    cout << str_istitle2.repr() + ".istitle() = " << str_istitle2.istitle() << endl;
    cout << str_istitle3.repr() + ".istitle() = " << str_istitle3.istitle() << endl;
    cout << str_istitle4.repr() + ".istitle() = " << str_istitle4.istitle() << endl;
    cout << str_istitle5.repr() + ".istitle() = " << str_istitle5.istitle() << endl;
    cout << str_istitle6.repr() + ".istitle() = " << str_istitle6.istitle() << endl;

    PString str_isupper = "_";
    PString str_isupper2 = "你好ABC";
    PString str_isupper3 = "你好";
    cout << str_isupper.repr() + ".isupper() = " << str_isupper.isupper() << endl;
    cout << str_isupper2.repr() + ".isupper() = " << str_isupper2.isupper() << endl;
    cout << str_isupper3.repr() + ".isupper() = " << str_isupper3.isupper() << endl;

    PString str_join = "a";
    std::vector<PString> join_list;
    join_list = {"a","b","c","d"};
    // PList join_list2 = PList("a", "b", "c", "d");
    PString join_str = "sdf";
     cout << str_join.repr() + ".join("<< join_str.repr() << ") = " << str_join.join(join_list).repr() << endl;
    cout << str_join.repr() + ".join(" << join_list << ") = " << str_join.join(join_str).repr() << endl;

    auto transtable = PString::maketrans("abc", "123");
    auto transtable2 = PString::maketrans("abc", "123", "def");

    cout << "PString::maketrans(\"abc\", \"123\") = " << transtable << endl;
    cout << "PString::maketrans(\"abc\", \"123\", \"def\") = " << transtable2 << endl;
    // cout << str_translate.repr() + ".translate(" << transtable.repr() << ") = " << str_translate.translate(transtable).repr() << endl;
    // cout << str_translate.repr() + ".translate(" << transtable2.repr() << ") = " << str_translate.translate(transtable2).repr() << endl;

    PString str_partition = "acbcc hello sdfdsfd";
    cout << str_partition.repr() + ".partition(\"hello\") = " << str_partition.partition("hello") << endl;
    cout << str_partition.repr() + ".partition(\"hee--\") = " << str_partition.partition("hee--") << endl;

    PString str_removeprefix = "TestHook";
    PString str_removeprefix2 = "BaseTestCase";
    cout << str_removeprefix.repr() + ".removeprefix(\"Test\") = " << str_removeprefix.removeprefix("Test").repr() << endl;
    cout << str_removeprefix2.repr() + ".removeprefix(\"Test\") = " << str_removeprefix2.removeprefix("Test").repr() << endl;

    PString str_removesuffix = "MiscTests";
    PString str_removesuffix2 = "TmpDirMixin";
    cout << str_removesuffix.repr() + ".removesuffix(\"Tests\") = " << str_removesuffix.removesuffix("Tests").repr() << endl;
    cout << str_removesuffix2.repr() + ".removesuffix(\"Tests\") = " << str_removesuffix2.removesuffix("Tests").repr() << endl;

    PString str_replace = "abcabcabc";
    cout << str_replace.repr() + ".replace(\"abc\", \"123\") = " << str_replace.replace("abc", "123").repr() << endl;
    cout << str_replace.repr() + ".replace(\"abc\", \"123\", 2) = " << str_replace.replace("abc", "123", 2).repr() << endl;
    cout << str_replace.repr() + ".replace(\"abc\", \"-\") = " << str_replace.replace("abc", "-").repr() << endl;
    cout << str_replace.repr() + ".replace(\"abc\", \"|....\") = " << str_replace.replace("abc", "|....").repr() << endl;

    PString str_find = "acbcc hello sdfdsfd";
    cout << str_find.repr() + ".find(\"hello\") = " << str_find.find("hello") << endl;
    cout << str_find.repr() + ".find(\"hello\",6,10) = " << str_find.find("hello",6,10) << endl;
    cout << str_find.repr() + ".find(\"hello\",6,11) = " << str_find.find("hello",6,11) << endl;
    cout << str_find.repr() + ".rfind(\"hello\") = " << str_find.rfind("hello") << endl;
    cout << str_find.repr() + ".rfind(\"hello\",6,10) = " << str_find.rfind("hello",6,10) << endl;
    cout << str_find.repr() + ".rfind(\"hello\",6,11) = " << str_find.rfind("hello",6,11) << endl;

    PString str_rpartition = "acbcc hello hello sdfdsfd";
    cout << str_rpartition.repr() + ".rpartition(\"hello\") = " << str_rpartition.rpartition("hello") << endl;

    PString str_splitlines = "acbcc hello\nhello\nsdfdsfd\rxxx\r\nxxx\n\rsss\x1cssds";
    cout << str_splitlines.repr() + ".splitlines() = " << str_splitlines.splitlines() << endl;
    cout << str_splitlines.repr() + ".splitlines(true) = " << str_splitlines.splitlines(true) << endl;

    PString str_swapcase = "你好AbCdEf";
    cout << str_swapcase.repr() + ".swapcase() = " << str_swapcase.swapcase().repr() << endl;
    cout << str_swapcase.repr() + ".swapcase().swapcase() = " << str_swapcase.swapcase().swapcase().repr() << endl;

    PString str_title = "they're bill's friends from the UK";
    cout << str_title.repr() + ".title() = " << str_title.title().repr() << endl;

    auto trans_table = PString::maketrans("123","abc");
    PString str_translate = "123abc---123456712123";
    cout << str_translate.repr() << ".translate(" << trans_table << ") = " << str_translate.translate(trans_table).repr() << endl;

    PString str_zfill = "42";
    cout << str_zfill.repr() + ".zfill(5) = " << str_zfill.zfill(5).repr() << endl;
    cout << str_zfill.repr() + ".zfill(2) = " << str_zfill.zfill(2).repr() << endl;
    PString str_zfill2 = "-42";
    cout << str_zfill2.repr() + ".zfill(5) = " << str_zfill2.zfill(5).repr() << endl;
    cout << str_zfill2.repr() + ".zfill(2) = " << str_zfill2.zfill(2).repr() << endl;

    PString str_expandtabs = "\n67890\t";
    PString str_expandtabs2 = "01\t012\t0123\t01234";
    cout << str_expandtabs.repr() + ".expandtabs() = " << str_expandtabs.expandtabs().repr()  << " len=" <<
    str_expandtabs.expandtabs().length() << endl;
    cout << str_expandtabs2.repr() + ".expandtabs(4) = " << str_expandtabs2.expandtabs(4).repr()  << " len=" <<
    str_expandtabs2.expandtabs(4).length() << endl;

    PString str_encode = "你好,abc";
    cout << str_encode.repr() + ".encode(\"utf-8\") = " << str_encode.encode("utf-8") <<
    "len = " << str_encode.encode("utf-8").size() << std::endl;
    cout << str_encode.repr() + ".encode(\"utf-16\") = " << str_encode.encode("utf-16") <<
    "len = " << str_encode.encode("utf-16").size() << std::endl;
    cout << str_encode.repr() + ".encode(\"utf-32\") = " << str_encode.encode("utf-32") <<
    "len = " << str_encode.encode("utf-32").size() << std::endl;

    PString str_equal = "你好,abc";
    PString str_equal_other = "你好,abc";
    const char* str_equal_other2 = "你好,abc";
    std::string str_equal_other3 = "你好,abc";
    PString str_equal_ = "您好,abc";
    cout << str_equal.repr() + " == " << str_equal_other.repr() << " = " << (str_equal == str_equal_other) << std::endl;
    cout << str_equal.repr() + " == " << str_equal_other2 << " = " << (str_equal == str_equal_other2) << std::endl;
    cout << str_equal.repr() + " == " << str_equal_other3 << " = " << (str_equal == str_equal_other3) << std::endl;
    cout << str_equal_.repr() + " == " << str_equal_other.repr() << " = " << (str_equal_ == str_equal_other) << std::endl;
    cout << str_equal_.repr() + " == " << str_equal_other2 << " = " << (str_equal_ == str_equal_other2) << std::endl;
    cout << str_equal_.repr() + " == " << str_equal_other3 << " = " << (str_equal_ == str_equal_other3) << std::endl;
    
#if __cplusplus >= 202002L
    cout << std::format("str_equal: {}",str_equal) << std::endl;
#endif
    const_iter(PString("123abc"));

    PString str_at = "abc";
    str_at[0] = '1';
    cout << str_at.repr() << "[0] = " << str_at[0] << endl;
    cout << str_at.repr() << "[1] = " << str_at[1] << endl;
    cout << str_at.repr() << "[2] = " << str_at[2] << endl;

    PString str_slice = "123456789";
    cout << str_slice.repr() + "[1:5] = " << str_slice.slice(1,5).repr() << endl;
    cout << str_slice.repr() + "[1:5] = " << str_slice(1,5).repr() << endl;
    cout << str_slice.repr() + "[1:5:2] = " << str_slice.slice(1,5,2).repr() << endl;
    cout << str_slice.repr() + "[1:5:2] = " << str_slice(1,5,2).repr() << endl;
    cout << str_slice.repr() + "[:5] = " << str_slice.slice(0,5).repr() << endl;
    cout << str_slice.repr() + "[:5] = " << str_slice(0,5).repr() << endl;
    cout << str_slice.repr() + "[1:] = " << str_slice.slice(1).repr() << endl;
    cout << str_slice.repr() + "[1:] = " << str_slice(1).repr() << endl;
    cout << str_slice.repr() + "[:] = " << str_slice.slice().repr() << endl;
    cout << str_slice.repr() + "[:] = " << str_slice().repr() << endl;
    cout << str_slice.repr() + "[-1:] = " << str_slice.slice(-1).repr() << endl;
    cout << str_slice.repr() + "[-1:] = " << str_slice(-1).repr() << endl;
    cout << str_slice.repr() + "[-1:-5] = " << str_slice.slice(-1,-5).repr() << endl;
    cout << str_slice.repr() + "[-1:-5] = " << str_slice(-1,-5).repr() << endl;
    cout << str_slice.repr() + "[-1:-5:-1] = " << str_slice.slice(-1,-5,-1).repr() << endl;
    cout << str_slice.repr() + "[-1:-5:-1] = " << str_slice(-1,-5,-1).repr() << endl;


	PString str_sstream_in;  
    std::stringstream ss("Hello,World!");
    ss >> str_sstream_in;
    cout << "str_sstream_in = " << str_sstream_in << endl;
	
		bug_list();

    return 0;
}
