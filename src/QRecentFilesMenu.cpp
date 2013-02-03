/*
*
* This file is part of QRecentFilesMenu,
* an open-source recent files menu widget
*
* Copyright (C) 2009 - 2010 Morgan Leborgne
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with QRecentFilesMenu. If not, see <http://www.gnu.org/licenses/>.
*
*/
#include "QRecentFilesMenu.h"

#include <QFileInfo>

static const qint32 RecentFilesMenuMagic = 0xff;

QRecentFilesMenu::QRecentFilesMenu(QWidget * parent)
: QMenu(parent)
, m_maxCount(10)
, m_format(QLatin1String("%d %s"))
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));

    setMaxCount(m_maxCount);
}

QRecentFilesMenu::QRecentFilesMenu(const QString & title, QWidget * parent)
: QMenu(title, parent)
, m_maxCount(10)
, m_format(QLatin1String("%d %s"))
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));

    setMaxCount(m_maxCount);
}

void QRecentFilesMenu::addRecentFile(const QString &fileName)
{
    m_files.removeAll(fileName);
    m_files.prepend(fileName);

    while (m_files.size() > maxCount())
        m_files.removeLast();

    updateRecentFileActions();
}

void QRecentFilesMenu::clearMenu()
{
    m_files.clear();

    updateRecentFileActions();
}

int QRecentFilesMenu::maxCount() const
{
    return m_maxCount;
}

void QRecentFilesMenu::setFormat(const QString &format)
{
    if (m_format == format)
        return;
    m_format = format;

    updateRecentFileActions();
}

const QString & QRecentFilesMenu::format() const
{
    return m_format;
}

QByteArray QRecentFilesMenu::saveState() const
{
    int version = 0;
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << qint32(RecentFilesMenuMagic);
    stream << qint32(version);
    stream << m_files;

    return data;
}

bool QRecentFilesMenu::restoreState(const QByteArray &state)
{
    int version = 0;
    QByteArray sd = state;
    QDataStream stream(&sd, QIODevice::ReadOnly);
    qint32 marker;
    qint32 v;

    stream >> marker;
    stream >> v;
    if (marker != RecentFilesMenuMagic || v != version)
        return false;

    stream >> m_files;

    updateRecentFileActions();

    return true;
}

void QRecentFilesMenu::setMaxCount(int count)
{
    m_maxCount = count;

    updateRecentFileActions();
}

void QRecentFilesMenu::menuTriggered(QAction* action)
{
    if (action->data().isValid())
        emit recentFileTriggered(action->data().toString());
}

void QRecentFilesMenu::updateRecentFileActions()
{
    int numRecentFiles = qMin(m_files.size(), maxCount());

    clear();

    for (int i = 0; i < numRecentFiles; ++i) {
        QString strippedName = QFileInfo(m_files[i]).fileName();

        QString text = m_format;
        text.replace(QLatin1String("%d"), QString::number(i + 1));
        text.replace(QLatin1String("%s"), strippedName);

        QAction* recentFileAct = addAction(text);
        recentFileAct->setData(m_files[i]);
    }
    addSeparator();
    addAction(QIcon(":/images/cancel.png"),tr("Clear Menu"), this, SLOT(clearMenu()));

    setEnabled(numRecentFiles > 0);
}

