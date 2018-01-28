/* ============================================================
* Falkon - Qt web browser
* Copyright (C) 2013-2018 David Rosca <nowrep@gmail.com>
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
#include "autofillwidget.h"
#include "ui_autofillwidget.h"
#include "autofill.h"
#include "qztools.h"
#include "webview.h"
#include "webpage.h"
#include "scripts.h"
#include "mainapplication.h"
#include "passwordmanager.h"

#include <QPushButton>

AutoFillWidget::AutoFillWidget(WebView* view, QWidget* parent)
    : LocationBarPopup(parent)
    , ui(new Ui::AutoFillWidget)
    , m_view(view)
{
    ui->setupUi(this);
}

void AutoFillWidget::setUsernames(const QStringList &usernames)
{
    int i = 0;
    for (const QString &username : usernames) {
        if (username.isEmpty()) {
            continue;
        }

        QPushButton* button = new QPushButton(this);
        button->setIcon(QIcon(":icons/other/login.png"));
        button->setStyleSheet("text-align:left;font-weight:bold;");
        button->setText(username);
        button->setFlat(true);

        ui->gridLayout->addWidget(button, i++, 0);
        connect(button, &QPushButton::clicked, this, [=]() {
            const auto entries = mApp->autoFill()->getFormData(m_view->url());
            for (PasswordEntry entry : entries) {
                if (entry.username != username) {
                    continue;
                }
                mApp->autoFill()->updateLastUsed(entry);
                m_view->page()->runJavaScript(Scripts::completeFormData(entry.data), WebPage::SafeJsWorld);
                break;
            }
            close();
        });
    }
}

AutoFillWidget::~AutoFillWidget()
{
    delete ui;
}
