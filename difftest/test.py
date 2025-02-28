import sys

import sys
sys.path.append("../lib")  # 添加模块所在目录
sys.path.append("./lib")  # 添加模块所在目录

from pstring import str as pstr

s = pstr("hello world")

print(s.upper())       # 输出HELLO WORLD
print(s.split(' '))    # 输出['hello', 'world']
print(s[1:5])          # 切片输出'ello'


