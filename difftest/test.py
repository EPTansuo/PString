import sys
import unicodedata
import random
import string
sys.path.extend(["../lib", "./lib"])

from pstring import pstr

def random_str():
    return  ''.join(random.sample(10*(string.ascii_letters + string.digits + " \v\f\n\t "), random.randint(0,100)))


def difftest(test_str, ref, impl, method_name, verbose=True):
    try:
        if ref != impl:
            print(f"\033[31mFAIL\033[0m: {method_name}()")
            if verbose:
                print(f"  Test Case: {repr(test_str)}")
                print(f"  Reference: {repr(ref)}")
                print(f"  Implementation: {repr(impl)}")
            return False
        return True
    except Exception as e:
        print(f"\033[31mERROR\033[0m: {method_name}() raised {type(e).__name__}: {str(e)}")
        return False

def run_tests():
    test_cases = [
        (" \r\n\thello world\t\r\n ", "Basic"),
        ("hello,,,worLD", "Basic2"),
        ("", "Empty String"),
        ("12345", "Number"),
        ("a,b;c.d|e", "Separator"),
        ("\t\n\r\x0b\x0c", "Blank Character"),
        ("'\"\\", "Escape characters"),
    ]

    for i in range(100):
        test_cases.append(tuple([random_str(), f"random_test{i}"]))

    for test_str, case_name in test_cases:
        print(f"\n\033[34m=== Test: {case_name} ===\033[0m")
        py_str = test_str
        ps_str = pstr(test_str)

        difftest(test_str, py_str.upper(), ps_str.upper(), "upper")
        difftest(test_str, py_str.lower(), ps_str.lower(), "lower")
        difftest(test_str, py_str.title(), ps_str.title(), "title")
        difftest(test_str, py_str.capitalize(), ps_str.capitalize(), "capitalize")
        difftest(test_str, py_str.swapcase(), ps_str.swapcase(), "swapcase")
        difftest(test_str, py_str.casefold(), ps_str.casefold(), "casefold")  # Unicode casefolding
        
        difftest(test_str, py_str.strip(), ps_str.strip(), "strip")
        difftest(test_str, py_str.lstrip(), ps_str.lstrip(), "lstrip")
        difftest(test_str, py_str.rstrip(), ps_str.rstrip(), "rstrip")
        difftest(test_str, py_str.removeprefix(" \r\n\t"), ps_str.removeprefix(" \r\n\t"), "removeprefix")
        difftest(test_str, py_str.removesuffix("\t\r\n "), ps_str.removesuffix("\t\r\n "), "removesuffix")


        difftest(test_str, py_str.split(), ps_str.split(), "split")
        difftest(test_str, py_str.split(maxsplit=2), ps_str.split(maxsplit=2), "split(maxsplit=2)")
        difftest(test_str, py_str.rsplit(maxsplit=1), ps_str.rsplit(maxsplit=1), "rsplit(maxsplit=1)")
        difftest(test_str, py_str.splitlines(), ps_str.splitlines(), "splitlines")
        difftest(test_str, py_str.splitlines(False), ps_str.splitlines(False), "splitlines")
        difftest(test_str, py_str.splitlines(True), ps_str.splitlines(True), "splitlines")
        
        difftest(test_str, py_str.center(20, '*'), ps_str.center(20, '*'), "center")
        difftest(test_str, py_str.ljust(15), ps_str.ljust(15), "ljust")
        difftest(test_str, py_str.rjust(15, '#'), ps_str.rjust(15, '#'), "rjust")
        difftest(test_str, py_str.zfill(10), ps_str.zfill(10), "zfill")
        
        difftest(test_str, py_str.find('e'), ps_str.find('e'), "find")
        difftest(test_str, py_str.rfind('l'), ps_str.rfind('l'), "rfind")

        try:
            pstr_index = ps_str.index('e')
            py_index = py_str.index('e')
            difftest(test_str, py_index, pstr_index, "index")
        except ValueError:
            pass

        difftest(test_str, py_str.count('l'), ps_str.count('l'), "count")
        difftest(test_str, py_str.replace('l', 'L', 2), ps_str.replace('l', 'L', 2), "replace")
        
        difftest(test_str, py_str.startswith(('He', 'ha')), ps_str.startswith(('He', 'ha')), "startswith")
        difftest(test_str, py_str.startswith('ha'), ps_str.startswith('ha'), "startswith")
        difftest(test_str, py_str.startswith('He'), ps_str.startswith('He'), "startswith")
        difftest(test_str, py_str.endswith(('ld', 'LD')), ps_str.endswith(('ld', 'LD')), "endswith")
        difftest(test_str, py_str.endswith('LD'), ps_str.endswith('LD'), "endswith")
        difftest(test_str, py_str.endswith('ld'), ps_str.endswith('ld'), "endswith")
        difftest(test_str, py_str.endswith(' '), ps_str.endswith(' '), "endswith")

        difftest(test_str, py_str.expandtabs(2), ps_str.expandtabs(2), "expandtabs")
        difftest(test_str, py_str.expandtabs(), ps_str.expandtabs(), "expandtabs")
        difftest(test_str, py_str.expandtabs(0), ps_str.expandtabs(0), "expandtabs")
        
        if hasattr(ps_str, 'format'):
            fmt_str = pstr("{} + {} = {}")
            difftest(test_str, "1 + 2 = 3", fmt_str.format(1, 2, 3), "format")
        
        try:
            encoded_ref = py_str.encode('utf-8')
            encoded_impl = ps_str.encode('utf-8')
            difftest(test_str, encoded_ref, bytes(encoded_impl), "encode")
        except AttributeError:
            pass  
        
        difftest(test_str, py_str * 3, ps_str * 3, "*")
        difftest(test_str, py_str + py_str, ps_str + ps_str, "+")
        difftest(test_str, py_str[1:-1], ps_str[1:-1], "silice")
        
        # nfc_str = unicodedata.normalize('NFC', py_str)
        # nfd_str = unicodedata.normalize('NFD', py_str)
        # difftest(nfc_str, pstr(nfd_str).normalize('NFC'), "normalize")

if __name__ == "__main__":
    run_tests()
    print("\n\033[32mTest Finish\033[0m")
