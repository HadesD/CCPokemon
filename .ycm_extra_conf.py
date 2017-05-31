def FlagsForFile( filename, **kwargs ):
    return {
        'flags': [
            '-x', 'c++', '-Wall', '-Wextra', '-Werror', '-std=c++14',
            '-I', './cocos2d/cocos' 
        ],
    }
