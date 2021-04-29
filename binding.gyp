{
    'targets': [
        {
            'target_name': 'binding',
            'sources': ['binding.cc'],
            'include_dirs': ["/usr/include/python3.8", "<!(node -p \"require('node-addon-api').include_dir\")"],
            'cflags!': ['-fno-exceptions'],
            'cflags_cc!': ['-fno-exceptions'],
            "cflags": ["-fPIC", "-DBOOST_ALL_NO_LIB"],
            "cflags_cc": ["-fPIC", "-DBOOST_ALL_NO_LIB"],
            'xcode_settings': {
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                'CLANG_CXX_LIBRARY': 'libc++',
                'MACOSX_DEPLOYMENT_TARGET': '10.7',
            },
            'msvs_settings': {
                'VCCLCompilerTool': {'ExceptionHandling': 1},
            },
            "libraries": ["/usr/lib/x86_64-linux-gnu/libpython3.8.so", "/usr/lib/x86_64-linux-gnu/libboost_filesystem.so", "/usr/lib/x86_64-linux-gnu/libboost_system.so"]
        }
    ],
    'conditions': [
        ['OS=="mac"', {
            'cflags+': ['-fvisibility=hidden'],
            'xcode_settings': {
                'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',  # -fvisibility=hidden
            }
        }]
    ]
}
