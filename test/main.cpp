#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <format>
#include <cassert>
#include "pstring.h"


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
    auto str_splited = str.split(",");
    std::cout << str_splited[0].upper() << std::endl;
    
    // Python-style join
    auto str_joined = PString(":").join(str_splited);
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
    cout << str_split_debug.toString() + ".split() = " << list_split << endl;
    PString str_split_debug2 = "sd d f\n\r\t   f";
    std::vector<PString> list_split2 = str_split_debug2.split();
    cout << str_split_debug2.toString() + ".split() = " << list_split2 << endl;
    

    PString str3 = "abc:1222::3333:::";
    auto list = str3.split(":");
    cout << str3.toString() + ".split(\":\") = " << list << endl;
    cout << str3.toString() + ".split() = " << str3.split() << endl;
    cout << str3.toString() + ".split(\":\",2) = " << str3.split(":",2) << endl;
    cout << str3.toString() + ".rsplit(\":\") = " << str3.rsplit(":") << endl;
    cout << str3.toString() + ".rsplit() = " << str3.rsplit() << endl;
    cout << str3.toString() + ".rsplit(\":\",2) = " << str3.rsplit(":",2) << endl;

    PString str_strip_before = "  \t\n\r  abc  \t\n\r  ";
    cout << str_strip_before.toString() + ".lstrip() = " << str_strip_before.lstrip().toString() << endl;
    cout << str_strip_before.toString() + ".rstrip() = " << str_strip_before.rstrip().toString() << endl;
    cout << str_strip_before.toString() + ".strip()  = " << str_strip_before.strip().toString() << endl;

    PString str_strip_2 = "abcaabb12345678bcaddbcabac";
    cout << str_strip_2.toString() + ".lstrip(\"abc\") = " << str_strip_2.lstrip("abc").toString() << endl;
    cout << str_strip_2.toString() + ".rstrip(\"abc\") = " << str_strip_2.rstrip("abc").toString() << endl;
    cout << str_strip_2.toString() + ".strip(\"abc\")  = " << str_strip_2.strip("abc").toString() << endl;

    PString str_cap1 = "aBC";
    cout << str_cap1.toString() + ".captilize() = " << str_cap1.captilize().toString() << endl;
    PString str_cap2 = "你好";
    cout << str_cap2.toString() + ".captilize() = " << str_cap2.captilize().toString() << endl;
    PString str_cap3 = " aBC dfdfd";
    cout << str_cap3.toString() + ".captilize() = " << str_cap3.captilize().toString() << endl;

    PString str_center = "abc";
    cout << str_center.toString() + ".center(10) = " << str_center.center(10).toString() << endl;
    cout << str_center.toString() + ".center(10, '-') = " << str_center.center(10, '-').toString() << endl;
    cout << str_center.toString() + ".center(2, '-') = " << str_center.center(2, '-').toString() << endl;
    cout << str_center.toString() + ".center(4, '-') = " << str_center.center(4, '-').toString() << endl;

    PString str_count = "abcabcabc";
    cout << str_count.toString() + ".count(\"abc\") = " << str_count.count("abc") << endl;
    cout << str_count.toString() + ".count(\"abc\",0,9) = " << str_count.count("abc",0,9) << endl;
    cout << str_count.toString() + ".count(\"abc\",0,8) = " << str_count.count("abc",0,8) << endl;
    cout << str_count.toString() + ".count(\"abc\",1,9) = " << str_count.count("abc",1,9) << endl;

#if __cplusplus >= 202002L
    PString fmt = "Hello, {}!";
    cout << fmt.toString() + ".format(\"World\") = " << fmt.format("World").toString() << endl;
