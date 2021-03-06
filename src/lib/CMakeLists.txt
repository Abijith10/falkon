add_definitions(-DFALKON_SHAREDLIBRARY)

set(CMAKE_CXX_STANDARD 14) # Enable C++14, with cmake >= 3.1
set(CMAKE_CXX_EXTENSIONS OFF) # Don't enable gcc-specific extensions

set(SRCS
    3rdparty/qtsingleapplication/qtsingleapplication.cpp
    3rdparty/qtsingleapplication/qtlocalpeer.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SRCS ${SRCS} ${CMAKE_SOURCE_DIR}/tests/modeltest/modeltest.cpp)
    include_directories(${CMAKE_SOURCE_DIR}/tests/modeltest)
endif()

include_directories(
    3rdparty
    adblock
    app
    autofill
    bookmarks
    cookies
    downloads
    history
    navigation
    network
    notifications
    opensearch
    other
    plugins
    popupwindow
    preferences
    session
    sidebar
    tabwidget
    tools
    webengine
    webtab
)

include_directories(${OPENSSL_INCLUDE_DIR})

set(SRCS ${SRCS}
    3rdparty/fancytabwidget.cpp
    3rdparty/lineedit.cpp
    3rdparty/processinfo.cpp
    3rdparty/squeezelabelv1.cpp
    3rdparty/squeezelabelv2.cpp
    3rdparty/stylehelper.cpp
    adblock/adblockaddsubscriptiondialog.cpp
    adblock/adblockurlinterceptor.cpp
    adblock/adblockdialog.cpp
    adblock/adblockicon.cpp
    adblock/adblockmanager.cpp
    adblock/adblockmatcher.cpp
    adblock/adblockrule.cpp
    adblock/adblocksearchtree.cpp
    adblock/adblocksubscription.cpp
    adblock/adblocktreewidget.cpp
    adblock/adblockplugin.cpp
    app/autosaver.cpp
    app/browserwindow.cpp
    app/commandlineoptions.cpp
    app/datapaths.cpp
    app/mainapplication.cpp
    app/mainmenu.cpp
    app/profilemanager.cpp
    app/proxystyle.cpp
    app/qzcommon.cpp
    app/settings.cpp
    autofill/autofill.cpp
    autofill/autofillicon.cpp
    autofill/autofillnotification.cpp
    autofill/autofillwidget.cpp
    autofill/passwordbackends/databaseencryptedpasswordbackend.cpp
    autofill/passwordbackends/databasepasswordbackend.cpp
    autofill/passwordbackends/passwordbackend.cpp
    autofill/passwordmanager.cpp
    bookmarks/bookmarkitem.cpp
    bookmarks/bookmarks.cpp
    bookmarks/bookmarksexport/bookmarksexportdialog.cpp
    bookmarks/bookmarksexport/bookmarksexporter.cpp
    bookmarks/bookmarksexport/htmlexporter.cpp
    bookmarks/bookmarksicon.cpp
    bookmarks/bookmarksimport/bookmarksimportdialog.cpp
    bookmarks/bookmarksimport/bookmarksimporter.cpp
    bookmarks/bookmarksimport/firefoximporter.cpp
    bookmarks/bookmarksimport/htmlimporter.cpp
    bookmarks/bookmarksimport/chromeimporter.cpp
    bookmarks/bookmarksimport/ieimporter.cpp
    bookmarks/bookmarksimport/operaimporter.cpp
    bookmarks/bookmarksitemdelegate.cpp
    bookmarks/bookmarksmanager.cpp
    bookmarks/bookmarksmenu.cpp
    bookmarks/bookmarksmodel.cpp
    bookmarks/bookmarkstoolbarbutton.cpp
    bookmarks/bookmarkstoolbar.cpp
    bookmarks/bookmarkstools.cpp
    bookmarks/bookmarkstreeview.cpp
    bookmarks/bookmarkswidget.cpp
    cookies/cookiejar.cpp
    cookies/cookiemanager.cpp
    downloads/downloaditem.cpp
    downloads/downloadmanager.cpp
    downloads/downloadoptionsdialog.cpp
    downloads/downloadsbutton.cpp
    history/history.cpp
    history/historyitem.cpp
    history/historymanager.cpp
    history/historymenu.cpp
    history/historymodel.cpp
    history/historytreeview.cpp
    navigation/completer/locationcompleter.cpp
    navigation/completer/locationcompleterdelegate.cpp
    navigation/completer/locationcompletermodel.cpp
    navigation/completer/locationcompleterrefreshjob.cpp
    navigation/completer/locationcompleterview.cpp
    navigation/downicon.cpp
    navigation/goicon.cpp
    navigation/locationbar.cpp
    navigation/locationbarpopup.cpp
    navigation/navigationbar.cpp
    navigation/navigationbartoolbutton.cpp
    navigation/navigationbarconfigdialog.cpp
    navigation/navigationcontainer.cpp
    navigation/reloadstopbutton.cpp
    navigation/siteicon.cpp
    navigation/websearchbar.cpp
    network/networkmanager.cpp
    network/networkurlinterceptor.cpp
    network/schemehandlers/extensionschemehandler.cpp
    network/schemehandlers/falkonschemehandler.cpp
    network/sslerrordialog.cpp
    notifications/desktopnotification.cpp
    notifications/desktopnotificationsfactory.cpp
    opensearch/editsearchengine.cpp
    opensearch/opensearchengine.cpp
    opensearch/opensearchenginedelegate.cpp
    opensearch/opensearchreader.cpp
    opensearch/searchenginesdialog.cpp
    opensearch/searchenginesmanager.cpp
    other/aboutdialog.cpp
    other/browsinglibrary.cpp
    other/clearprivatedata.cpp
    other/checkboxdialog.cpp
    other/iconchooser.cpp
    other/licenseviewer.cpp
    other/qzsettings.cpp
    other/siteinfo.cpp
    other/siteinfowidget.cpp
    other/statusbar.cpp
    other/updater.cpp
    other/useragentmanager.cpp
    other/protocolhandlermanager.cpp
    plugins/pluginproxy.cpp
    plugins/plugins.cpp
    plugins/speeddial.cpp
    plugins/qml/qmlpluginloader.cpp
    plugins/qml/qmlplugin.cpp
    plugins/qml/qmlplugins.cpp
    plugins/qml/qmlplugininterface.cpp
    plugins/qml/qmlengine.cpp
    plugins/qml/qmlstaticdata.cpp
    plugins/qml/api/bookmarks/qmlbookmarktreenode.cpp
    plugins/qml/api/bookmarks/qmlbookmarks.cpp
    plugins/qml/api/topsites/qmlmostvisitedurl.cpp
    plugins/qml/api/topsites/qmltopsites.cpp
    plugins/qml/api/history/qmlhistoryitem.cpp
    plugins/qml/api/history/qmlhistory.cpp
    plugins/qml/api/cookies/qmlcookie.cpp
    plugins/qml/api/cookies/qmlcookies.cpp
    plugins/qml/api/tabs/qmltab.cpp
    plugins/qml/api/tabs/qmltabs.cpp
    plugins/qml/api/notifications/qmlnotifications.cpp
    plugins/qml/api/clipboard/qmlclipboard.cpp
    plugins/qml/api/windows/qmlwindow.cpp
    plugins/qml/api/windows/qmlwindows.cpp
    plugins/qml/api/browseraction/qmlbrowseraction.cpp
    plugins/qml/api/sidebar/qmlsidebar.cpp
    plugins/qml/api/menus/qmlmenu.cpp
    plugins/qml/api/menus/qmlaction.cpp
    plugins/qml/api/menus/qmlwebhittestresult.cpp
    plugins/qml/api/settings/qmlsettings.cpp
    plugins/qml/api/events/qmlqzobjects.cpp
    plugins/qml/api/events/qmlmouseevent.cpp
    plugins/qml/api/events/qmlwheelevent.cpp
    plugins/qml/api/events/qmlkeyevent.cpp
    plugins/qml/api/userscript/qmluserscript.cpp
    plugins/qml/api/userscript/qmluserscripts.cpp
    plugins/qml/api/userscript/qmlexternaljsobject.cpp
    plugins/qml/api/extensionscheme/qmlextensionscheme.cpp
    plugins/qml/api/extensionscheme/qmlwebengineurlrequestjob.cpp
    plugins/qml/api/fileutils/qmlfileutils.cpp
    plugins/qml/api/qmlenums.cpp
    popupwindow/popuplocationbar.cpp
    popupwindow/popupstatusbarmessage.cpp
    popupwindow/popupwebview.cpp
    popupwindow/popupwindow.cpp
    preferences/acceptlanguage.cpp
    preferences/autofillmanager.cpp
    preferences/jsoptions.cpp
    preferences/pluginlistdelegate.cpp
    preferences/pluginsmanager.cpp
    preferences/preferences.cpp
    preferences/thememanager.cpp
    preferences/useragentdialog.cpp
    session/recoveryjsobject.cpp
    session/restoremanager.cpp
    session/sessionmanager.cpp
    session/sessionmanagerdialog.cpp
    sidebar/bookmarkssidebar.cpp
    sidebar/historysidebar.cpp
    sidebar/sidebar.cpp
    tabwidget/combotabbar.cpp
    tabwidget/tabbar.cpp
    tabwidget/tabicon.cpp
    tabwidget/tabmodel.cpp
    tabwidget/tabmrumodel.cpp
    tabwidget/tabtreemodel.cpp
    tabwidget/tabstackedwidget.cpp
    tabwidget/tabwidget.cpp
    tabwidget/tabcontextmenu.cpp
    tools/abstractbuttoninterface.cpp
    tools/aesinterface.cpp
    tools/animatedwidget.cpp
    tools/buttonwithmenu.cpp
    tools/certificateinfowidget.cpp
    tools/clickablelabel.cpp
    tools/closedtabsmanager.cpp
    tools/closedwindowsmanager.cpp
    tools/colors.cpp
    tools/delayedfilewatcher.cpp
    tools/desktopfile.cpp
    tools/docktitlebarwidget.cpp
    tools/enhancedmenu.cpp
    tools/focusselectlineedit.cpp
    tools/headerview.cpp
    tools/horizontallistwidget.cpp
    tools/html5permissions/html5permissionsdialog.cpp
    tools/html5permissions/html5permissionsmanager.cpp
    tools/html5permissions/html5permissionsnotification.cpp
    tools/iconprovider.cpp
    tools/listitemdelegate.cpp
    tools/mactoolbutton.cpp
    tools/menubar.cpp
    tools/pagethumbnailer.cpp
    tools/progressbar.cpp
    tools/qztools.cpp
    tools/removeitemfocusdelegate.cpp
    tools/scripts.cpp
    tools/sqldatabase.cpp
    tools/toolbutton.cpp
    tools/treewidget.cpp
    tools/wheelhelper.cpp
    webengine/javascript/autofilljsobject.cpp
    webengine/javascript/externaljsobject.cpp
    webengine/loadrequest.cpp
    webengine/webhittestresult.cpp
    webengine/webinspector.cpp
    webengine/webpage.cpp
    webengine/webview.cpp
    webengine/webscrollbar.cpp
    webengine/webscrollbarmanager.cpp
    webtab/searchtoolbar.cpp
    webtab/tabbedwebview.cpp
    webtab/webtab.cpp
)

