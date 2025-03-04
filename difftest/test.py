import sys
import unicodedata
sys.path.extend(["../lib", "./lib"])

from pstring import pstr

def difftest(ref, impl, method_name, verbose=True):
    try:
        if ref != impl:
            print(f"\033[31mFAIL\033[0m: {method_name}()")
            if verbose:
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

    for test_str, case_name in test_cases:
        print(f"\n\033[34m=== Test: {case_name} ===\033[0m")
        py_str = test_str
        ps_str = pstr(test_str)

        difftest(py_str.upper(), ps_str.upper(), "upper")
        difftest(py_str.lower(), ps_str.lower(), "lower")
        difftest(py_str.title(), ps_str.title(), "title")
        difftest(py_str.capitalize(), ps_str.capitalize(), "capitalize")
        difftest(py_str.swapcase(), ps_str.swapcase(), "swapcase")
        difftest(py_str.casefold(), ps_str.casefold(), "casefold")  # Unicode casefolding
        
        difftest(py_str.strip(), ps_str.strip(), "strip")
        difftest(py_str.lstrip(), ps_str.lstrip(), "lstrip")
        difftest(py_str.rstrip(), ps_str.rstrip(), "rstrip")
        difftest(py_str.removeprefix(" \r\n\t"), ps_str.removeprefix(" \r\n\t"), "removeprefix")
        difftest(py_str.removesuffix("\t\r\n "), ps_str.removesuffix("\t\r\n "), "removesuffix")


        difftest(py_str.split(), ps_str.split(), "split")
        difftest(py_str.split(maxsplit=2), ps_str.split(maxsplit=2), "split(maxsplit=2)")
        difftest(py_str.rsplit(maxsplit=1), ps_str.rsplit(maxsplit=1), "rsplit(maxsplit=1)")
        difftest(py_str.splitlines(), ps_str.splitlines(), "splitlines")
        difftest(py_str.splitlines(False), ps_str.splitlines(False), "splitlines")
        difftest(py_str.splitlines(True), ps_str.splitlines(True), "splitlines")
        
        difftest(py_str.center(20, '*'), ps_str.center(20, '*'), "center")
        difftest(py_str.ljust(15), ps_str.ljust(15), "ljust")
        difftest(py_str.rjust(15, '#'), ps_str.rjust(15, '#'), "rjust")
        difftest(py_str.zfill(10), ps_str.zfill(10), "zfill")
        
        difftest(py_str.find('e'), ps_str.find('e'), "find")
        difftest(py_str.rfind('l'), ps_str.rfind('l'), "rfind")
        # difftest(py_str.index('o'), ps_str.index('o'), "index")
        difftest(py_str.count('l'), ps_str.count('l'), "count")
        difftest(py_str.replace('l', 'L', 2), ps_str.replace('l', 'L', 2), "replace")
        
        # difftest(py_str.startswith(('He', 'ha')), ps_str.startswith(('He', 'ha')), "startswith")
        difftest(py_str.startswith('ha'), ps_str.startswith('ha'), "startswith")
        difftest(py_str.startswith('He'), ps_str.startswith('He'), "startswith")
        # difftest(py_str.endswith(('ld', 'LD')), ps_str.endswith(('ld', 'LD')), "endswith")
        difftest(py_str.endswith('LD'), ps_str.endswith('LD'), "endswith")
        difftest(py_str.endswith('ld'), ps_str.endswith('ld'), "endswith")

        difftest(py_str.expandtabs(2), ps_str.expandtabs(2), "expandtabs")
        
        if hasattr(ps_str, 'format'):
            fmt_str = pstr("{} + {} = {}")
            difftest("1 + 2 = 3", fmt_str.format(1, 2, 3), "format")
        
        try:
            encoded_ref = py_str.encode('utf-8')
            encoded_impl = ps_str.encode('utf-8')
            difftest(encoded_ref, bytes(encoded_impl), "encode")
        except AttributeError:
            pass  
        
        difftest(py_str * 3, ps_str * 3, "*")
        difftest(py_str + py_str, ps_str + ps_str, "+")
        difftest(py_str[1:-1], ps_str[1:-1], "silice")
        
        # nfc_str = unicodedata.normalize('NFC', py_str)
        # nfd_str = unicodedata.normalize('NFD', py_str)
        # difftest(nfc_str, pstr(nfd_str).normalize('NFC'), "normalize")

if __name__ == "__main__":
    run_tests()
    print("\n\033[32mTest Finish\033[0m")
