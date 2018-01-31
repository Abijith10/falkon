/* ============================================================
* Falkon - Qt web browser
* Copyright (C) 2018 David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "webtabtest.h"
#include "autotests.h"
#include "webtab.h"
#include "mainapplication.h"

void WebTabTest::initTestCase()
{
}

void WebTabTest::cleanupTestCase()
{
}

void WebTabTest::parentChildTabsTest()
{
    WebTab tab1(mApp->getWindow());
    WebTab tab2(mApp->getWindow());
    WebTab tab3(mApp->getWindow());
    WebTab tab4(mApp->getWindow());
    WebTab tab5(mApp->getWindow());
    WebTab tab6(mApp->getWindow());

    tab1.addChildTab(&tab2);
    QCOMPARE(tab1.childTabs(), QVector<WebTab*>{&tab2});
    QCOMPARE(tab2.parentTab(), &tab1);
    QCOMPARE(tab2.childTabs(), QVector<WebTab*>{});

    tab1.addChildTab(&tab3);
    QCOMPARE(tab1.childTabs(), (QVector<WebTab*>{&tab2, &tab3}));
    QCOMPARE(tab3.parentTab(), &tab1);
    QCOMPARE(tab3.childTabs(), QVector<WebTab*>{});

    tab1.addChildTab(&tab4, 1);
    QCOMPARE(tab1.childTabs(), (QVector<WebTab*>{&tab2, &tab4, &tab3}));
    QCOMPARE(tab4.parentTab(), &tab1);
    QCOMPARE(tab4.childTabs(), QVector<WebTab*>{});

    tab4.addChildTab(&tab5);
    tab4.addChildTab(&tab6);

    tab4.attach(mApp->getWindow());
    tab4.detach();

    QCOMPARE(tab1.childTabs(), (QVector<WebTab*>{&tab2, &tab5, &tab6, &tab3}));
    QCOMPARE(tab4.parentTab(), nullptr);
    QCOMPARE(tab4.childTabs(), QVector<WebTab*>{});

    tab3.addChildTab(&tab4);
    tab3.setParentTab(nullptr);
    tab1.addChildTab(&tab3, 0);

    QCOMPARE(tab1.childTabs(), (QVector<WebTab*>{&tab3, &tab2, &tab5, &tab6}));
    QCOMPARE(tab3.parentTab(), &tab1);
    QCOMPARE(tab3.childTabs(), QVector<WebTab*>{&tab4});
    QCOMPARE(tab4.parentTab(), &tab3);
}

FALKONTEST_MAIN(WebTabTest)
