{
    'targets': [
        {
            'target_name': 'binding',
            'sources': ['binding.cc'],
            'include_dirs': ["/usr/include/python3.8"],
            "cflags!": [ "-fno-exceptions" ],
            "cflags": [ "-fPIC", "-DBOOST_ALL_NO_LIB" ],
            "cflags_cc": [ "-fPIC", "-DBOOST_ALL_NO_LIB" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "libraries": ["/usr/lib/x86_64-linux-gnu/libpython3.8.so", "/usr/lib/x86_64-linux-gnu/libboost_filesystem.so", "/usr/lib/x86_64-linux-gnu/libboost_system.so"]
        }
    ]
}
