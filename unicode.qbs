import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        name: "manualtest"
        consoleApplication: true
        cpp.cxxLanguageVersion: "c++14"
        files: [
            "unicode_view",
            "main.cpp",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }

    CppApplication {
        name: "benchmark"
        consoleApplication: true
        cpp.cxxLanguageVersion: "c++14"
        files: [
            "benchmark_util.h",
            "unicode_view",
            "benchmark.cpp"
        ]
    }
}
