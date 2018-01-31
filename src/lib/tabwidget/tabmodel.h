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
#pragma once

#include <QAbstractListModel>

#include "qzcommon.h"

class WebTab;
class BrowserWindow;

class FALKON_EXPORT TabModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        WebTabRole = Qt::UserRole + 1,
        TitleRole = Qt::UserRole + 2,
        IconRole = Qt::UserRole + 3,
        PinnedRole = Qt::UserRole + 4,
        RestoredRole = Qt::UserRole + 5
    };

    explicit TabModel(BrowserWindow *window, QObject *parent = nullptr);

    QModelIndex tabIndex(WebTab *tab) const;
    WebTab *tab(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

private:
    void init();
    void tabInserted(int index);
    void tabRemoved(int index);
    void tabMoved(int from, int to);

    BrowserWindow *m_window;
    QVector<WebTab*> m_tabs;
};
