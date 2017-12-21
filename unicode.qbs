import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true
        cpp.cxxLanguageVersion: "c++14"
        files: [
            "main.cpp",
            "unicode_view",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