#endif
    

    PString str_istitle1 = "Hello World!";
    PString str_istitle2 = "1Cc";
    PString str_istitle3 = "1CC";
    PString str_istitle4 = "1cC";
    PString str_istitle5 = "Ss Abc_cc";
    PString str_istitle6 = "Ss Abc_Cc";
    cout << str_istitle1.toString() + ".istitle() = " << str_istitle1.istitle() << endl;
    cout << str_istitle2.toString() + ".istitle() = " << str_istitle2.istitle() << endl;
    cout << str_istitle3.toString() + ".istitle() = " << str_istitle3.istitle() << endl;
    cout << str_istitle4.toString() + ".istitle() = " << str_istitle4.istitle() << endl;
    cout << str_istitle5.toString() + ".istitle() = " << str_istitle5.istitle() << endl;
    cout << str_istitle6.toString() + ".istitle() = " << str_istitle6.istitle() << endl;

    PString str_isupper = "_";
    PString str_isupper2 = "你好ABC";
    PString str_isupper3 = "你好";
    cout << str_isupper.toString() + ".isupper() = " << str_isupper.isupper() << endl;
    cout << str_isupper2.toString() + ".isupper() = " << str_isupper2.isupper() << endl;
    cout << str_isupper3.toString() + ".isupper() = " << str_isupper3.isupper() << endl;

    PString str_join = "a";
    std::vector<PString> join_list;
    join_list = {"a","b","c","d"};
    // PList join_list2 = PList("a", "b", "c", "d");
    PString join_str = "sdf";
     cout << str_join.toString() + ".join("<< join_str.toString() << ") = " << str_join.join(join_list).toString() << endl;
    cout << str_join.toString() + ".join(" << join_list << ") = " << str_join.join(join_str).toString() << endl;

    auto transtable = PString::maketrans("abc", "123");
    auto transtable2 = PString::maketrans("abc", "123", "def");

    cout << "PString::maketrans(\"abc\", \"123\") = " << transtable << endl;
    cout << "PString::maketrans(\"abc\", \"123\", \"def\") = " << transtable2 << endl;
    // cout << str_translate.toString() + ".translate(" << transtable.toString() << ") = " << str_translate.translate(transtable).toString() << endl;
    // cout << str_translate.toString() + ".translate(" << transtable2.toString() << ") = " << str_translate.translate(transtable2).toString() << endl;

    PString str_partition = "acbcc hello sdfdsfd";
    cout << str_partition.toString() + ".partition(\"hello\") = " << str_partition.partition("hello") << endl;
    cout << str_partition.toString() + ".partition(\"hee--\") = " << str_partition.partition("hee--") << endl;

    PString str_removeprefix = "TestHook";
    PString str_removeprefix2 = "BaseTestCase";
    cout << str_removeprefix.toString() + ".remoteprefix(\"Test\") = " << str_removeprefix.remoteprefix("Test").toString() << endl;
    cout << str_removeprefix2.toString() + ".remoteprefix(\"Test\") = " << str_removeprefix2.remoteprefix("Test").toString() << endl;

    PString str_removesuffix = "MiscTests";
    PString str_removesuffix2 = "TmpDirMixin";
    cout << str_removesuffix.toString() + ".removesuffix(\"Tests\") = " << str_removesuffix.removesuffix("Tests").toString() << endl;
    cout << str_removesuffix2.toString() + ".removesuffix(\"Tests\") = " << str_removesuffix2.removesuffix("Tests").toString() << endl;

    PString str_replace = "abcabcabc";
    cout << str_replace.toString() + ".replace(\"abc\", \"123\") = " << str_replace.replace("abc", "123").toString() << endl;
    cout << str_replace.toString() + ".replace(\"abc\", \"123\", 2) = " << str_replace.replace("abc", "123", 2).toString() << endl;
    cout << str_replace.toString() + ".replace(\"abc\", \"-\") = " << str_replace.replace("abc", "-").toString() << endl;
    cout << str_replace.toString() + ".replace(\"abc\", \"|....\") = " << str_replace.replace("abc", "|....").toString() << endl;

    PString str_find = "acbcc hello sdfdsfd";
    cout << str_find.toString() + ".find(\"hello\") = " << str_find.find("hello") << endl;
    cout << str_find.toString() + ".find(\"hello\",6,10) = " << str_find.find("hello",6,10) << endl;
    cout << str_find.toString() + ".find(\"hello\",6,11) = " << str_find.find("hello",6,11) << endl;
    cout << str_find.toString() + ".rfind(\"hello\") = " << str_find.rfind("hello") << endl;
    cout << str_find.toString() + ".rfind(\"hello\",6,10) = " << str_find.rfind("hello",6,10) << endl;
    cout << str_find.toString() + ".rfind(\"hello\",6,11) = " << str_find.rfind("hello",6,11) << endl;

    PString str_rpartition = "acbcc hello hello sdfdsfd";
    cout << str_rpartition.toString() + ".rpartition(\"hello\") = " << str_rpartition.rpartition("hello") << endl;

    PString str_splitlines = "acbcc hello\nhello\nsdfdsfd\rxxx\r\nxxx\n\rsss\x1cssds";
    cout << str_splitlines.toString() + ".splitlines() = " << str_splitlines.splitlines() << endl;
    cout << str_splitlines.toString() + ".splitlines(true) = " << str_splitlines.splitlines(true) << endl;

    PString str_swapcase = "你好AbCdEf";
    cout << str_swapcase.toString() + ".swapcase() = " << str_swapcase.swapcase().toString() << endl;
    cout << str_swapcase.toString() + ".swapcase().swapcase() = " << str_swapcase.swapcase().swapcase().toString() << endl;

    PString str_title = "they're bill's friends from the UK";
    cout << str_title.toString() + ".title() = " << str_title.title().toString() << endl;

    auto trans_table = PString::maketrans("123","abc");
    PString str_translate = "123abc---123456712123";
    cout << str_translate.toString() << ".translate(" << trans_table << ") = " << str_translate.translate(trans_table).toString() << endl;

    PString str_zfill = "42";
    cout << str_zfill.toString() + ".zfill(5) = " << str_zfill.zfill(5).toString() << endl;
    cout << str_zfill.toString() + ".zfill(2) = " << str_zfill.zfill(2).toString() << endl;
    PString str_zfill2 = "-42";
    cout << str_zfill2.toString() + ".zfill(5) = " << str_zfill2.zfill(5).toString() << endl;
    cout << str_zfill2.toString() + ".zfill(2) = " << str_zfill2.zfill(2).toString() << endl;

    PString str_expandtabs = "\n67890\t";
    PString str_expandtabs2 = "01\t012\t0123\t01234";
    cout << str_expandtabs.toString() + ".expandtabs() = " << str_expandtabs.expandtabs().toString()  << " len=" <<
    str_expandtabs.expandtabs().length() << endl;
    cout << str_expandtabs2.toString() + ".expandtabs(4) = " << str_expandtabs2.expandtabs(4).toString()  << " len=" <<
    str_expandtabs2.expandtabs(4).length() << endl;

    PString str_encode = "你好,abc";
    cout << str_encode.toString() + ".encode(\"utf-8\") = " << str_encode.encode("utf-8") <<
    "len = " << str_encode.encode("utf-8").size() << std::endl;
    cout << str_encode.toString() + ".encode(\"utf-16\") = " << str_encode.encode("utf-16") <<
    "len = " << str_encode.encode("utf-16").size() << std::endl;
    cout << str_encode.toString() + ".encode(\"utf-32\") = " << str_encode.encode("utf-32") <<
    "len = " << str_encode.encode("utf-32").size() << std::endl;

    PString str_equal = "你好,abc";
    PString str_equal_other = "你好,abc";
    const char* str_equal_other2 = "你好,abc";
    std::string str_equal_other3 = "你好,abc";
    PString str_equal_ = "您好,abc";
    cout << str_equal.toString() + " == " << str_equal_other.toString() << " = " << (str_equal == str_equal_other) << std::endl;
    cout << str_equal.toString() + " == " << str_equal_other2 << " = " << (str_equal == str_equal_other2) << std::endl;
    cout << str_equal.toString() + " == " << str_equal_other3 << " = " << (str_equal == str_equal_other3) << std::endl;
    cout << str_equal_.toString() + " == " << str_equal_other.toString() << " = " << (str_equal_ == str_equal_other) << std::endl;
    cout << str_equal_.toString() + " == " << str_equal_other2 << " = " << (str_equal_ == str_equal_other2) << std::endl;
    cout << str_equal_.toString() + " == " << str_equal_other3 << " = " << (str_equal_ == str_equal_other3) << std::endl;
    
