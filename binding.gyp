{
    'targets': [
        {
            'target_name': 'binding',
            'sources': ['binding.cc'],
            'include_dirs': [
                "/usr/local/opt/python/Frameworks/Python.framework/Versions/Current/include/python3.9", # for Mac
                "/usr/include/python3.8", "<!(node -p \"require('node-addon-api').include_dir\")"],
            'cflags!': ['-fno-exceptions'],
            'cflags_cc!': ['-fno-exceptions'],
            "cflags": ["-fPIC", "-DBOOST_ALL_NO_LIB", "-static"],
            "cflags_cc": ["-fPIC", "-DBOOST_ALL_NO_LIB", "-static"],
            'xcode_settings': {
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                'CLANG_CXX_LIBRARY': 'libc++',
                'MACOSX_DEPLOYMENT_TARGET': '10.15',
            },
            'msvs_settings': {
                'VCCLCompilerTool': {'ExceptionHandling': 1},
            },
            "libraries": ["/tmp/cpython/libpython3.9.a", "/tmp/boost_1_61_0/stage/lib/libboost_filesystem.a", "/tmp/boost_1_61_0/stage/lib/libboost_system.a"]
        }
    ],
    'conditions': [
        ['OS=="mac"', {
            'cflags+': ['-fvisibility=hidden'],
            'xcode_settings': {
                'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',  # -fvisibility=hidden
            }
        }]
    ],
    'dependencies': [
        "<!(node -p \"require('node-addon-api').gyp\")",
    ]
}
