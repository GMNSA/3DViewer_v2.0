import os
import ycm_core

flag_qt6 = [
    '-std=c++17',
    '-I/usr/lib/qt6/mkspecs/linux-clang',
    '-I/usr/lib/qt/mkspecs/linux-clang',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/',
   '-I/home/_who/Qt/6.4.0/gcc_64/include/QtOpenGLWidgets',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtOpenGLWidgets/QOpenGLWidget',
    #'-I/home/_who/Qt/6.4.0/gcc_64/include/QtOpenGL',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtConcurrent',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtCore',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtDBus',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtGui',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtHelp',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtMultimedia',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtMultimediaWidgets',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtNetwork',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtPlatformSupport',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtPositioning',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtScript',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtScriptTools',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtSql',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtSvg',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtTest',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtUiTools',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtV8',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtWebKit',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtWebKitWidgets',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtWidgets',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtXml',
    '-I/home/_who/Qt/6.4.0/gcc_64/include/QtXmlPatterns',
    '-DQT_CORE_LIB',
    '-DQT_GUI_LIB',
    '-DQT_NETWORK_LIB',
    '-DQT_QML_LIB',
    '-DQT_QUICK_LIB',
    '-DQT_SQL_LIB',
    '-DQT_WIDGETS_LIB',
    '-DQT_XML_LIB',
    '-I./lib/3DViewer/includes',
    '-I./lib/QtGifImage/includes'
    '-x'
]

flags_tmp = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-isystem',
    '-Wno-long-long',
    '-Wno-variadic-macros',
    '-fexceptions',
    '-ferror-limit=10000',
    '-DNDEBUG',
    '-x',
    'c++',
    "-fPIE",
    '-I/usr/lib/',
    '/usr/include',
    '/usr/local/include',
    '-I./code_c/',
    '-I./includes/',
    '-I./includes/View/',
    '-I./includes/Model/',
    '-I./includes/Controller/',
    '-I./srcs/',
    '-I./ui/',
    '-I/usr/lib/'
]

flags = flag_qt6 + flags_tmp


# Пути к заголовочным файлам Qt
qt_include_path = '/home/_who/Qt/6.4.0/gcc_64/include/'

# Флаги для всех файлов
flags = flag_qt6 + flags_tmp

# Путь к файлу UI
# ui_file = './srcs/mainwindow.ui'

# Путь к файлу cpp, сгенерированному из UI файла
# cpp_file_ui = './ui/mainwindow_ui.cpp'

# Путь к папке с компиляционной базой данных (если есть)
compilation_database_folder = ''

if os.path.exists(compilation_database_folder):
    database = ycm_core.CompilationDatabase(compilation_database_folder)
else:
    database = None

SOURCE_EXTENSIONS = ['.cpp', '.cxx', '.cc', '.c', '.m', '.mm', '.ui']

import subprocess

def compile_ui_files():
    ui_files_folder = './srcs/View/'
    cpp_files_folder = './ui/'

    if not os.path.exists(cpp_files_folder):
        os.makedirs(cpp_files_folder)

    for filename in os.listdir(ui_files_folder):
        if filename.endswith('.ui'):
            ui_file_path = os.path.join(ui_files_folder, filename)
            # cpp_file_path = os.path.join(cpp_files_folder, os.path.splitext(filename)[0] + '.cpp')
            cpp_file_path = os.path.join(cpp_files_folder, "ui_" + os.path.splitext(filename)[0] + '.h')
            command = f'uic {ui_file_path} -o {cpp_file_path}'
            subprocess.run(command, shell=True)

compile_ui_files()


def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))


def IsHeaderFile(filename):
    extension = os.path.splitext(filename)[1]
    return extension in ['.h', '.hxx', '.hpp', '.hh']


def GetCompilationInfoForFile(filename):
    if IsHeaderFile(filename):
        basename = os.path.splitext(filename)[0]
        for extension in SOURCE_EXTENSIONS:
            replacement_file = basename + extension
            if os.path.exists(replacement_file):
                compilation_info = database.GetCompilationInfoForFile(replacement_file)
                if compilation_info.compiler_flags_:
                    return compilation_info
        return None
    return database.GetCompilationInfoForFile(filename)


def Settings(**kwargs):
    if not database:
        return {
            'flags': flags,
            'include_paths_relative_to_dir': DirectoryOfThisScript(),
        }
    filename = kwargs['filename']
    compilation_info = GetCompilationInfoForFile(filename)

    if not compilation_info:
        return None

    return {
        'flags': list(compilation_info.compiler_flags_),
        'include_paths_relative_to_dir': compilation_info.compiler_working_dir_
    }