#if __cplusplus >= 202002L
    cout << std::format("str_equal: {}",str_equal) << std::endl;
#endif
    const_iter(PString("123abc"));

    PString str_at = "abc";
    str_at[0] = '1';
    cout << str_at.toString() << "[0] = " << str_at[0] << endl;
    cout << str_at.toString() << "[1] = " << str_at[1] << endl;
    cout << str_at.toString() << "[2] = " << str_at[2] << endl;

    PString str_slice = "123456789";
    cout << str_slice.toString() + "[1:5] = " << str_slice.slice(1,5).toString() << endl;
    cout << str_slice.toString() + "[1:5] = " << str_slice(1,5).toString() << endl;
    cout << str_slice.toString() + "[1:5:2] = " << str_slice.slice(1,5,2).toString() << endl;
    cout << str_slice.toString() + "[1:5:2] = " << str_slice(1,5,2).toString() << endl;
    cout << str_slice.toString() + "[:5] = " << str_slice.slice(0,5).toString() << endl;
    cout << str_slice.toString() + "[:5] = " << str_slice(0,5).toString() << endl;
    cout << str_slice.toString() + "[1:] = " << str_slice.slice(1).toString() << endl;
    cout << str_slice.toString() + "[1:] = " << str_slice(1).toString() << endl;
    cout << str_slice.toString() + "[:] = " << str_slice.slice().toString() << endl;
    cout << str_slice.toString() + "[:] = " << str_slice().toString() << endl;
    cout << str_slice.toString() + "[-1:] = " << str_slice.slice(-1).toString() << endl;
    cout << str_slice.toString() + "[-1:] = " << str_slice(-1).toString() << endl;
    cout << str_slice.toString() + "[-1:-5] = " << str_slice.slice(-1,-5).toString() << endl;
    cout << str_slice.toString() + "[-1:-5] = " << str_slice(-1,-5).toString() << endl;
    cout << str_slice.toString() + "[-1:-5:-1] = " << str_slice.slice(-1,-5,-1).toString() << endl;
    cout << str_slice.toString() + "[-1:-5:-1] = " << str_slice(-1,-5,-1).toString() << endl;

    return 0;
}
