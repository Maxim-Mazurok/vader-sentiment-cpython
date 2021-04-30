{
    'targets': [
        {
            'target_name': 'binding',
            'sources': ['binding.cc'],
            'include_dirs': ["/usr/include/python3.8", "<!(node -p \"require('node-addon-api').include_dir\")"],
            'cflags!': ['-fno-exceptions'],
            'cflags_cc!': ['-fno-exceptions'],
            "cflags": ["-fPIC", "-DBOOST_ALL_NO_LIB", "-static"],
            "cflags_cc": ["-fPIC", "-DBOOST_ALL_NO_LIB", "-static"],
            'xcode_settings': {
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                'CLANG_CXX_LIBRARY': 'libc++',
                'MACOSX_DEPLOYMENT_TARGET': '10.7',
            },
            'msvs_settings': {
                'VCCLCompilerTool': {'ExceptionHandling': 1},
            },
            "libraries": ["/tmp/cpython-3.8.5/libpython3.8.a", "/tmp/boost_1_76_0/stage/lib/libboost_filesystem.a", "/tmp/boost_1_76_0/stage/lib/libboost_system.a"]
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
