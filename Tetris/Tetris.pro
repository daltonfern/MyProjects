QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TetrisPiece.cpp \
    endgamedialog.cpp \
    gamewindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    TetrisPiece.h \
    endgamedialog.h \
    gamewindow.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS += \
    logo.ico

DISTFILES += \
    README.md \
    docs/_tetris_piece_8h_source.html \
    docs/annotated.html \
    docs/bc_s.png \
    docs/bc_sd.png \
    docs/class_block-members.html \
    docs/class_block.html \
    docs/class_end_game_dialog-members.html \
    docs/class_end_game_dialog.html \
    docs/class_end_game_dialog.png \
    docs/class_game_window-members.html \
    docs/class_game_window.html \
    docs/class_game_window.png \
    docs/class_game_window_1_1_game_window.html \
    docs/class_main_window-members.html \
    docs/class_main_window.html \
    docs/class_main_window.png \
    docs/class_main_window_1_1_main_window.html \
    docs/class_tetris_piece-members.html \
    docs/class_tetris_piece.html \
    docs/classes.html \
    docs/clipboard.js \
    docs/closed.png \
    docs/cookie.js \
    docs/doc.svg \
    docs/docd.svg \
    docs/doxygen.css \
    docs/doxygen.svg \
    docs/doxygen_crawl.html \
    docs/dynsections.js \
    docs/endgamedialog_8h_source.html \
    docs/files.html \
    docs/folderclosed.svg \
    docs/folderclosedd.svg \
    docs/folderopen.svg \
    docs/folderopend.svg \
    docs/functions.html \
    docs/functions_func.html \
    docs/gamewindow_8h_source.html \
    docs/hierarchy.html \
    docs/index.html \
    docs/jquery.js \
    docs/mainwindow_8h_source.html \
    docs/md__r_e_a_d_m_e.html \
    docs/menu.js \
    docs/menudata.js \
    docs/minus.svg \
    docs/minusd.svg \
    docs/moc__predefs_8h_source.html \
    docs/nav_f.png \
    docs/nav_fd.png \
    docs/nav_g.png \
    docs/nav_h.png \
    docs/nav_hd.png \
    docs/open.png \
    docs/pages.html \
    docs/plus.svg \
    docs/plusd.svg \
    docs/search/all_0.js \
    docs/search/all_1.js \
    docs/search/all_2.js \
    docs/search/all_3.js \
    docs/search/all_4.js \
    docs/search/all_5.js \
    docs/search/all_6.js \
    docs/search/all_7.js \
    docs/search/all_8.js \
    docs/search/all_9.js \
    docs/search/all_a.js \
    docs/search/all_b.js \
    docs/search/classes_0.js \
    docs/search/classes_1.js \
    docs/search/classes_2.js \
    docs/search/classes_3.js \
    docs/search/classes_4.js \
    docs/search/close.svg \
    docs/search/functions_0.js \
    docs/search/functions_1.js \
    docs/search/functions_2.js \
    docs/search/functions_3.js \
    docs/search/functions_4.js \
    docs/search/functions_5.js \
    docs/search/functions_6.js \
    docs/search/functions_7.js \
    docs/search/functions_8.js \
    docs/search/functions_9.js \
    docs/search/functions_a.js \
    docs/search/mag.svg \
    docs/search/mag_d.svg \
    docs/search/mag_sel.svg \
    docs/search/mag_seld.svg \
    docs/search/pages_0.js \
    docs/search/pages_1.js \
    docs/search/pages_2.js \
    docs/search/search.css \
    docs/search/search.js \
    docs/search/searchdata.js \
    docs/splitbar.png \
    docs/splitbard.png \
    docs/sync_off.png \
    docs/sync_on.png \
    docs/tab_a.png \
    docs/tab_ad.png \
    docs/tab_b.png \
    docs/tab_bd.png \
    docs/tab_h.png \
    docs/tab_hd.png \
    docs/tab_s.png \
    docs/tab_sd.png \
    docs/tabs.css

RESOURCES += \
    Images.qrc