if (HAVE_LIBINTL)
    set(SRCS ${SRCS} plugins/qml/api/i18n/qmli18n.cpp)
endif()

if (WIN32)
    set(SRCS ${SRCS} other/registerqappassociation.cpp)
endif()
if (APPLE)
    set(SRCS ${SRCS} tools/disablewindowtabbbing.mm)
endif()

# TODO: use ki18n_wrap_ui?
qt5_wrap_ui(SRCS
    adblock/adblockaddsubscriptiondialog.ui
    adblock/adblockdialog.ui
    autofill/autofillnotification.ui
    autofill/autofillwidget.ui
    autofill/passwordbackends/masterpassworddialog.ui
    bookmarks/bookmarksexport/bookmarksexportdialog.ui
    bookmarks/bookmarksimport/bookmarksimportdialog.ui
    bookmarks/bookmarksmanager.ui
    bookmarks/bookmarkswidget.ui
    cookies/cookiemanager.ui
    downloads/downloaditem.ui
    downloads/downloadmanager.ui
    downloads/downloadoptionsdialog.ui
    history/historymanager.ui
    navigation/navigationbarconfigdialog.ui
    network/sslerrordialog.ui
    notifications/desktopnotification.ui
    opensearch/editsearchengine.ui
    opensearch/searchenginesdialog.ui
    other/aboutdialog.ui
    other/browsinglibrary.ui
    other/clearprivatedata.ui
    other/iconchooser.ui
    other/siteinfo.ui
    other/siteinfowidget.ui
    preferences/acceptlanguage.ui
    preferences/addacceptlanguage.ui
    preferences/autofillmanager.ui
    preferences/jsoptions.ui
    preferences/pluginslist.ui
    preferences/preferences.ui
    preferences/thememanager.ui
    preferences/useragentdialog.ui
    session/sessionmanagerdialog.ui
    sidebar/bookmarkssidebar.ui
    sidebar/historysidebar.ui
    tools/certificateinfowidget.ui
    tools/docktitlebarwidget.ui
    tools/html5permissions/html5permissionsdialog.ui
    tools/html5permissions/html5permissionsnotification.ui
    webengine/jsalert.ui
    webengine/jsconfirm.ui
    webengine/jsprompt.ui
    webtab/searchtoolbar.ui
)

