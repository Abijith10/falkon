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
#include "locationcompleterview.h"
#include "locationcompletermodel.h"
#include "locationcompleterdelegate.h"

#include <QKeyEvent>
#include <QApplication>
#include <QScrollBar>
#include <QVBoxLayout>

LocationCompleterView::LocationCompleterView()
    : QWidget(nullptr)
    , m_ignoreNextMouseMove(false)
{
    setAttribute(Qt::WA_ShowWithoutActivating);
    setAttribute(Qt::WA_X11NetWmWindowTypeCombo);

    if (qApp->platformName() == QL1S("xcb")) {
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::BypassWindowManagerHint);
    } else {
        setWindowFlags(Qt::Popup);
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    m_view = new QListView(this);
    layout->addWidget(m_view);

    m_view->setUniformItemSizes(true);
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);

    m_view->setMouseTracking(true);
    qApp->installEventFilter(this);

    m_delegate = new LocationCompleterDelegate(this);
    m_view->setItemDelegate(m_delegate);
}

QAbstractItemModel *LocationCompleterView::model() const
{
    return m_view->model();
}

void LocationCompleterView::setModel(QAbstractItemModel *model)
{
    m_view->setModel(model);
}

QModelIndex LocationCompleterView::currentIndex() const
{
    return m_view->currentIndex();
}

void LocationCompleterView::setCurrentIndex(const QModelIndex &index)
{
    m_view->setCurrentIndex(index);
}

QItemSelectionModel *LocationCompleterView::selectionModel() const
{
    return m_view->selectionModel();
}

void LocationCompleterView::setOriginalText(const QString &originalText)
{
    m_delegate->setOriginalText(originalText);
}

void LocationCompleterView::adjustSize()
{
    const int maxItemsCount = 12;
    m_view->setFixedHeight(m_view->sizeHintForRow(0) * qMin(maxItemsCount, model()->rowCount()) + 2 * m_view->frameWidth());
    setFixedHeight(sizeHint().height());
}

