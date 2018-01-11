/* ============================================================
* Falkon - Qt web browser
* Copyright (C) 2010-2018 David Rosca <nowrep@gmail.com>
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
#ifndef ADBLOCKICON_H
#define ADBLOCKICON_H

#include <QPointer>

#include "qzcommon.h"
#include "abstractbuttoninterface.h"

class QUrl;

class AdBlockRule;

<<<<<<< HEAD
class FALKON_EXPORT AdBlockIcon : public ClickableLabel
||||||| parent of d11997ee... AdBlockIcon: Move from statusbar to navigationbar as tool button
class QUPZILLA_EXPORT AdBlockIcon : public ClickableLabel
=======
class QUPZILLA_EXPORT AdBlockIcon : public AbstractButtonInterface
>>>>>>> d11997ee... AdBlockIcon: Move from statusbar to navigationbar as tool button
{
    Q_OBJECT

public:
    explicit AdBlockIcon(QObject *parent = nullptr);
    ~AdBlockIcon();

    QString id() const override;
    QString name() const override;

private slots:
    void toggleCustomFilter();

private:
    void updateState();
    void webPageChanged(WebPage *page);
    void clicked(ClickController *controller);

    QPointer<WebPage> m_page;
    QVector<QPair<AdBlockRule*, QUrl> > m_blockedPopups;
};

#endif // ADBLOCKICON_H
