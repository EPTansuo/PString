import sys

import sys
sys.path.append("../lib")
sys.path.append("./lib")

from pstring import str as pstr

s = pstr("hello world")

print(s.upper())
print(s.split(' '))
print(s[1:5])