bool LocationCompleterView::eventFilter(QObject* object, QEvent* event)
{
    // Event filter based on QCompleter::eventFilter from qcompleter.cpp

    if (object == this || object == m_view || !isVisible()) {
        return false;
    }

    if (object == m_view->viewport()) {
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *e = static_cast<QMouseEvent*>(event);
            QModelIndex idx = m_view->indexAt(e->pos());
            if (!idx.isValid()) {
                return false;
            }

            Qt::MouseButton button = e->button();
            Qt::KeyboardModifiers modifiers = e->modifiers();

            if (button == Qt::LeftButton && modifiers == Qt::NoModifier) {
                emit indexActivated(idx);
                return true;
            }

            if (button == Qt::MiddleButton || (button == Qt::LeftButton && modifiers == Qt::ControlModifier)) {
                emit indexCtrlActivated(idx);
                return true;
            }

            if (button == Qt::LeftButton && modifiers == Qt::ShiftModifier) {
                emit indexShiftActivated(idx);
                return true;
            }
        }
        return false;
    }

    switch (event->type()) {
    case QEvent::KeyPress: {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        const QModelIndex idx = m_view->currentIndex();
        const QModelIndex visitSearchIdx = model()->index(0, 0).data(LocationCompleterModel::VisitSearchItemRole).toBool() ? model()->index(0, 0) : QModelIndex();

        if ((keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down) && m_view->currentIndex() != idx) {
            m_view->setCurrentIndex(idx);
        }

        switch (keyEvent->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (!idx.isValid()) {
                break;
            }

            if (modifiers == Qt::NoModifier || modifiers == Qt::KeypadModifier) {
                emit indexActivated(idx);
                return true;
            }

            if (modifiers == Qt::ControlModifier) {
                emit indexCtrlActivated(idx);
                return true;
            }

            if (modifiers == Qt::ShiftModifier) {
                emit indexShiftActivated(idx);
                return true;
            }
            break;

        case Qt::Key_End:
            if (modifiers & Qt::ControlModifier) {
                m_view->setCurrentIndex(model()->index(model()->rowCount() - 1, 0));
                return true;
            } else {
                close();
            }
            break;

        case Qt::Key_Home:
            if (modifiers & Qt::ControlModifier) {
                m_view->setCurrentIndex(model()->index(0, 0));
                m_view->scrollToTop();
                return true;
            } else {
                close();
            }
            break;

        case Qt::Key_Escape:
            close();
            return true;

        case Qt::Key_F4:
            if (modifiers == Qt::AltModifier)  {
                close();
                return false;
            }
            break;

        case Qt::Key_Tab:
        case Qt::Key_Backtab: {
            if (keyEvent->modifiers() != Qt::NoModifier) {
                return false;
            }
            Qt::Key k = keyEvent->key() == Qt::Key_Tab ? Qt::Key_Down : Qt::Key_Up;
            QKeyEvent ev(QKeyEvent::KeyPress, k, Qt::NoModifier);
            QApplication::sendEvent(focusProxy(), &ev);
            return true;
        }

        case Qt::Key_Up:
            if (!idx.isValid() || idx == visitSearchIdx) {
                int rowCount = model()->rowCount();
                QModelIndex lastIndex = model()->index(rowCount - 1, 0);
                m_view->setCurrentIndex(lastIndex);
            } else if (idx.row() == 0) {
                m_view->setCurrentIndex(QModelIndex());
            } else {
                m_view->setCurrentIndex(model()->index(idx.row() - 1, 0));
            }
            return true;

        case Qt::Key_Down:
            if (!idx.isValid()) {
                QModelIndex firstIndex = model()->index(0, 0);
                m_view->setCurrentIndex(firstIndex);
            } else if (idx != visitSearchIdx && idx.row() == model()->rowCount() - 1) {
                m_view->setCurrentIndex(visitSearchIdx);
                m_view->scrollToTop();
            } else {
                m_view->setCurrentIndex(model()->index(idx.row() + 1, 0));
            }
            return true;

        case Qt::Key_Delete:
            if (idx != visitSearchIdx && m_view->viewport()->rect().contains(m_view->visualRect(idx))) {
                emit indexDeleteRequested(idx);
                return true;
            }
            break;

        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            if (keyEvent->modifiers() != Qt::NoModifier) {
                return false;
            }
            QApplication::sendEvent(m_view, event);
            return true;

        case Qt::Key_Shift:
            // don't switch if there is no hovered or selected index to not disturb typing
            if (idx != visitSearchIdx || underMouse()) {
                m_delegate->setShowSwitchToTab(false);
                m_view->viewport()->update();
                return true;
            }
            break;
        } // switch (keyEvent->key())

        if (focusProxy()) {
            (static_cast<QObject*>(focusProxy()))->event(keyEvent);
        }
        return true;
    }

    case QEvent::KeyRelease: {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        switch (keyEvent->key()) {
        case Qt::Key_Shift:
            m_delegate->setShowSwitchToTab(true);
            m_view->viewport()->update();
            return true;
        }
        break;
    }

    case QEvent::Show:
        // Don't hover item when showing completer and mouse is currently in rect
        m_ignoreNextMouseMove = true;
        break;

    case QEvent::Wheel:
    case QEvent::MouseButtonPress:
        if (!underMouse()) {
            close();
            return false;
        }
        break;

    case QEvent::FocusOut: {
        QFocusEvent *focusEvent = static_cast<QFocusEvent*>(event);
        if (focusEvent->reason() != Qt::PopupFocusReason && focusEvent->reason() != Qt::MouseFocusReason) {
            close();
        }
        break;
    }

    case QEvent::Move:
    case QEvent::Resize: {
        QWidget *w = qobject_cast<QWidget*>(object);
        if (w && w->isWindow() && focusProxy() && w == focusProxy()->window()) {
            close();
        }
        break;
    }

    default:
        break;
    } // switch (event->type())

    return false;
}

void LocationCompleterView::close()
{
    hide();
    m_view->verticalScrollBar()->setValue(0);

    m_delegate->setShowSwitchToTab(true);

    emit closed();
}
