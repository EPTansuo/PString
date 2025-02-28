#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pstring.h>

namespace py = pybind11;

PYBIND11_MODULE(pstring, m) {


    py::class_<PString>(m, "str")
        .def(py::init<>())
        .def(py::init<const char*>())
        .def(py::init<char>())
        .def(py::init<const std::string&>())
        .def(py::init<const PString&>())

        .def("__repr__", [](const PString& s) { return '\'' + s.str() + '\''; })
        .def("__str__", &PString::str)
        .def("__len__", &PString::size)
        .def("__bool__", &PString::operator bool)
        .def("__hash__", &PString::hash)

        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(py::self < py::self)
        .def(py::self <= py::self)
        .def(py::self > py::self)
        .def(py::self >= py::self)

        .def(py::self + py::self)
        .def(py::self += py::self)
        .def(py::self * size_t())
        .def(py::self *= size_t())

        .def("__getitem__", [](const PString& s, int index) {
            if (index < 0) index += s.size();
            if (index >= s.size() || index < 0)
                throw py::index_error();
            return s[index];
        })
        .def("__getitem__", [](const PString& s, py::slice slice) {
            size_t start, stop, step, slicelength;
            if (!slice.compute(s.size(), &start, &stop, &step, &slicelength))
                throw py::error_already_set();
            return s.slice(start, stop, step);
        })

        #define BIND_SIMPLE(func) .def(#func, &PString::func)
        BIND_SIMPLE(captilize)
        BIND_SIMPLE(casefold)
        BIND_SIMPLE(lower)
        BIND_SIMPLE(upper)
        BIND_SIMPLE(swapcase)
        BIND_SIMPLE(title)
        BIND_SIMPLE(istitle)
        BIND_SIMPLE(isalnum)
        BIND_SIMPLE(isalpha)
        BIND_SIMPLE(isascii)
        BIND_SIMPLE(isdecimal)
        BIND_SIMPLE(isdigit)
        BIND_SIMPLE(isidentifier)
        BIND_SIMPLE(islower)
        BIND_SIMPLE(isnumeric)
        BIND_SIMPLE(isprintable)
        BIND_SIMPLE(isspace)
        BIND_SIMPLE(isupper)
        #undef BIND_SIMPLE

        .def("count", &PString::count,
            py::arg("sub"), py::arg("start")=0, py::arg("end")=std::string::npos)
        
        .def("find", &PString::find,
            py::arg("sub"), py::arg("start")=0, py::arg("end")=std::string::npos)
        
        .def("index", &PString::index,
            py::arg("sub"), py::arg("start")=0, py::arg("end")=std::string::npos)

        .def("encode", [](const PString& s, const std::string& encoding, const std::string& errors) {
            auto bytes = s.encode(encoding, errors);
            return py::bytes(reinterpret_cast<const char*>(bytes.data()), bytes.size());
        }, py::arg("encoding")="utf-8", py::arg("errors")="strict")

        .def("split", [](const PString& s, const PString& sep, int maxsplit) {
            return s.split(sep, maxsplit);
        }, py::arg("sep")="", py::arg("maxsplit")=-1)

        .def("join", [](const PString& s, const py::iterable& iter) {
            std::vector<PString> items;
            for (auto handle : iter) {
                items.push_back(handle.cast<PString>());
            }
            return s.join(items);
        })

        .def_static("maketrans", [](const py::args& args) {
            if (args.size() == 1) {
								auto trans_table = args[0].cast<std::unordered_map<char,char>>();
				        return PString::maketrans(trans_table);
            } else if (args.size() == 2) {
                return PString::maketrans(
                    args[0].cast<PString>(),
                    args[1].cast<PString>()
                );
            } else if (args.size() == 3) {
                return PString::maketrans(
                    args[0].cast<PString>(),
                    args[1].cast<PString>(),
                    args[2].cast<PString>()
                );
            }
            throw py::value_error("Invalid number of arguments");
        })

        .def(py::self + py::self)
        .def(py::self += py::self)
        .def("__mul__", [](const PString& s, size_t n) { return s * n; })
        .def("__rmul__", [](const PString& s, size_t n) { return s * n; });

    m.def("__add__", [](const char* lhs, const PString& rhs) { return PString(lhs) + rhs; });
    m.def("__add__", [](const std::string& lhs, const PString& rhs) { return PString(lhs) + rhs; });

		py::implicitly_convertible<py::str, PString>();
    py::implicitly_convertible<std::string, PString>();

}