qt5_add_resources(SRCS
    data/data.qrc
    data/html.qrc
    data/icons.qrc
    data/breeze-fallback.qrc
    adblock/adblock.qrc
)

add_library(FalkonPrivate SHARED ${SRCS})

get_property(QT_WEBENGINE_INCLUDE_DIRS TARGET Qt5::WebEngine PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(FalkonPrivate SYSTEM PUBLIC ${QT_WEBENGINE_INCLUDE_DIRS})

target_link_libraries(FalkonPrivate
    Qt5::Widgets
    Qt5::WebEngineWidgets
    Qt5::Network
    Qt5::Sql
    Qt5::PrintSupport
    Qt5::QuickWidgets
    Qt5::WebChannel
    ${OPENSSL_CRYPTO_LIBRARY}
)

if (UNIX AND NOT APPLE)
    if (NOT NO_X11)
        target_link_libraries(FalkonPrivate XCB::XCB Qt5::X11Extras)
    endif()

    set_target_properties(FalkonPrivate PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION "3")
    install(TARGETS FalkonPrivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
endif()

if (WIN32)
    target_link_libraries(FalkonPrivate Qt5::WinExtras)
endif()

if (APPLE)
    target_link_libraries(FalkonPrivate "-framework CoreServices -framework AppKit")
endif()

if (NOT DISABLE_DBUS)
    target_link_libraries(FalkonPrivate Qt5::DBus)
endif()
